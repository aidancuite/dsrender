#include "ShaderMap.hpp"

void ShaderMap::showShaders(){
	for(const auto& shader : shaderMap){
		std::cout << shader.first.name << ", Size: " << shader.second.size() << std::endl;
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

void ShaderMap::addShader(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return;
    }
    std::stringstream buf;
    buf << file.rdbuf();
    size_t lastDot = filePath.find_last_of('.');
    size_t lastSlash = filePath.find_last_of('/') + 1;
    std::string name = filePath.substr(lastSlash, lastDot - lastSlash);
    std::string extension = filePath.substr(lastDot + 1);
    ShaderType type = getTypeFromExtension(extension);

    ShaderKey key = {name, type};
    auto shaderCode = std::make_unique<char[]>(buf.str().length() + 1);
    strcpy(shaderCode.get(), buf.str().c_str());

    // Store in both maps
    shaderPointerMap[key] = (const GLchar* const*)shaderCode.get();
    shaderMap[key] = buf.str();
}

const GLchar* const* ShaderMap::getShader(std::string name, ShaderType type){
	ShaderKey key = {name, type};
	auto it = shaderPointerMap.find(key);
	return it != shaderPointerMap.end() ? it->second : nullptr;
}