#pragma once

#include "gl_core_4_5.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Texture
{
	Texture(const char* filePath, GLenum textureUnit)
	{
		_textureUnit = textureUnit;
		glGenTextures(1, &_texture);
		glActiveTexture(_textureUnit);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	~Texture()
	{
		glDeleteTextures(1, &_texture);
	}

	void SetActive()
	{
		glActiveTexture(_textureUnit);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	void SetInactive()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	GLuint _texture;
	GLenum _textureUnit;
};