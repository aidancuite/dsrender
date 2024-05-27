cmake_minimum_required(VERSION 3.10)
project(DSRender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui)
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)

file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${IMGUI_DIR}/*.h)
file(GLOB IMGUI_BACKENDS ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

# Add CmakeLists.txt subdirectories.
add_subdirectory(3rdparty/glfw)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/deps/glad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui/backends)

# Add executable
add_executable(DSRender main.cpp ${IMGUI_SOURCES} ${IMGUI_BACKENDS})

# Link libraries
target_link_libraries(DSRender glfw)
if (WIN32)
  target_link_libraries(DSRender opengl32)
else ()
  find_package(OpenGL REQUIRED)
  target_link_libraries(DSRender ${OPENGL_gl_LIBRARY})
endif ()
