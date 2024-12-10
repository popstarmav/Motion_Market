#include <Python.h>
#include <vector>
#include <tuple>
#include <iostream>
#include "RenderGUI.h"

// Function to fetch candlestick data from Python
std::vector<std::tuple<float, float, float, float>> fetchCandlestickData() {
    Py_Initialize();  // Initialize the Python interpreter

    // Load and execute the candlestick script
    PyObject* module = PyImport_ImportModule("candlestick_script");
    if (!module) {
        PyErr_Print();
        std::cerr << "Failed to import candlestick_script.py\n";
        Py_Finalize();
        return {};
    }

    // Call the function get_candlestick_data
    PyObject* func = PyObject_GetAttrString(module, "get_candlestick_data");
    if (!func || !PyCallable_Check(func)) {
        PyErr_Print();
        std::cerr << "Failed to find get_candlestick_data function\n";
        Py_DECREF(module);
        Py_Finalize();
        return {};
    }

    PyObject* result = PyObject_CallObject(func, nullptr);
    if (!result || !PyList_Check(result)) {
        PyErr_Print();
        std::cerr << "Function call failed\n";
        Py_DECREF(func);
        Py_DECREF(module);
        Py_Finalize();
        return {};
    }

    // Parse the result into a C++ vector
    std::vector<std::tuple<float, float, float, float>> data;
    for (Py_ssize_t i = 0; i < PyList_Size(result); i++) {
        PyObject* tuple = PyList_GetItem(result, i);
        if (!PyTuple_Check(tuple) || PyTuple_Size(tuple) != 4) {
            std::cerr << "Invalid tuple format in Python data\n";
            continue;
        }
        float open = static_cast<float>(PyFloat_AsDouble(PyTuple_GetItem(tuple, 0)));
        float high = static_cast<float>(PyFloat_AsDouble(PyTuple_GetItem(tuple, 1)));
        float low = static_cast<float>(PyFloat_AsDouble(PyTuple_GetItem(tuple, 2)));
        float close = static_cast<float>(PyFloat_AsDouble(PyTuple_GetItem(tuple, 3)));
        data.emplace_back(open, high, low, close);
    }

    Py_DECREF(result);
    Py_DECREF(func);
    Py_DECREF(module);
    Py_Finalize();  // Shut down the Python interpreter

    return data;
}

int main() {
    // Fetch data from Python
    auto candlestickData = fetchCandlestickData();
    if (candlestickData.empty()) {
        std::cerr << "No data fetched. Exiting program.\n";
        return -1;
    }

    // Render GUI with ImPlot
    RenderGUI gui;
    gui.run(candlestickData);

    return 0;
}

