#include "ShaderMap.hpp"

void ShaderMap::showShaders(){
	for(const auto& shader : shaderMap){
		std::cout << shader.first.name << ", " << (int)shader.first.type << ", Size: " << shader.second.size() << std::endl;
	}
}

std::string ShaderMap::loadShaderFromFile(const std::string& filePath){
	std::ifstream file(filePath);
	if(!file){
		std::cerr << "Could not open file: " << filePath << std::endl;
		return "";
	}
	std::stringstream buf;
	buf << file.rdbuf();
	std::cout << "Loaded shader at " << filePath << "\n\t" << "Size: " << buf.str().size() << std::endl;
	return buf.str();
}

void ShaderMap::addShader(const std::string& filePath){
	std::cout << "Adding " << filePath << " to shader map" << std::endl;
	size_t lastDot = filePath.find_last_of('.');
	size_t lastSlash = filePath.find_last_of('/') + 1;
	if(lastSlash >= filePath.size()){
		lastSlash = 0;
		std::cout << "Failed to find last slash in shader path" << std::endl;
		return;
	}

	if(lastDot == filePath.size() - 1){
		lastDot = 0;
		std::cout << "Failed to find last dot in shaderPath" << std::endl;
		return;
	}

	std::string name = filePath.substr(lastSlash, lastDot);
	std::string extension = filePath.substr(lastDot + 1);
	ShaderType type = getTypeFromExtension(extension);

	ShaderKey key = {name, type};
	shaderMap[key] = loadShaderFromFile(filePath);
}

std::string ShaderMap::getShader(std::string name, ShaderType type){
	ShaderKey key = {name, type};
	return shaderMap[key];
}

std::vector<std::pair<ShaderKey, std::string>> ShaderMap::getShadersByType(ShaderType type){
	std::vector<std::pair<ShaderKey, std::string>> ret;

	for(auto const& shader : shaderMap){
		if(shader.first.type == type){
			ret.push_back(shader);
		}
	}

	return ret;
}