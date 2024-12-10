#!/usr/bin/python3
"""
candlestick_script.py

This module generates or simulates candlestick data for visualization purposes.
The data is structured as tuples of (open, high, low, close) prices.
"""

def get_candlestick_data():
    """
    Generate candlestick data.

    Returns:
        list of tuple: A list of tuples, where each tuple represents candlestick data
                       in the format (open, high, low, close).

    Example:
        [
            (1.0, 2.0, 0.5, 1.5),
            (1.5, 2.5, 1.0, 2.0),
            ...
        ]
    """
    return [
        (1.0, 2.0, 0.5, 1.5),  # Example candlestick data
        (1.5, 2.5, 1.0, 2.0),
        (2.0, 3.0, 1.5, 2.5),
        (2.5, 3.5, 2.0, 3.0)
    ]
