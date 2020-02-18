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
void setupInput();
void setupTextures();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput();
void setTransformationMatrices();

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

GLFWwindow* window;
Shader* shader;
Texture* texture_main;
Texture* texture_dirt;
Plane* plane;
OBJMesh mesh;

// camera
Camera camera(glm::vec3(0.0f, 15.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;