#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

class TradingIndicators {
private:
    std::vector<double> prices;
    int smaWindow, rsiWindow;
    double cash;
    int shares;

public:
    TradingIndicators(int smaWindow, int rsiWindow, double initialCash) 
        : smaWindow(smaWindow), rsiWindow(rsiWindow), cash(initialCash), shares(0) {}

    void updatePrice(double price) {
        prices.push_back(price);
        if (prices.size() > std::max(smaWindow, rsiWindow)) {
            prices.erase(prices.begin());
        }
    }

    double calculateSMA() {
        if (prices.size() < smaWindow) return 0.0;
        double sum = std::accumulate(prices.end() - smaWindow, prices.end(), 0.0);
        return sum / smaWindow;
    }

    double calculateRSI() {
        if (prices.size() < rsiWindow + 1) return 0.0;

        double gain = 0.0, loss = 0.0;

        // Calculate gains and losses over the RSI window
        for (int i = prices.size() - rsiWindow; i < prices.size(); ++i) {
            double change = prices[i] - prices[i - 1];
            if (change > 0) gain += change;
            else loss -= change;
        }

        double avgGain = gain / rsiWindow;
        double avgLoss = loss / rsiWindow;

        // Avoid division by zero
        if (avgLoss == 0) return 100.0;

        double rs = avgGain / avgLoss;
        return 100 - (100 / (1 + rs));
    }
    
    void buy(double price) {
        if (cash > 0) {
            int sharesToBuy = static_cast<int>(cash / price);
            shares += sharesToBuy;
            cash -= sharesToBuy * price;
            std::cout << "Bought " << sharesToBuy << " shares at " << price << std::endl;
        }
    }

    void sell(double price) {
        if (shares > 0) {
            cash += shares * price;
            std::cout << "Sold " << shares << " shares at " << price << std::endl;
            shares = 0;
        }
    }

    double getPortfolioValue(double currentPrice) {
        return cash + shares * currentPrice;
    }
    
    void decideTrade(double currentPrice) {
        double sma = calculateSMA();
        double rsi = calculateRSI();

        // Simple buy/sell logic based on SMA and RSI
        if (currentPrice < sma && rsi < 30) {
            buy(currentPrice);  // Buy if price is below SMA and RSI indicates oversold
        } else if (currentPrice > sma && rsi > 70) {
            sell(currentPrice); // Sell if price is above SMA and RSI indicates overbought
        }
    }
};

int main() {
    const int SMA_WINDOW = 5;
    const int RSI_WINDOW = 14;
    const double INITIAL_CASH = 10000.0;

    TradingIndicators indicators(SMA_WINDOW, RSI_WINDOW, INITIAL_CASH);

    // Sample price data
    std::vector<double> priceData = {100, 102, 101, 105, 110, 108, 107, 106, 111, 115, 113, 112, 114, 116, 118};

    // Simulating trading for each price in priceData
    for (double price : priceData) {
        indicators.updatePrice(price);
        indicators.decideTrade(price);

        double sma = indicators.calculateSMA();
        double rsi = indicators.calculateRSI();

        std::cout << "Price: " << price
                  << ", SMA(" << SMA_WINDOW << "): " << sma
                  << ", RSI(" << RSI_WINDOW << "): " << rsi
                  << std::endl;

        // Display portfolio value at each step
        double portfolioValue = indicators.getPortfolioValue(price);
        std::cout << "Portfolio Value: " << portfolioValue << std::endl;
    }

    return 0;
}