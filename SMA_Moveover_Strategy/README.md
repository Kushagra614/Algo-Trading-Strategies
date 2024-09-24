# Simple Moving Average (SMA) Trading Strategy



**The Simple Moving Average (SMA) strategy** is one of the most fundamental techniques used in algorithmic trading. It involves calculating the average of an asset's price over a specific period to generate buy or sell signals based on price trends. Here’s a detailed explanation of how it works, along with examples:

---

## **Concept of Simple Moving Average (SMA)**

**Definition:** The SMA is a technical indicator that calculates the average price of an asset over a specified number of periods. It smooths out price data to identify trends by filtering out the day-to-day price fluctuations.

### Formula

For a given window size N and ending index i:

SMA = \frac{1}{N} \sum_{j=i-N+1}^{i} Price[j]

where Price[j] is the price at index j.

## Code Explanation

### Includes and Class Definition

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

class SMATradingStrategy {
  ...
};
```

### Private Members

```cpp
private:
  std::vector<double> stockPrices; // Stock prices
  int shortWindow; // Short-term SMA window
  int longWindow; // Long-term SMA window
  double cash; // Cash balance
  double position; // Number of shares held
```

### Constructor

```cpp
SMATradingStrategy(int shortW, int longW, double startCapital) 
  : shortWindow(shortW), longWindow(longW), cash(startCapital), position(0) {}
```

### Load Stock Prices

```cpp
void loadStockPrices() {
  stockPrices = {100.34, 101.56, 102.78, 103.45, 102.32, 101.50, 104.50, 105.00, 103.00, 104.00, 102.50, 101.50};
}
```

### Calculate SMA

```cpp
double calculateSMA(int windowSize, int endIndex) {
  ...
}
```

### Execute the Strategy

```cpp
void executeStrategy() {
  ...
}
```

### Main Function

```cpp
int main() {
  // Create a strategy with short window 3, long window 5, and initial capital 10000
  SMATradingStrategy strategy(3, 5, 10000.0);
  
  // Load stock prices
  strategy.loadStockPrices();
  
  // Execute the strategy
  strategy.executeStrategy();
  
  return 0;
}
```

## Dry Run

### Stock Prices

100.34, 101.56, 102.78, 103.45, 102.32, 101.50, 104.50, 105.00, 103.00, 104.00, 102.50, 101.50

Short Window: 3, Long Window: 5

### Index 5
- Short SMA: 102.76
- Long SMA: 102.09
- Action: Buy (holding = true, cash = 0, position = 97.47 shares)

### Index 6
- Short SMA: 102.42
- Long SMA: 102.12
- Action: Hold (cash = 0, position = 97.47)

### Index 7
- Short SMA: 103.15
- Long SMA: 102.78
- Action: Hold (cash = 0, position = 97.47)

**Note:** This is a basic implementation of a Simple Moving Average trading strategy. You should not use this code for actual trading without further testing and validation.
