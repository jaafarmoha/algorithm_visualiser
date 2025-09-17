cmake_minimum_required(VERSION 3.10)
project(AlgorithmVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Find GLFW
find_package(glfw3 3.4 REQUIRED)

# Add executable
add_executable(algorithm_visualizer 
    src/main.cpp
    src/glad.c
)

# Link libraries
target_link_libraries(algorithm_visualizer 
    glfw 
    ${GLFW_LIBRARIES}
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${OPENGL_gl_LIBRARY}
)

# Copy GLFW dylib to build directory on macOS
if(APPLE)
    add_custom_command(TARGET algorithm_visualizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/library/libglfw.3.4.dylib
        $<TARGET_FILE_DIR:algorithm_visualizer>
    )
endif()
