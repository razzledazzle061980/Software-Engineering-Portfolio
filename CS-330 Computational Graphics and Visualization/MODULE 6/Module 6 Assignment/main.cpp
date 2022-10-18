#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "stb_image.h"
#include "common/controls.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "camera.h"
#include "textures.h"



namespace {
	glm::vec3 cameraPos = glm::vec3(-4.71f, 0.41f, 6.30f);
	glm::vec3 cameraFront = glm::vec3(0.66f, 1.65f, -0.75f);
	glm::vec3 cameraUp = glm::vec3(1.089f, 1.0f, 1.234f);

	GLuint pyramidTexID;
	GLuint planeTexID;
	GLuint cylinderTexID;

	glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

	glm::vec3 lightPositions[] = {
		glm::vec3(5.2f, 3.0f, 0.0f),
		glm::vec3(-7.2f, 4.5f, 0.0f)
	};

	glm::vec3 lightColors[] = {
		glm::vec3(0.41f, 0.62f, 0.22f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	float lightIntesity[] = {
		1.0f,
		0.1f
	};

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Module 6 Assignment", NULL, NULL);
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
	//Shader appShader("shaderfiles/7.3.camera.vs", "shaderfiles/7.3.camera.fs");
	Shader lightingShader("shaderfiles/2.2.basic_lighting.vs", "shaderfiles/2.2.basic_lighting.fs");
	Shader lampShader("shaderfiles/2.2.light_cube.vs", "shaderfiles/2.2.light_cube.fs");

	// Pyramid: Creation of pyramid
		// --------------------------------------------------
	float pyramid[] = {
		//		Position			Normals				Texture Coords
		//----------------------------------------------------------------
		// Front Face				 Positive Z		
		0.0f,	 1.0f,	0.0f,	 0.0f,	 0.0f,	 1.0f,	 0.5f,	 1.0f,	// Top Light Green Vertex 0 
	   -1.0f,	-1.0f,	1.0f,	 0.0f,	 0.0f,	 1.0f,	 0.0f,	 0.0f,	// Left Green Vertex 1
		1.0f,	-1.0f,	1.0f,	 0.0f,	 0.0f,	 1.0f,	 1.0f,	 0.0f,	// Right Green Vertex 2

		// Right Face				Positive X		 	
		0.0f,	 1.0f,	0.0f,	 1.0f,	 0.0f,	 0.0f,	 0.5f,	 1.0f,	// Top Light Green Vertex 0 
		1.0f,	-1.0f,	1.0f,	 1.0f,	 0.0f,	 0.0f,	 0.0f,	 0.0f,	// Left Dark Green Vertex 2
		1.0f,	-1.0f, -1.0f,	 1.0f,	 0.0f,	 0.0f,	 1.0f,	 0.0f,	// Right Dark Green Vertex 3

		// Back Face				Negative Z		 	
		0.0f,	1.0f,	0.0f,	 0.0f,	 0.0f,	-1.0f,	 0.5f,	 1.0f,	// Top Light Green Vertex 0 
		1.0f,  -1.0f,  -1.0f,	 0.0f,	 0.0f,	-1.0f,	 0.0f,	 0.0f,	// Left Dark Green Vertex 3
	   -1.0f,  -1.0f,  -1.0f,	 0.0f,	 0.0f,	-1.0f,	 1.0f,	 0.0f,	// Right Dark Medium Green Vertex 4

	   // Left Face					Negative X	
	   0.0f,	1.0f,	0.0f,	-1.0f,	 0.0f,	 0.0f,	 0.5f,	 1.0f,	// Top Light Green Vertex 0 
	  -1.0f,   -1.0f,	1.0f,	-1.0f,	 0.0f,	 0.0f,	 1.0f,	 0.0f,	// Right Green Vertex 1
	  -1.0f,   -1.0f,  -1.0f,	-1.0f,	 0.0f,	 0.0f,	 0.0f,	 0.0f,	// Left Dark Green Vertex 4

	  // First Bottom				Negative Y
	  -1.0f,   -1.0f,	1.0f,	 0.0f,	-1.0f,	 0.0f,	 0.0f,	 0.0f,	// Left Medium Green Vertex 6
	   1.0f,   -1.0f,	1.0f,	 0.0f,	-1.0f,	 0.0f,	 0.5f,	 1.0f,	// Top Front Dark Green Vertex 7
	   1.0f,   -1.0f,  -1.0f,	 0.0f,	-1.0f,	 0.0f,	 1.0f,	 0.0f,	// Right Medium Green Vertex 8

	   // Second Bottom		 		Negative Y
	  -1.0f,   -1.0f,	1.0f,	 0.0f,	-1.0f,	 0.0f,	 1.0f,	 0.0f,	// Right Medium Green Vertex 6
	   1.0f,   -1.0f,  -1.0f,	 0.0f,	-1.0f,	 0.0f,	 0.0f,	 0.0f,	// Left Medium Green Vertex 8
	  -1.0f,   -1.0f,  -1.0f,	 0.0f,	-1.0f,	 0.0f,	 0.5f,	 1.0f,	// Top Light Green Vertex 9
	};

	// Pyramid: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int pyramidVBO, pyramidVAO;
	glGenVertexArrays(1, &pyramidVAO);
	glGenBuffers(1, &pyramidVBO);

	glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

	// Pyramid: Vertices
	// --------------------------------------------------
	glBindVertexArray(pyramidVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Pyramid: Normals 
	// --------------------------------------------------
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Pyramid: Texture Coords
	// --------------------------------------------------
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Pyramid Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* pyramidTexFilename = "includes/images/brick.jpg";
	pyramidTexID = CreateTexture(pyramidTexFilename);

	// Pyramid: Set the texture
	// --------------------------------------------------
	lightingShader.use();
	lightingShader.setInt("pyramidTexID", 0);

	// Lamp: Creation
	// --------------------------------------------------
	float lamp[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// Lamp: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int lampVBO, lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glGenBuffers(1, &lampVBO);

	glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lamp), lamp, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
	
	// Lamp: Vertices
	// --------------------------------------------------
	glBindVertexArray(lampVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate Shader
		// --------------------------------------------------
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		// Lamp 1 - Key
		lightingShader.setVec3("lights[0].pos", lightPositions[0]);
		lightingShader.setVec3("lights[0].color", lightColors[0]);
		lightingShader.setFloat("lights[0].intensity", lightIntesity[0]);
		// Lamp 2 - Fill
		lightingShader.setVec3("lights[1].pos", lightPositions[1]);
		lightingShader.setVec3("lights[1].color", lightColors[1]);
		lightingShader.setFloat("lights[1].intensity", lightIntesity[1]);

		// Transformation: View, Model & Projection
		// --------------------------------------------------
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		glm::mat4 model;
		
		// Pyramid: Instantiate & Transformations
		// --------------------------------------------------
		ProcessTexture(GL_TEXTURE0, pyramidTexID);
		glBindVertexArray(pyramidVAO);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightingShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 18);

		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);

		glBindVertexArray(lampVAO);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f));
		lampShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPositions[1]);
		model = glm::scale(model, glm::vec3(0.2f));
		lampShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// GLFW: Swap Buffers & Poll IO Events
		// --------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		// Delete Buffers & Vertex Arrays
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &pyramidVAO);
		glDeleteBuffers(1, &pyramidVBO);




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

