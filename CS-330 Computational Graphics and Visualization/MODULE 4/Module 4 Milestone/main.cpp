#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "stb_image.h"
#include "common/controls.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "cylinder.h"
#include "shader.h"
#include "camera.h"


// Shader Program
//----------------------------------
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Shader Source Code
// ---------------------------------------------
const char* vertexShaderSource = GLSL(440,
	layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vertexColor = color;
}
);

// Fragment Shader Source Code
const char* fragmentShaderSource = GLSL(440,
	in vec4 vertexColor;
out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(vertexColor);
}
);

namespace {
	glm::vec3 cameraPos = glm::vec3(-4.71f, 0.41f, 6.30f);
	glm::vec3 cameraFront = glm::vec3(0.66f, 1.65f, -0.75f);
	glm::vec3 cameraUp = glm::vec3(1.089f, 1.0f, 1.234f);

}

// Functions
// --------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);
void ChangeView();
//unsigned int LoadTexture(const char* path);

// Settings
// --------------------------------------------------
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Camera
// --------------------------------------------------
Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
// --------------------------------------------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Program Entry Point
// --------------------------------------------------
int main() {


	// GLFW: Initialize & Configure
	// --------------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW: Window Creation
	// --------------------------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Function Callbacks
	// --------------------------------------------------
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	//glfwSetKeyCallback(window, KeypressCallback);

	// Set Input Mode & Load OpenGL
	// --------------------------------------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// OpenGL: Configure state
	// --------------------------------------------------
	glEnable(GL_DEPTH_TEST);

	// Build & Compile Shader Program
	// --------------------------------------------------
	Shader appShader(vertexShaderSource, fragmentShaderSource);

	// Pyramid: Creation of pyramid
	// --------------------------------------------------
	float pyramid[] = {
		// Front Face
		0.0f,	 1.0f,	0.0f,	0.18f,	0.49f,	0.2f,	1.f, // Top Light Green Vertex 0 
	   -1.0f,	-1.0f,	1.0f,	0.27f,	0.63f,	0.29f,	1.f, // Front Left Green Vertex 1
		1.0f,	-1.0f,	1.0f,	0.27f,	0.63f,	0.29f,	1.f, // Front Right Green Vertex 2

		// Right Face
		0.0f,	 1.0f,	0.0f,	0.27f,	0.63f,	0.29f,	1.f, // Top Light Green Vertex 0 
		1.0f,	-1.0f,	1.0f,	0.18f,	0.49f,	0.2f,	1.f, // Front Right Dark Green Vertex 2
		1.0f,	-1.0f, -1.0f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 3

		// Back Face
		0.0f,	1.0f,	0.0f,	0.51f,	0.78f,	0.52f,	1.f, // Top Light Green Vertex 0 
		1.0f,  -1.0f,  -1.0f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 3
	   -1.0f,  -1.0f,  -1.0f,	0.3f,	0.69f,	0.31f,	1.f,  // Back Dark Medium Green Vertex 4

	   // Left Face
	   0.0f,	1.0f,	0.0f,	0.51f,	0.78f,	0.52f,	1.f, // Top Light Green Vertex 0 
	  -1.0f,   -1.0f,	1.0f,	0.27f,	0.63f,	0.29f,	1.f, // Front Left Green Vertex 1
	  -1.0f,   -1.0f,  -1.0f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 4

	  // First Bottom
	  -1.0f,   -1.0f,	1.0f,	0.3f,	0.69f,	0.31f,	1.f, // Bottom Left Medium Green Vertex 6
	   1.0f,   -1.0f,	1.0f,	0.18f,	0.49f,	0.2f,	1.f, // Bottom Front Dark Green Vertex 7
	   1.0f,   -1.0f,  -1.0f,	0.3f,	0.69f,	0.31f,	1.f,  // Bottom Right Medium Green Vertex 8

	   // Second Bottom
	  -1.0f,   -1.0f,	1.0f,	0.3f,	0.69f,	0.31f,	1.f, // Bottom Left Medium Green Vertex 6
	   1.0f,   -1.0f,  -1.0f,	0.3f,	0.69f,	0.31f,	1.f,  // Bottom Right Medium Green Vertex 8
	  -1.0f,   -1.0f,  -1.0f,	0.51f,	0.78f,	0.52f,	1.f,  // Bottom Back Light Green Vertex 9
	};

	// Pyramid: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int pyramidVBO, pyramidVAO;
	glGenVertexArrays(1, &pyramidVAO);
	glGenBuffers(1, &pyramidVBO);

	glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

	glBindVertexArray(pyramidVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Cylinder: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int cylinderVBO, cylinderVAO;
	glGenVertexArrays(1, &cylinderVAO);
	glGenBuffers(1, &cylinderVBO);

	glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
	glBindVertexArray(cylinderVAO);

	// Plane: Creation of plane
	// --------------------------------------------------
	float plane[] = {
		// Bottom Triangle
		-5.0f,	-5.0f,	-5.0f,	0.18f,	0.49f,	0.2f,	1.0f,	// Bottom Left Dark Green
		 5.0f,	-5.0f,	-5.0f,	0.18f,	0.49f,	0.2f,	1.0f,	// Bottom Right Dark Green
		 5.0f,	-5.0f,	 5.0f,	0.30f,	0.69f,	0.31f,	1.0f,	// Top Right Medium Green

		 // Top Triangle
		 5.0f,	-5.0f,	 5.0f,	0.30f,	0.69f,	0.31f,	1.0f,	// Top Right Medium Green
		-5.0f,	-5.0f,	 5.0f,	0.30f,	0.69f,	0.31f,	1.0f,	// Top Left Medium Green
		-5.0f,	-5.0f,	-5.0f,	0.18f,	0.49f,	0.2f,	1.0f,	// Bottom Left Dark Green
	};

	// Plane:Configure VAO & VBO
	// --------------------------------------------------
	unsigned int planeVBO, planeVAO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

	glBindVertexArray(planeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Render Loop
	// --------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// Time Frame Logic
		// --------------------------------------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Input Listener
		// --------------------------------------------------
		ProcessInput(window);
		computeMatricesFromInputs(window);
		// Render
		// --------------------------------------------------
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate Shader
		// --------------------------------------------------
		appShader.use();
		//appShader.setVec3("viewPos", camera.Position);

		// Transformation: View, Model & Projection
		// --------------------------------------------------
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		appShader.setMat4("projection", projection);
		appShader.setMat4("view", view);
		glm::mat4 model;
		
		// Pyramid: Instantiate & Transformations
		// --------------------------------------------------
		glBindVertexArray(pyramidVAO);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		appShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 18);

		// Cylinder: Instantiate & Transformations
		// --------------------------------------------------
		glBindVertexArray(cylinderVAO);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		appShader.setMat4("model", model);

		static_meshes_3D::Cylinder c(1.5, 30, 0.5, true, true, true);
		c.render();

		// Plane: Instantiate & Transformations
		// --------------------------------------------------
		glBindVertexArray(planeVAO);
		model = glm::translate(model, glm::vec3(0.0f, 4.73f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		appShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);



		// GLFW: Swap Buffers & Poll IO Events
		// --------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		// Delete Buffers & Vertex Arrays
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &pyramidVAO);
		glDeleteVertexArrays(1, &cylinderVAO);
		glDeleteBuffers(1, &pyramidVBO);
		glDeleteBuffers(1, &planeVBO);
		glDeleteVertexArrays(1, &planeVAO);



		// GLFW: Terminate & Clear All Resources
		// ------------------------------------------------------------------------
		glfwTerminate();
		return 0;
}

// Process Input: Listen For Keypress
// ------------------------------------------------------------------------
void ProcessInput(GLFWwindow* window) {
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
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		std::cout << "Position: X: " << camera.Position[0] << " Y: " << camera.Position[1] << " Z: " << camera.Position[2] << "\n\n" << std::endl;
		std::cout << "Front: X: " << camera.Front[0] << " Y: " << camera.Front[1] << " Z: " << camera.Front[2] << "\n\n" << std::endl;
		std::cout << "Up: X: " << camera.Up[0] << " Y: " << camera.Up[1] << " Z: " << camera.Up[2] << "\n\n" << std::endl;
		ChangeView();
	}
}


// GLFW: Called Whenever Window Resized
// ------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	// Verifies the viewport is the correct size
	glViewport(0, 0, width, height);
}

// GLFW: Called On Mouse Movement
// -------------------------------------------------------
void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// GLFW: Called on Mouse Scroll
// ----------------------------------------------------------------------
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}

void ChangeView() {
	camera.Position = cameraPos;
	camera.Front = cameraFront;
	camera.Up = cameraUp;
	std::cout << "Position: X: " << camera.Position[0] << " Y: " << camera.Position[1] << " Z: " << camera.Position[2] << "\n\n" << std::endl;
	std::cout << "Front: X: " << camera.Front[0] << " Y: " << camera.Front[1] << " Z: " << camera.Front[2] << "\n\n" << std::endl;
	std::cout << "Up: X: " << camera.Up[0] << " Y: " << camera.Up[1] << " Z: " << camera.Up[2] << "\n\n" << std::endl;

}

