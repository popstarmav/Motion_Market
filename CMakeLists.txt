cmake_minimum_required(VERSION 3.10)

# Project configuration
project(Motion_Market VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict warnings for code quality
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Define external library directories
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/external/implot)

# Define ImGui and ImPlot source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)

# Define project source and header files
set(PROJECT_SOURCES
    src/Token.cpp
    src/FakeDataGenerator.cpp
    src/ImGuiSetup.cpp
    src/Market.cpp
    src/UserProfile.cpp
    src/main.cpp
)

set(PROJECT_HEADERS
    src/Token.h
    src/FakeDataGenerator.h
    src/ImGuiSetup.h
    src/Market.h
    src/UserProfile.h
)

# Include directories
include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMPLOT_DIR}
    src
)

# Add the main executable
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${IMGUI_SOURCES}
    ${IMPLOT_SOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
)

message(STATUS "CMake configuration complete for project ${PROJECT_NAME}")

