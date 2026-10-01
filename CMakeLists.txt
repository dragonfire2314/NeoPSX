cmake_minimum_required(VERSION 3.20)
project(NeoPSX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GLFW
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(glfw)

# Define Executable
add_executable(NeoPSX 
    src/main.cc
    src/glad.c
)

# Link Libraries
target_link_libraries(NeoPSX PRIVATE glfw ${OPENGL_gl_LIBRARY})
target_include_directories(NeoPSX PRIVATE include)   
