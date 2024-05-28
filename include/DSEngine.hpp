#pragma once

#include <iostream>
#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ShaderMap.hpp"

struct ImGuiContext;

class DSEngine {
private:
	GLFWwindow* window;
	ShaderMap shaderMap; //Map from shader key to the glsl code.

	bool showDebug;

	// Callbacks for GLFW
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void toggleDebug(){ showDebug = !showDebug; std::cout << "Toggle Debug" << std::endl; };

	uint8_t init();
	uint8_t cleanup();

public:
	DSEngine();
	~DSEngine();

	//Main run loop method. Contains loop.
	uint8_t run();
};