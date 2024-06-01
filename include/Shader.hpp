#pragma once

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Shader class jacked from learnopengl.com
class Shader {
public:
    // This is where the compiled shaders are linked to. 
	// Each shader has a vertex and fragment shader linked to its ID.
    GLuint ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use() { glUseProgram(ID); };
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};