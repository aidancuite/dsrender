#include <iostream>

// Use GLFW for surfaces.
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
	glfwSwapInterval(1); //Set 1 cycle minimum swap window inorder to reduce wasted calls.
	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGL(glfwGetProcAddress)){
		std::cerr << "Failed to init OpenGL" << std::endl;
	}
	std::cout << "Initialized OpenGL" << std::endl;

	//Our main loop :)
	double deltaTime = 0;
	double upTime = 0;

	bool first = true;
	while(!glfwWindowShouldClose(window)){  
		std::cout << "Delta T: " << deltaTime << "\n";
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();

		//Time + deltaTime tracking.
		deltaTime = glfwGetTime() - upTime;
		upTime = glfwGetTime();
	}
	
	//Free the window.
	glfwDestroyWindow(window);

	glfwTerminate();
	std::cout << "GLFW Terminated Succesfully" << std::endl;

	return EXIT_SUCCESS;
}