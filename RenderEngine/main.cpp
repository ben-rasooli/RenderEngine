#include "mainDetails.h"

int main()
{
	if (!glfwInit())
		return -1;

	setupGLFW();

	if (!canCreateWindow())
		return -2;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	setupInput();

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwTerminate();
		return -3;
	}

	glEnable(GL_DEPTH_TEST);

	shader = new Shader("./vertexShader.glsl", "./fragmentShader.glsl");
	setupTextures();
	plane = new Plane();
	rock_mesh_1.load("./models/Rock_Set/Rock_2/Rock_2.obj", false);
	rock_mesh_2.load("./models/Rock_Set/Rock_5/Rock_5.obj", false);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setDeltaTime();
		processInput();

		shader->use();
		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("lightPos", glm::vec3(20.0f, 20.0f, 20.0f));
		shader->SetVec3("viewPos", camera.Position);

		plane->SetActive();
		glDrawElements(GL_TRIANGLES, plane->VertexCount(), GL_UNSIGNED_INT, 0);
		drawFirstRock();
		drawSecondRock();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete plane;
	delete texture_main;
	delete texture_dirt;
	delete shader;
	glfwTerminate();
	return 0;
}

void setupGLFW()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool canCreateWindow()
{
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Render Engine", NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

void setDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void setupTextures()
{
	texture_main = new Texture("./textures/Gray.jpg", GL_TEXTURE0);
	texture_dirt = new Texture("./textures/DirtTexture.jpg", GL_TEXTURE1);

	shader->use();
	shader->setInt("texture1", 0);
	//shader->setInt("texture2", 1);
	texture_main->SetActive();
	//texture_dirt->SetActive();
}

void setupInput()
{
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void drawFirstRock()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(4.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
	shader->SetMat4("model", modelMatrix);

	setVPTransformationMatrices();
	rock_mesh_1.draw();
}

void drawSecondRock()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
	shader->SetMat4("model", modelMatrix);

	setVPTransformationMatrices();
	rock_mesh_2.draw();
}

void setVPTransformationMatrices()
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader->SetMat4("projection", projectionMatrix);

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	shader->SetMat4("view", viewMatrix);
}