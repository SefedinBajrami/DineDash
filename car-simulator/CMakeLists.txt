cmake_minimum_required(VERSION 3.10)
project(CarSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLFW
find_package(glfw3 REQUIRED)

# Add GLM
find_package(glm REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/shader.cpp
    src/camera.cpp
    src/car.cpp
    src/environment.cpp
    src/glad.c
)

# Create executable
add_executable(CarSimulator ${SOURCES})

# Link libraries
target_link_libraries(CarSimulator 
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})
