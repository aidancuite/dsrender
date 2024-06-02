#include "DSEngine.hpp" //This will contain the main "engine" that we call run.

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"

int main() {
	DSEngine engine;

	engine.run();

	return EXIT_SUCCESS;
}