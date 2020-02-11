#include "gl_core_4_5.h"
#include "glm.hpp"
#include "ext.hpp"
#include "glfw3.h"
#include <iostream>
#include <stdlib.h>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Render Engine", NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwTerminate();
		return -3;
	}

	Shader shader("./vertexShader.glsl", "./fragmentShader.glsl");

	// data - vertices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,		0.8f, 0.5f, 0.2f,
		-0.5f,  0.5f, 0.0f,		0.2f, 0.9f, 0.8f,
		 0.5f,  0.5f, 0.0f,		0.5f, 0.2f, 0.5f,
		 0.5f, -0.5f, 0.0f,		0.3f, 0.0f, 0.3f
	};
	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLuint vertexArrayObjId;
	glGenVertexArrays(1, &vertexArrayObjId);
	glBindVertexArray(vertexArrayObjId);

	GLuint vertexBufferObjId;
	glGenBuffers(1, &vertexBufferObjId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	GLuint elementBufferObjId;
	glGenBuffers(1, &elementBufferObjId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glBindVertexArray(vertexArrayObjId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjId);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLfloat greenColor = sin(glfwGetTime()) / 2.0f + 0.5f;
		shader.setFloat("variableColorG", greenColor);
		glDrawElements(GL_TRIANGLES, sizeof(vertices) / sizeof(GLfloat), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayObjId);
	glDeleteBuffers(1, &vertexBufferObjId);

	glfwTerminate();
	return 0;
}