#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// -----------------------------------------------------------------------
	Shader(const char* vtxShaderSource, const char* fragShaderSource)
	{

		// Create shader program object
		ID = glCreateProgram();

		// Create shader objects
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		// Get shader sources
		glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
		glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

		// Compile the vertex shader and print compilation errors
		glCompileShader(vertexShaderId);
		checkCompileErrors(vertexShaderId, "vertex");

		// Compile fragment shader
		glCompileShader(fragmentShaderId);
		checkCompileErrors(fragmentShaderId, "fragment");

		// Attach compiled shaders to program
		glAttachShader(ID, vertexShaderId);
		glAttachShader(ID, fragmentShaderId);

		// Link shader program
		glLinkProgram(ID);
		checkCompileErrors(ID, "app");

	}
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(GLuint shaderID, std::string shader)
	{
		GLint success;
		GLchar infoLog[1024];

		if (shader == "vertex") {
			// Check for shader compile errors
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << stderr << "\n" << infoLog << std::endl;
				return;
			}
		}
		else if (shader == "fragment") {
			// Check for shader compile errors
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				return;
			}
		} 
		else {
			// Check linking errors
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << stderr << "\n" << infoLog << std::endl;
				return;
			}
		}
	}
};
#endif
