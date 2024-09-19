#include <iostream>
#include <vector>
#include <iomanip>  // For std::setw and std::fixed

class SMATradingStrategy {
private:
    std::vector<double> stockPrices;  // Stock prices
    int shortWindow;  // Short-term SMA window
    int longWindow;   // Long-term SMA window
    double cash;      // Cash balance
    double position;  // Number of shares held

public:
    SMATradingStrategy(int shortW, int longW, double startCapital) 
        : shortWindow(shortW), longWindow(longW), cash(startCapital), position(0) {}

    // Load stock prices (hardcoded for simplicity)
    void loadStockPrices() {
        stockPrices = {100.34, 101.56, 102.78, 103.45, 102.32, 101.50, 
                       104.50, 105.00, 103.00, 104.00, 102.50, 101.50};
    }

    // Calculate SMA for a given window size at a specific index
    double calculateSMA(int windowSize, int endIndex) {
        double sum = 0.0;
        for (int i = endIndex - windowSize + 1; i <= endIndex; ++i) {
            sum += stockPrices[i];
        }
        return sum / windowSize;
    }

    // Execute the strategy (buy/sell signals based on SMA crossovers)
    void executeStrategy() {
        bool holding = false;
        std::cout << std::fixed << std::setprecision(2);  // Set decimal precision

        std::cout << "Price  ShortSMA  LongSMA  Action  Cash    Position\n";
        std::cout << "--------------------------------------------------------\n";

        // Iterate through stock prices and calculate SMAs
        for (size_t i = longWindow; i < stockPrices.size(); ++i) {
            double shortSMA = calculateSMA(shortWindow, i);
            double longSMA = calculateSMA(longWindow, i);

            std::string action;
            if (shortSMA > longSMA && !holding) {
                holding = true;
                position = cash / stockPrices[i];  // Buy shares
                cash = 0;  // Invest all cash
                action = "    Buy    " ;
            }
            else if (shortSMA < longSMA && holding) {
                holding = false;
                cash = position * stockPrices[i];  // Sell all shares
                position = 0;  // No shares held
                action = "    Sell   ";
            }
            else {
                // Hold: no action
                action = "    Hold   ";
            }

            // Print the results
            std::cout << std::setw(6) << stockPrices[i] 
                      << std::setw(10) << shortSMA 
                      << std::setw(10) << longSMA 
                      << std::setw(7) << action 
                      << std::setw(7) << cash 
                      << std::setw(10) << position 
                      << std::endl;
        }
        
        // Final portfolio value
        double finalPortfolioValue = cash + (position * stockPrices.back());
        std::cout << "--------------------------------------------------------\n";
        std::cout << "Final Portfolio Value: " << finalPortfolioValue << "\n";
    }
};

int main() {
    // Create a strategy with short window 3, long window 5, and initial capital 10000
    SMATradingStrategy strategy(3, 5, 10000.0);
    
    // Load stock prices
    strategy.loadStockPrices();
    
    // Execute the strategy
    strategy.executeStrategy();

    return 0;
}
