// This class reads in shaders contained within shaders, and then maps them by name + type,
// Eg, test.frag would be stored in (test, frag) -> shadercode, and test.vert would be stored at (test, vert)

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <cstring>

// Use GLFW for surfaces.
#include <glad/gl.h>

enum class ShaderType {
	Unknown,
	Vertex,
	Fragment
};

static ShaderType getTypeFromExtension(const std::string& extension){
	if(extension == "vert") return ShaderType::Vertex;
	if(extension == "frag") return ShaderType::Fragment;
	return ShaderType::Unknown;
}

struct ShaderKey {
	std::string name;
	ShaderType type;

	//Comparison operator for shaderkey type for map.
	bool operator<(const ShaderKey& other) const {
		if(name == other.name){
			return type < other.type;
		}
		return name < other.name;
	}
};

class ShaderMap {
private:
	// Map of ShaderKey to shader code
	std::map<ShaderKey, std::string> shaderMap;
	std::map<ShaderKey, const GLchar* const*> shaderPointerMap;

public:
	void showShaders();
	// std::map<ShaderKey, std::unique_ptr<const char[]>> getMap(){return shaderMap;};

	std::string loadShaderFromFile(const std::string& filePath);
	void addShader(const std::string& filePath);

	const GLchar* const* getShader(std::string name, ShaderType type); //Look up specific shader
};