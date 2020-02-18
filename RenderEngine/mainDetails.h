#pragma once

#include "gl_core_4_5.h"
#include "glm.hpp"
#include "ext.hpp"
#include "glfw3.h"
#include <iostream>
#include <stdlib.h>
#include "Shader.h"
#include "plane.h"
#include "texture.h"
#include "camera.h"
#include "OBJMesh.h"

void setDeltaTime();
void setupGLFW();
bool canCreateWindow();
void setupInput(GLFWwindow* window);
void setupTextures(Shader& shader);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void setTransformationMatrices(Shader& shader);
