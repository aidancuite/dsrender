cmake_minimum_required(VERSION 3.10)
project(DSRender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui)
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw)
set(GLM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm)

include_directories(
	${IMGUI_DIR}
	${IMGUI_DIR}/backends
	${GLFW_DIR}/include
	${GLFW_DIR}/deps
	${GLFW_DIR}/deps/glad
	${GLM_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${IMGUI_DIR}/*.h)
file(GLOB IMGUI_BACKENDS ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add CmakeLists.txt subdirectories. This handles building glfw
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glm)

# Add executable
add_executable(DSRender main.cpp ${IMGUI_SOURCES} ${IMGUI_BACKENDS} ${SOURCES})

# Link libraries
target_link_libraries(DSRender glfw)
if (WIN32)
  target_link_libraries(DSRender opengl32)
else ()
  find_package(OpenGL REQUIRED)
  target_link_libraries(DSRender ${OPENGL_gl_LIBRARY})
endif ()
