# RSI Strategy (Relative Strength Index) with SMA

## Introduction

RSI (Relative Strength Index) is a momentum oscillator used in technical analysis to measure the speed and change of price movements. It oscillates between 0 and 100 and helps identify overbought or oversold conditions of a stock or asset.

- **Overbought**: RSI value > 70, indicating that the asset might be overvalued and a price drop could be due.
- **Oversold**: RSI value < 30, indicating that the asset might be undervalued and a price increase could be expected.

## How RSI Works

RSI is calculated based on the average gains and average losses over a specified period (typically 14 days).

- **Gain**: The price difference when a stock closes higher than the previous day.
- **Loss**: The price difference when a stock closes lower than the previous day.

### RSI Formula

```
RSI = 100 - (100 / (1 + RS))
```

Where:
RS = Average Gain / Average Loss

This formula can also be expressed as:
```
RSI = 100 - (100 / (1 + (Average Gain / Average Loss)))
```

## Interpretation of RSI

- An RSI value above 70 is generally considered overbought.
- An RSI value below 30 is generally considered oversold.
- The RSI can remain in overbought or oversold territory for extended periods during strong trends.
- Divergences between the RSI and price action can signal potential trend reversals.

## Combining RSI with SMA

When using RSI in conjunction with SMA (Simple Moving Average), traders often look for:

1. **Confirmation**: When the price crosses above or below the SMA, they may look to the RSI for confirmation of the trend.
2. **Divergence**: If the price is making new highs or lows, but the RSI is not, this could signal a potential trend reversal.
3. **Support/Resistance**: The SMA can act as a support or resistance level, and traders might use RSI to gauge the strength of price reactions at these levels.

Remember that while these indicators can be powerful tools, they should be used in conjunction with other forms of analysis and risk management strategies for optimal trading decisions.

## Trading Indicators: SMA and RSI Explanation

Let's break down the code and logic behind calculating Simple Moving Average (SMA) and Relative Strength Index (RSI). We'll explain how it works, why certain formulas are used, and what happens in a dry run.

