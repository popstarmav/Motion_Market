cmake_minimum_required(VERSION 3.14)
project(flutter_application_1 LANGUAGES CXX)

# Add your C++ source files
add_library(flutter_application_1 SHARED
    blockchain.cpp
    graph.cpp
    main.cpp
)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Link the library
target_link_libraries(flutter_application_1 PRIVATE flutter)

# Set the output directory for the shared library
set_target_properties(flutter_application_1 PROPERTIES
    OUTPUT_NAME "flutter_application_1"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

