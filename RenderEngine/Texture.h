#pragma once

#include "gl_core_4_5.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Texture
{
	Texture(const char* filePath)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char* data = stbi_load("./UV.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	void SetActive()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void SetInactive()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	GLuint texture;
};