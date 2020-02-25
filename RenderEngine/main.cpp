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

	shader_1 = new Shader("./vertexShader_1.glsl", "./fragmentShader_1.glsl");
	shader_2 = new Shader("./vertexShader_2.glsl", "./fragmentShader_2.glsl");
	setupTexture();
	rock_mesh_1.load("./models/Rock_1/Rock.obj", false);
	rock_mesh_2.load("./models/Rock_2/Rock.obj", false);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setDeltaTime();
		processInput();

		setupPhongLighting(shader_1);
		drawFirstRock();

		setupPhongLighting(shader_2);
		shader_2->setFloat("time", glfwGetTime());
		drawSecondRock();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete rock_1_texture;
	delete rock_2_texture;
	delete shader_1;
	delete shader_2;
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

void setupTexture()
{
	rock_1_texture = new Texture("./models/Rock_1/Diffuse.jpg", GL_TEXTURE0);
	rock_2_texture = new Texture("./models/Rock_2/Diffuse.jpg", GL_TEXTURE0);
	
	shader_1->use();
	shader_1->setInt("texture1", 0);

	shader_2->use();
	shader_2->setInt("texture1", 0);
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

void setupPhongLighting(Shader* shader)
{
	shader->use();

	shader->SetVec3("light_1.diffuse", glm::vec3(0.25f, 0.40f, 0.40f));
	shader->SetVec3("light_1.position", glm::vec3(-20.0f, -20.0f, 0.0f));

	shader->SetVec3("light_2.diffuse", glm::vec3(0.8f, 0.2f, 0.2f));
	shader->SetVec3("light_2.position", glm::vec3(20.0f, 20.0f, 0.0f));

	shader_2->SetVec3("viewPos", camera.Position);
}

void drawFirstRock()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(4.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
	shader_1->SetMat4("model", modelMatrix);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader_1->SetMat4("projection", projectionMatrix);

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	shader_1->SetMat4("view", viewMatrix);

	shader_1->use();
	rock_1_texture->SetActive();
	rock_mesh_1.draw();
}

void drawSecondRock()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
	shader_2->SetMat4("model", modelMatrix);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader_2->SetMat4("projection", projectionMatrix);

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	shader_2->SetMat4("view", viewMatrix);

	shader_2->use();
	rock_2_texture->SetActive();
	rock_mesh_2.draw();
}