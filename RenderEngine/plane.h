#pragma once

#include "gl_core_4_5.h"

struct Plane
{
	Plane()
	{
		glGenVertexArrays(1, &vertexArrayObj);
		glBindVertexArray(vertexArrayObj);

		glGenBuffers(1, &vertexBufferObj);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &elementBufferObj);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	~Plane()
	{
		glDeleteVertexArrays(1, &vertexArrayObj);
		glDeleteBuffers(1, &vertexBufferObj);
	}

	GLsizei Size()
	{
		return sizeof(vertices) / sizeof(GLfloat);
	}

	GLsizei VertexCount()
	{
		//return (GLsizei)(sizeof(vertices) / 5 * sizeof(GLfloat));
		return (GLsizei)sizeof(indices);
	}

	void SetActive()
	{
		glBindVertexArray(vertexArrayObj);
	}

	void SetInactive()
	{
		glBindVertexArray(0);
	}

private:
	GLuint vertexArrayObj;
	GLuint vertexBufferObj;
	GLuint elementBufferObj;

	GLfloat vertices[20] = {
		-10.0f,  0.0f,  10.0f,  0.0f, 1.0f,
		-10.0f,  0.0f, -10.0f,  0.0f, 0.0f,
		 10.0f,  0.0f, -10.0f,  1.0f, 0.0f,
		 10.0f,  0.0f,  10.0f,  1.0f, 1.0f
	};

	GLuint indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};
};