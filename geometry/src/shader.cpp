#define GLEW_STATIC
#include "GL/glew.h"

#include <iostream>
#include <fstream>

#include "shader.h"

// TODO: in production, make ship shaders inside executable

void readFileToString(std::string& str, std::ifstream& file) {
	file.seekg(0, std::ios::end);
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	str.assign((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
}

namespace Geometry {

Shader::Shader(): id(glCreateProgram()) {}
Shader::Shader(const GLchar* vertexName,const GLchar* fragmentName): id(glCreateProgram()) {
	this->useShader(vertexName  , GL_VERTEX_SHADER  );
	this->useShader(fragmentName, GL_FRAGMENT_SHADER);
	this->link();
}
Shader::~Shader() {
	glDeleteProgram(id);
}
void Shader::use() {
	glUseProgram(id);
}
void Shader::link() const {
	GLint success;
	char infoLog[512];
	glLinkProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		std::cout << "Shader program error!\n" << infoLog << "\n";
	}

}
void Shader::useShader(const GLchar* fileName, int type) const {
	std::string shaderPath = "./shaders/";
	shaderPath += fileName;

	std::ifstream shaderFile(shaderPath);
	GLint success;
	char infoLog[512];
	std::string str;
	const char* source;
	readFileToString(str, shaderFile);
	source = str.c_str();
	int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	// TODO: exceptions
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader comilation error!\n" << infoLog << "\n";
	}
	glAttachShader(this->id, shader);
	glDeleteShader(shader);
	shaderFile.close();
}
void Shader::setBool  (const char *name, bool      value ) const {
	glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}
void Shader::setInt   (const char* name, int       value ) const {
	glUniform1i(glGetUniformLocation(this->id, name), value);
}
void Shader::setFloat (const char* name, float     value ) const {
	glUniform1f(glGetUniformLocation(this->id, name), value);
}
void Shader::setMat2 (const char* name, float* mat2x2  ) const {
	glUniformMatrix2fv(glGetUniformLocation(this->id, name), 1, GL_TRUE, mat2x2);
}
void Shader::setMat3 (const char* name, float* mat3x3  ) const {
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_TRUE, mat3x3);
}
void Shader::setMat4 (const char* name, float* mat4x4  ) const {
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_TRUE, mat4x4);
}
void Shader::setVec2 (const char* name, float* vec2    ) const {
	glUniform2fv(glGetUniformLocation(this->id, name), 1, vec2);
}
void Shader::setVec3 (const char* name, float* vec3    ) const {
	glUniform3fv(glGetUniformLocation(this->id, name), 1, vec3);
}

}; // namespace Geometry