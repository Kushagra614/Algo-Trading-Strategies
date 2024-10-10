#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class BollingerBands {
private:
    int period;
    double multiplier;
    std::vector<double> prices;

public:
    BollingerBands(int p, double m) : period(p), multiplier(m) {}

    void addPrice(double price) {
        prices.push_back(price);
    }

    double calculateSMA(int currentIndex) {
        if (currentIndex < period - 1) return 0;
        double sum = 0.0;
        for (int i = currentIndex - period + 1; i <= currentIndex; ++i) {
            sum += prices[i];
        }
        return sum / period;
    }

    double calculateStandardDeviation(double sma, int currentIndex) {
        if (currentIndex < period - 1) return 0;
        double sum = 0.0;
        for (int i = currentIndex - period + 1; i <= currentIndex; ++i) {
            sum += pow(prices[i] - sma, 2);
        }
        return sqrt(sum / period);
    }

    std::pair<double, double> getBollingerBands(int currentIndex) {
        double sma = calculateSMA(currentIndex);
        double stdDev = calculateStandardDeviation(sma, currentIndex);
        double upperBand = sma + (multiplier * stdDev);
        double lowerBand = sma - (multiplier * stdDev);
        return std::make_pair(upperBand, lowerBand);
    }

    void generateSignals() {
        std::cout << std::fixed << std::setprecision(2);
    
        // Print table header
        std::cout << "Day | Price | Upper Band | Lower Band | Signal" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;

        // Vectors to store buy and sell signals
        std::vector<std::pair<int, double>> buySignals;
        std::vector<std::pair<int, double>> sellSignals;

        double prevPrice = 0;

        for (int i = period - 1; i < prices.size(); ++i) {
            double price = prices[i];
            auto bands = getBollingerBands(i);
            double upperBand = bands.first;
            double lowerBand = bands.second;

            std::string signal = "HOLD";

            // Check for buy signal
            if (i > period && (price < lowerBand || (prevPrice > lowerBand && price <= lowerBand))) {
                buySignals.push_back({i, price});
                signal = "BUY";
            } 
            // Check for sell signal
            else if (i > period && (price > upperBand || (prevPrice < upperBand && price >= upperBand))) {
                sellSignals.push_back({i, price});
                signal = "SELL";
            }

            // Print table row with signal
            std::cout << std::setw(3) << i << " | " 
                      << std::setw(5) << price << " | " 
                      << std::setw(10) << upperBand << " | " 
                      << std::setw(10) << lowerBand << " | "
                      << std::setw(4) << signal << std::endl;

            prevPrice = price;
        }

        // Print buy signals
        std::cout << "\nBuy Signals:" << std::endl;
        for (const auto& signal : buySignals) {
            std::cout << "Buy Signal at Price: " << signal.second 
                      << " on Day: " << signal.first << std::endl;
        }

        // Print sell signals
        std::cout << "\nSell Signals:" << std::endl;
        for (const auto& signal : sellSignals) {
            std::cout << "Sell Signal at Price: " << signal.second 
                      << " on Day: " << signal.first << std::endl;
        }

        if (buySignals.empty() && sellSignals.empty()) {
            std::cout << "\nNo buy or sell signals were generated." << std::endl;
        }
    }
};

int main() {
    BollingerBands bb(20, 2.0);  // 20-day period, 2 standard deviations

    // New dataset with sufficient volatility to generate buy/sell signals
    std::vector<double> priceData = {
        100, 102, 105, 107, 110, 113, 115, 110, 108, 105,  // Initial uptrend
        103, 100, 98, 95, 97, 100, 105, 110, 115, 120,    // Fluctuation
        125, 130, 128, 126, 124, 122, 121, 123, 126, 130, // Uptrend followed by slight decline
        135, 140, 138, 135, 130, 125, 120, 115, 110, 105, // Gradual decline
        102, 100, 98, 95, 92, 90, 88, 86, 84, 82,          // Continued decline
        90, 95, 100, 110, 120, 130, 125, 120, 115, 120    // Gradual rise back up
    };

    for (double price : priceData) {
        bb.addPrice(price);
    }

    bb.generateSignals();

    return 0;
}