### Code Explanation

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
```

- `iostream` is used for input/output operations.
- `vector` is a dynamic array where we store prices.
- `numeric` provides functions like accumulate to sum up elements.
- `cmath` provides mathematical functions like abs, pow, etc.

### Class Definition: TradingIndicators

```cpp
class TradingIndicators {
private:
    std::vector<double> prices;
    int smaWindow, rsiWindow;
```

- `prices`: This vector stores the historical prices. Each new price is added at the end, and we maintain a history to calculate indicators like SMA and RSI.
- `smaWindow`: The window size for calculating the Simple Moving Average (SMA), typically set to 5.
- `rsiWindow`: The window size for Relative Strength Index (RSI), typically set to 14.

### Constructor

```cpp
public:
    TradingIndicators(int smaWindow, int rsiWindow)
        : smaWindow(smaWindow), rsiWindow(rsiWindow) {}
```

Constructor initializes the window sizes (for both SMA and RSI). We pass these sizes when we create an object of this class.

### updatePrice Method

```cpp
void updatePrice(double price) {
    prices.push_back(price);  // Add new price to the list
    if (prices.size() > std::max(smaWindow, rsiWindow)) {
        prices.erase(prices.begin());  // Keep only necessary prices
    }
}
```

**Purpose**: This function is called every time a new price comes in.

- It adds the latest price to the vector.
- If the number of stored prices exceeds the maximum required window size (either for SMA or RSI), it removes the oldest price. This keeps the price list within bounds and avoids unnecessary memory usage.

**Logic**: We only need to keep track of the last max(smaWindow, rsiWindow) prices to calculate SMA and RSI efficiently. Keeping extra data would be wasteful.

### SMA Calculation

```cpp
double calculateSMA() {
    if (prices.size() < smaWindow) return 0.0;  // Not enough data yet

    double sum = std::accumulate(prices.end() - smaWindow, prices.end(), 0.0);
    return sum / smaWindow;
}
```

**Purpose**: This function calculates the Simple Moving Average (SMA) over the last smaWindow prices.

- `accumulate`: Sums up the last smaWindow prices (from prices.end() - smaWindow to prices.end()).

**Why use this formula?**: The SMA is calculated as the average of the prices over a fixed number of days. This smooths out the price movements, making it easier to spot trends.

**Dry Run for SMA**:

Assume smaWindow = 5 and prices are [100, 102, 104, 105, 106].
The sum of the last 5 prices: 100 + 102 + 104 + 105 + 106 = 517.
SMA = 517 / 5 = 103.4.

### RSI Calculation

```cpp
double calculateRSI() {
    if (prices.size() < rsiWindow + 1) return 0.0;  // Not enough data

    double gain = 0.0, loss = 0.0;

    for (int i = prices.size() - rsiWindow; i < prices.size(); ++i) {
        double change = prices[i] - prices[i - 1];
        if (change > 0) gain += change;
        else loss -= change;
    }
```

**Purpose**: The RSI is calculated based on the price changes (gains and losses) over the last rsiWindow periods.

**Logic**:

- If the price increases from the previous day, it's considered a gain.
- If the price decreases, it's considered a loss.
- Gains and losses are accumulated over the RSI window.

**Why This Formula?**
RSI tracks the momentum of the price, so we need to know how much the price is going up or down relative to previous periods. By calculating the average gain and average loss, we can tell whether the market is overbought or oversold.

Continuing RSI Calculation:

```cpp
    double avgGain = gain / rsiWindow;
    double avgLoss = loss / rsiWindow;

    if (avgLoss == 0) return 100.0;  // No losses, RSI is 100

    double rs = avgGain / avgLoss;
    return 100 - (100 / (1 + rs));
}
```

- `avgGain` and `avgLoss`: Average gain and loss over the window.
- RS (Relative Strength): The ratio of average gain to average loss.
  - If the market is consistently gaining, RS > 1.
  - If the market is consistently losing, RS < 1.

**RSI Formula**:

```
RSI = 100 - (100 / (1 + RS))
```

- If RS is high, RSI approaches 100, indicating an overbought condition.
- If RS is low, RSI approaches 0, indicating an oversold condition.

**Dry Run for RSI**:

Suppose prices are [100, 102, 101, 103, 104] with rsiWindow = 4.
Price changes: [+2, -1, +2, +1].

Gains = 2 + 2 + 1 = 5.
Losses = 1.
avgGain = 5 / 4 = 1.25.
avgLoss = 1 / 4 = 0.25.

RS = 1.25 / 0.25 = 5.
RSI = 100 - (100 / (1 + 5)) = 83.33 (indicating a strong uptrend).

### Main Function and Dry Run

```cpp
int main() {
    const int SMA_WINDOW = 5;
    const int RSI_WINDOW = 14;
    TradingIndicators indicators(SMA_WINDOW, RSI_WINDOW);

    std::vector<double> priceData = {100, 102, 101, 105, 110, 108, 107, 106, 111, 115, 113, 112, 114, 116, 118};

    for (double price : priceData) {
        indicators.updatePrice(price);

        double sma = indicators.calculateSMA();
        double rsi = indicators.calculateRSI();

        std::cout << "Price: " << price
                  << ", SMA(" << SMA_WINDOW << "): " << sma
                  << ", RSI(" << RSI_WINDOW << "): " << rsi
                  << std::endl;
    }

    return 0;
}
```

`priceData` contains a list of prices over time.
For each price, we update the prices in the indicator object and calculate the SMA and RSI.

**What Happens During a Dry Run?**

Initially: The SMA and RSI cannot be calculated because there aren't enough prices (fewer than SMA_WINDOW or RSI_WINDOW).
As more prices come in: Once the number of prices is at least SMA_WINDOW and RSI_WINDOW, the calculations begin. For each new price:

- SMA is calculated as the average of the last 5 prices.
- RSI is calculated as the ratio of average gains to average losses.

For example:

On day 5, with prices [100, 102, 101, 105, 110]:

- SMA: The average of [100, 102, 101, 105, 110] is 103.6.
- RSI: We have price changes of +2, -1, +4, +5, resulting in an RSI calculation.

## Conclusion

This code allows you to simulate and calculate two key trading indicators:

- SMA smooths price trends.
- RSI detects momentum shifts in the market. Both are used by traders to make buy/sell decisions.