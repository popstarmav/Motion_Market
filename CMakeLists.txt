cmake_minimum_required(VERSION 3.10)

project(Motion_Market)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Manually include GLFW
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)  # Set path to your glfw directory
include_directories(${GLFW_DIR}/include)

# Manually include GLAD
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/external/glad)  # Set path to your glad directory
include_directories(${GLAD_DIR}/include)

# Include ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)  # Set path to your imgui directory
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Set source files
set(SOURCES
    src/main.cpp
    src/artists.cpp
    ${GLAD_DIR}/src/glad.c  # Link the glad source file

    # Add ImGui source files
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Create executable
add_executable(Motion_Market ${SOURCES})

# Link libraries (glfw and OpenGL)
target_link_libraries(Motion_Market PRIVATE
    glfw
    OpenGL::GL
)
