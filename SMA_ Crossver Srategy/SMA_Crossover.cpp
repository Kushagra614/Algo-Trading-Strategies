#include <iostream>
#include <vector>
#include <random>
#include <string>

class MovingAverageCrossoverStrategy {
private:
    std::vector<double> prices;
    int shortWindow;
    int longWindow;
    bool lastSignalWasBuy;

public:
    MovingAverageCrossoverStrategy(int shortWindow, int longWindow)
        : shortWindow(shortWindow), longWindow(longWindow), lastSignalWasBuy(false) {}

    void updatePrice(double price) {
        prices.push_back(price);
        if (prices.size() > longWindow) {
            prices.erase(prices.begin());
        }
    }

    std::string generateSignal() {
        if (prices.size() < longWindow) {
            return "Hold";
        }
        double shortMA = calculateMovingAverage(shortWindow);
        double longMA = calculateMovingAverage(longWindow);
        std::cout << "Short MA: " << shortMA << ", Long MA: " << longMA << std::endl;
        
        if (shortMA > longMA && !lastSignalWasBuy) {
            lastSignalWasBuy = true;
            return "Buy";
        } else if (shortMA < longMA && lastSignalWasBuy) {
            lastSignalWasBuy = false;
            return "Sell";
        }
        return "Hold";
    }

private:
    double calculateMovingAverage(int window) {
        double sum = 0.0;
        for (int i = prices.size() - window; i < prices.size(); ++i) {
            sum += prices[i];
        }
        return sum / window;
    }
};

// Function to generate a random price change
double generateRandomPriceChange() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> d(0, 1); // Mean 0, standard deviation 1
    return d(gen);
}

int main() {
    MovingAverageCrossoverStrategy strategy(10, 30); // 10-day short MA, 30-day long MA
    double currentPrice = 100.0; // Starting price
    int days = 100; // Simulate 100 days

    std::cout << "Day\tPrice\tSignal" << std::endl;

    for (int day = 1; day <= days; ++day) {
        // Generate a random price change and update the price
        currentPrice += generateRandomPriceChange();
        strategy.updatePrice(currentPrice);

        // Generate a signal
        std::string signal = strategy.generateSignal();

        // Print the results
        std::cout << day << "\t" << currentPrice << "\t" << signal << std::endl;
    }

    return 0;
}