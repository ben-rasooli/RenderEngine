#include "gl_core_4_5.h"
#include "glm.hpp"
#include "ext.hpp"
#include "glfw3.h"
#include <iostream>
#include <stdlib.h>
#include "Shader.h"
#include "Geometry.h"
#include "Texture.h"

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

	Geometry geometry;
	Texture texture("./UV.png");
	Shader shader("./vertexShader.glsl", "./fragmentShader.glsl");

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		texture.SetActive();
		shader.use();
		geometry.SetActive();
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		/*double mousePos_X;
		double mousePos_Y;
		glfwGetCursorPos(window, &mousePos_X, &mousePos_Y);
		GLfloat greenColor = sin((float)mousePos_X);
		GLfloat blueColor = sin((float)mousePos_Y);
		shader.setFloat("variableColorG", greenColor);
		shader.setFloat("variableColorB", blueColor);*/
		glDrawElements(GL_TRIANGLES, geometry.Size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}