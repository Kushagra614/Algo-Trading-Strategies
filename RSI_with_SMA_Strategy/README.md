# RSI Strategy with SMA

This repository contains a C++ implementation of a trading strategy using the Relative Strength Index (RSI) and Simple Moving Average (SMA) indicators.

## Table of Contents
- [Introduction](#introduction)
- [Indicators](#indicators)
  - [RSI (Relative Strength Index)](#rsi-relative-strength-index)
  - [SMA (Simple Moving Average)](#sma-simple-moving-average)
- [Implementation](#implementation)
  - [Class: TradingIndicators](#class-tradingindicators)
  - [Methods](#methods)
- [Usage](#usage)
- [Example](#example)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project implements a trading strategy that combines the Relative Strength Index (RSI) and Simple Moving Average (SMA) indicators. These technical analysis tools are commonly used by traders to identify potential buy and sell signals in financial markets.

## Indicators

### RSI (Relative Strength Index)

RSI is a momentum oscillator that measures the speed and change of price movements. It oscillates between 0 and 100 and is used to identify overbought or oversold conditions of a stock or asset.

- **Overbought**: RSI value > 70, indicating that the asset might be overvalued and a price drop could be due.
- **Oversold**: RSI value < 30, indicating that the asset might be undervalued and a price increase could be expected.

#### RSI Formula

```
RSI = 100 - (100 / (1 + RS))
Where:
RS = Average Gain / Average Loss
```

This can also be expressed as:

```
RSI = 100 - (100 / (1 + (Average Gain / Average Loss)))
```

### SMA (Simple Moving Average)

SMA is a basic technical analysis tool that smooths out price data by calculating the average price over a specific number of periods.

## Implementation

### Class: TradingIndicators

The `TradingIndicators` class encapsulates the logic for calculating both RSI and SMA.

#### Properties:
- `prices`: Vector to store historical prices
- `smaWindow`: Window size for SMA calculation
- `rsiWindow`: Window size for RSI calculation

### Methods

1. **Constructor**
   ```cpp
   TradingIndicators(int smaWindow, int rsiWindow)
   ```

2. **updatePrice**
   ```cpp
   void updatePrice(double price)
   ```
   Adds a new price to the history and maintains the size of the price list.

3. **calculateSMA**
   ```cpp
   double calculateSMA()
   ```
   Calculates the Simple Moving Average over the last `smaWindow` prices.

4. **calculateRSI**
   ```cpp
   double calculateRSI()
   ```
   Calculates the Relative Strength Index over the last `rsiWindow` prices.

## Usage

To use this strategy in your C++ project:

1. Include the necessary headers:
   ```cpp
   #include <iostream>
   #include <vector>
   #include <numeric>
   #include <cmath>
   ```

2. Create an instance of `TradingIndicators`:
   ```cpp
   const int SMA_WINDOW = 5;
   const int RSI_WINDOW = 14;
   TradingIndicators indicators(SMA_WINDOW, RSI_WINDOW);
   ```

3. Update prices and calculate indicators:
   ```cpp
   double price = 100.0;
   indicators.updatePrice(price);
   double sma = indicators.calculateSMA();
   double rsi = indicators.calculateRSI();
   ```

## Example

Here's a simple example of how to use the `TradingIndicators` class:

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





