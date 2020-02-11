#pragma once

#include "gl_core_4_5.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	GLuint programId;

	Shader(const char* vShaderPath, const char* fShaderPath)
	{
		ifstream vShaderFile(vShaderPath);
		ifstream fShaderFile(fShaderPath);

		if (!vShaderFile.is_open() && !fShaderFile.is_open())
			throw "Could not Load File";
		
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		std::string vShaderString = vShaderStream.str();
		std::string fShaderString = fShaderStream.str();
		
		const char* vShaderCode = vShaderString.c_str();
		const char* fShaderCode = fShaderString.c_str();

		vShaderFile.close();
		fShaderFile.close();

		GLuint vertexShader, fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");

		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);
		glLinkProgram(programId);
		checkCompileErrors(programId, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void use()
	{
		glUseProgram(programId);
	}

	void setBool(const string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
	}

	void setInt(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
	}

	void setFloat(const string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
	}

private:
	// checking shader compilation/linking errors.
	void checkCompileErrors(GLuint program, string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(program, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(program, 1024, NULL, infoLog);
				cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			}
		}
		else
		{
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 1024, NULL, infoLog);
				cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			}
		}
	}
};