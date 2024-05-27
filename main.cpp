#include <iostream>

// Use GLFW for surfaces.
#define GLFW_INCLUDE_NONE
#include "3rdparty\glfw\deps\glad\gl.h"
#include "3rdparty/glfw/include/GLFW/glfw3.h"

// #include "glfwManager.hpp"
#include "stdio.h"

// Error callback for glfw.
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main() {
	std::cout << "Begin things." << std::endl;

	glfwSetErrorCallback(error_callback);

	if(!glfwInit()){
		std::cerr << "Failed to init glfw" << std::endl;
		return EXIT_FAILURE;
	}

	//Create the glfw window. Require at least OpenGL 2.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(640, 480, "DSRender", NULL, NULL);
	if(!window){
		std::cerr << "Failed to init glfwWindow" << std::endl;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGL(glfwGetProcAddress)){

	}

	//Our main loop :)
	bool first = true;
	while(!glfwWindowShouldClose(window)){
		if(first){
			std::cout << "Entered main loop" << std::endl;
			first = false;
		}
		
	}
	
	//Free the window.
	glfwDestroyWindow(window);

	glfwTerminate();
	std::cout << "GLFW Terminated Succesfully" << std::endl;

	return EXIT_SUCCESS;
}