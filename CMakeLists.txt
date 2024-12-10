cmake_minimum_required(VERSION 3.10)

# Project Name
project(Motion_Market)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Directories for External Libraries
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)        # Path to GLFW
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/external/glad)        # Path to GLAD
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)      # Path to ImGui
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/external/implot)    # Path to ImPlot
set(PYTHON_DIR ${CMAKE_SOURCE_DIR}/python)             # Path to Python Scripts

# Include Directories
include_directories(${GLFW_DIR}/include)
include_directories(${GLAD_DIR}/include)
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)
include_directories(${IMPLOT_DIR})  # Include ImPlot

# Add ImGui Source Files
set(IMGUI_SRC_FILES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add ImPlot Source Files
set(IMPLOT_SRC_FILES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
    ${IMPLOT_DIR}/implot_demo.cpp
)

# Add Source Files
set(SOURCES
    src/main.cpp
    src/artists.cpp
    src/Market.cpp
    src/RenderGUI.cpp
    src/User.cpp

    # Add GLAD Source File
    ${GLAD_DIR}/src/glad.c

    # Add ImGui Source Files
    ${IMGUI_SRC_FILES}

    # Add ImPlot Source Files
    ${IMPLOT_SRC_FILES}
)

# Create Executable
add_executable(Motion_Market ${SOURCES})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link GLFW and OpenGL
target_link_libraries(Motion_Market PRIVATE
    glfw
    OpenGL::GL
)

# Add GLAD as a Static Library
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
target_link_libraries(Motion_Market PRIVATE glad)
target_link_libraries(Motion_Market PRIVATE glfw OpenGL::GL)

# Add ImPlot as a Static Library
add_library(implot STATIC ${IMPLOT_SRC_FILES})
target_include_directories(implot PUBLIC ${IMPLOT_DIR})
target_link_libraries(Motion_Market PRIVATE implot)

# Add Python Integration
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)  # Ensure Python is available
if (Python3_FOUND)
    message(STATUS "Python3 found: ${Python3_EXECUTABLE}")
    message(STATUS "Python3 include dirs: ${Python3_INCLUDE_DIRS}")
    message(STATUS "Python3 libraries: ${Python3_LIBRARIES}")
    target_include_directories(Motion_Market PRIVATE ${Python3_INCLUDE_DIRS})
    target_link_libraries(Motion_Market PRIVATE ${Python3_LIBRARIES})
else()
    message(FATAL_ERROR "Python3 not found. Please ensure it is installed and available.")
endif()

# Organize Output Binaries
set_target_properties(Motion_Market PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Display Summary
message(STATUS "Project Motion_Market configuration complete.")

