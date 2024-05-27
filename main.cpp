#include <iostream>

// Use GLFW for surfaces.
#define GLFW_INCLUDE_NONE
#include "3rdparty\glfw\deps\glad\gl.h"
#include "3rdparty/glfw/include/GLFW/glfw3.h"

int main() {
	std::cout << "Begin things." << std::endl;

	if(!glfwInit()){
		std::cerr << "Failed to init glfw" << std::endl;
		return EXIT_FAILURE;
	}

	

	glfwTerminate();
	std::cout << "GLFW Terminated Succesfully" << std::endl;

	return EXIT_SUCCESS;
}