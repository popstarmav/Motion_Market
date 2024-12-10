#!/usr/bin/python3
"""
data_processor.py

This module provides functions for processing financial data, such as calculating 
growth rates based on candlestick data.
"""

def calculate_growth(data):
    """
    Calculate growth rates for candlestick data.

    Args:
        data (list of tuple): A list of tuples representing candlestick data
                              in the format (open, high, low, close).

    Returns:
        list of float: A list of growth rates (in percentage) between consecutive
                       candlestick data points.

    Example:
        Input:
            [
                (1.0, 2.0, 0.5, 1.5),
                (1.5, 2.5, 1.0, 2.0),
                (2.0, 3.0, 1.5, 2.5)
            ]
        Output:
            [33.33, 25.00]
    """
    growth_rates = []
    for i in range(1, len(data)):
        prev_close = data[i - 1][3]  # Close price of previous candlestick
        curr_close = data[i][3]     # Close price of current candlestick
        growth = ((curr_close - prev_close) / prev_close) * 100
        growth_rates.append(growth)
    return growth_rates
