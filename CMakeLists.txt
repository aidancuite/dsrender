cmake_minimum_required(VERSION 3.10)
project(DSRender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add GLFW
add_subdirectory(3rdparty/glfw)

# Include directories
include_directories(3rdparty/glfw/include)
include_directories(3rdparty/glfw/deps)
include_directories(3rdparty/glfw/deps/glad)

# Add executable
add_executable(DSRender main.cpp)

# Link libraries
target_link_libraries(DSRender glfw)
if (WIN32)
  target_link_libraries(DSRender opengl32)
else ()
  find_package(OpenGL REQUIRED)
  target_link_libraries(DSRender ${OPENGL_gl_LIBRARY})
endif ()
