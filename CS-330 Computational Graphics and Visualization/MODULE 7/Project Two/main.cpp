#include "common/ShapeGenerator.h"
#include "common/ShapeData.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/controls.cpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cylinder.h"
#include "sphere.h"
#include "shader.h"
#include "camera.h"
#include "textures.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>


using namespace std;

namespace {
	glm::vec3 cameraPos = glm::vec3(-4.71f, 0.41f, 6.30f);
	glm::vec3 cameraFront = glm::vec3(0.66f, 1.65f, -0.75f);
	glm::vec3 cameraUp = glm::vec3(1.089f, 1.0f, 1.234f);

	GLuint pyramidTexID;
	GLuint planeTexID;
	GLuint cylinderTexID;
	GLuint chalkTexID;
	GLuint ball2TexID, ball3TexID, ball4TexID, ball5TexID, ball12TexID, ball13TexID, ball14TexID, ball15TexID;
	glm::vec3 lightColor = glm::vec3(0.65f, 0.65f, 0.65f);
	
}

// Functions
// --------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);
void ChangeView();
void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Timer: Set Timeout 
// ----------------------------------------------------------------------
void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

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
bool orthographic = false;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Module 6 Milestone", NULL, NULL);
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
	glfwSetKeyCallback(window, KeyboardCallback);

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
	Shader appShader("shaderfiles/5.4.light_casters.vs", "shaderfiles/5.4.light_casters.fs");
	Shader lampShader("shaderfiles/5.4.light_cube.vs", "shaderfiles/5.4.light_cube.fs");


	

	// Cylinder: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int cylinderVBO, cylinderVAO;
	glGenVertexArrays(1, &cylinderVAO);
	glGenBuffers(1, &cylinderVBO);

	glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
	glBindVertexArray(cylinderVAO);

	// Cylinder Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* cylinderTexFilename = "includes/images/chalk_texture.jpg";
	cylinderTexID = CreateTexture(cylinderTexFilename, false);

	// Cylinder: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("cylinderTexID", 1);

	// Plane: Creation of plane
	// --------------------------------------------------
	float REPEAT = 3.0f;
	float plane[] = {
		//		Position				Normals				Texture
		// --------------------------------------------------------------------
		// Bottom Triangle				Positive Y
		-5.f,	-5.0f,	-5.0f,	 0.0f,	 1.0f,	 0.0f,	 0.0f,	 1.0f,	// Left 
		 5.0f,	-5.0f,	-5.0f,	 0.0f,	 1.0f,	 0.0f,	 0.0f,	 0.0f,	// Top
		 5.0f,	-5.0f,	 5.0f,	 0.0f,	 1.0f,	 0.0f,	 1.0f,	 0.0f,	// Right
							  
		 // Top Triangle				Positive Y
		 5.0f,	-5.0f,	 5.0f,	 0.0f,	 1.0f,	 0.0f,	 1.0f,	 0.0f,	// Left
		-5.0f,	-5.0f,	 5.0f,	 0.0f,	 1.0f,	 0.0f,	 0.0f,	 0.0f,	// Top
		-5.0f,	-5.0f,	-5.0f,	 0.0f,	 1.0f,	 0.0f,	 0.0f,	 1.0f,	// Right
	};

	// Plane:Configure VAO & VBO
	// --------------------------------------------------
	unsigned int planeVBO, planeVAO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

	// Plane: Vertices
	// --------------------------------------------------
	glBindVertexArray(planeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Plane: Texture Coords
	// --------------------------------------------------
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Plane: Normals
	// --------------------------------------------------
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Plane Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* planeTexFilename = "includes/images/table_lining.jpg";
	planeTexID = CreateTexture(planeTexFilename);

	// Plane: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("planeTexID", 2);

	// Chalk:  Chalk Creation
	float chalk[] = {
		//		Position				Normals				Texture
		// --------------------------------------------------------------------
		//	Back Face				Negative Z						
		-0.5f, -0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 0.0f,	 0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 1.0f,	 0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 1.0f,	 1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 1.0f,	 1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 0.0f,	 1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,	 0.0f,	-1.0f,	 0.0f,	 0.0f,

		// Front Face				Positive Z
		-0.5f, -0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 0.0f,	 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 1.0f,	 0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 1.0f,	 1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 1.0f,	 1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 0.0f,	 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,	 0.0f,	1.0f,	 0.0f,	 0.0f,

		// Left Face				Negative X
		-0.5f,  0.5f,  0.5f,	-1.0f,	 0.0f,	0.0f,	 1.0f,	 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,	 0.0f,	0.0f,	 1.0f,	 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,	 0.0f,	0.0f,	 0.0f,	 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,	 0.0f,	0.0f,	 0.0f,	 1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,	 0.0f,	0.0f,	 0.0f,	 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,	 0.0f,	0.0f,	 1.0f,	 0.0f,

		// Right Face				Positive X
		 0.5f,  0.5f,  0.5f,	 1.0f,	 0.0f,	0.0f,	 1.0f,	 0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,	 0.0f,	0.0f,	 1.0f,	 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,	 0.0f,	0.0f,	 0.0f,	 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,	 0.0f,	0.0f,	 0.0f,	 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,	 0.0f,	0.0f,	 0.0f,	 0.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,	 0.0f,	0.0f,	 1.0f,	 0.0f,

		 // Bottom Face				Negative Y
		-0.5f, -0.5f, -0.5f,	 0.0f,	-1.0f,	0.0f,	 0.0f,	 1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,	-1.0f,	0.0f,	 1.0f,	 1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,	-1.0f,	0.0f,	 1.0f,	 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,	-1.0f,	0.0f,	 1.0f,	 0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,	-1.0f,	0.0f,	 0.0f,	 0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,	-1.0f,	0.0f,	 0.0f,	 1.0f,

		// Top Face					Positive Y
		-0.5f,  0.5f, -0.5f,	 0.0f,	 1.0f,	0.0f,	 0.0f,	 1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,	 1.0f,	0.0f,	 1.0f,	 1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,	 1.0f,	0.0f,	 1.0f,	 0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,	 1.0f,	0.0f,	 1.0f,	 0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,	 1.0f,	0.0f,	 0.0f,	 0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,	 1.0f,	0.0f,	 0.0f,	 1.0f,
	};

	// Chalk:Configure VAO & VBO
	// --------------------------------------------------
	unsigned int chalkVBO, chalkVAO;
	glGenVertexArrays(1, &chalkVAO);
	glGenBuffers(1, &chalkVBO);

	glBindBuffer(GL_ARRAY_BUFFER, chalkVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(chalk), chalk, GL_STATIC_DRAW);

	// Chalk: Vertices
	// --------------------------------------------------
	glBindVertexArray(chalkVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Chalk: Texture Coords
	// --------------------------------------------------
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Chalk: Normals
// --------------------------------------------------
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Chalk Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* chalkTexFilename = "includes/images/chalk.jpg";
	chalkTexID = CreateTexture(chalkTexFilename);

	// Chalk: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("chalkTexID", 3);



	// balls: Set the texture
	// --------------------------------------------------

	// Ball2
	// --------------------------------------------------
	unsigned int ball2VBO, ball2VAO;
	glGenVertexArrays(1, &ball2VAO);
	glGenBuffers(1, &ball2VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball2VBO);
	glBindVertexArray(ball2VAO);

	ball2TexID = CreateTexture("includes/images/ball-2.jpg");
	appShader.use();
	appShader.setInt("ball2TexID", 2);

	// Ball3
	// --------------------------------------------------
	unsigned int ball3VBO, ball3VAO;
	glGenVertexArrays(1, &ball3VAO);
	glGenBuffers(1, &ball3VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball3VBO);
	glBindVertexArray(ball3VAO);

	ball3TexID = CreateTexture("includes/images/ball-3.jpg");
	appShader.use();
	appShader.setInt("ball3TexID", 3);


	// Ball4
	// --------------------------------------------------
	unsigned int ball4VBO, ball4VAO;
	glGenVertexArrays(1, &ball4VAO);
	glGenBuffers(1, &ball4VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball4VBO);
	glBindVertexArray(ball4VAO);

	ball4TexID = CreateTexture("includes/images/ball-4.jpg");
	appShader.use();
	appShader.setInt("ball4TexID", 4);

	// Ball5
	// --------------------------------------------------
	unsigned int ball5VBO, ball5VAO;
	glGenVertexArrays(1, &ball5VAO);
	glGenBuffers(1, &ball5VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball5VBO);
	glBindVertexArray(ball5VAO);

	ball5TexID = CreateTexture("includes/images/ball-5.jpg");
	appShader.use();
	appShader.setInt("ball5TexID", 5);


	// Ball12
	// --------------------------------------------------
	unsigned int ball12VBO, ball12VAO;
	glGenVertexArrays(1, &ball12VAO);
	glGenBuffers(1, &ball12VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball12VBO);
	glBindVertexArray(ball12VAO);

	ball12TexID = CreateTexture("includes/images/ball-12.jpg");
	appShader.use();
	appShader.setInt("ball12TexID", 12);

	// Ball13
	// --------------------------------------------------
	unsigned int ball13VBO, ball13VAO;
	glGenVertexArrays(1, &ball13VAO);
	glGenBuffers(1, &ball13VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball13VBO);
	glBindVertexArray(ball13VAO);

	ball13TexID = CreateTexture("includes/images/ball-13.jpg");
	appShader.use();
	appShader.setInt("ball13TexID", 13);

	// Ball14
	// --------------------------------------------------
	unsigned int ball14VBO, ball14VAO;
	glGenVertexArrays(1, &ball14VAO);
	glGenBuffers(1, &ball14VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball14VBO);
	glBindVertexArray(ball14VAO);

	ball14TexID = CreateTexture("includes/images/ball-14.jpg");
	appShader.use();
	appShader.setInt("ball14TexID", 14);
	
	// Ball15
	// --------------------------------------------------
	unsigned int ball15VBO, ball15VAO;
	glGenVertexArrays(1, &ball15VAO);
	glGenBuffers(1, &ball15VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball15VBO);
	glBindVertexArray(ball15VAO);

	ball15TexID = CreateTexture("includes/images/ball-15.jpg");
	appShader.use();
	appShader.setInt("ball15TexID", 15);

	// PointLights: Positions
	// --------------------------------------------------
	glm::vec3 pointLights[] = {
		glm::vec3( 0.0f,	 3.0f,	-1.75f),
		glm::vec3(-1.2f,	 2.3f,	-1.9f),
		glm::vec3( 1.9f,	 3.0f,	-2.2f),
		glm::vec3( 3.0f,	 1.0f,	 3.0f)
	};

	glm::vec3 spotLights[] = {
		glm::vec3(-1.25f,	 6.0f,	 5.5f),
		glm::vec3( 2.5f,	 6.0f,	 2.0f)
	};

	/// pointLight: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);

	glBindBuffer(GL_ARRAY_BUFFER, chalkVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
		appShader.use();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection;
		if (orthographic) {
			float scale = 100;
			projection = glm::ortho(-((float)SCR_WIDTH / scale), ((float)SCR_WIDTH / scale), -((float)SCR_HEIGHT / scale), ((float)SCR_HEIGHT / scale), -10.0f, 10.0f);
			glm::mat4 orthomodel = glm::mat4(1.0f);
			//orthomodel = glm::translate(orthomodel, glm::vec3(0.0f, -5.0f, -75.0f));
			appShader.setMat4("model", orthomodel);
		}
		else {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		}
		appShader.setMat4("view", view);
		glm::mat4 model;
		appShader.setMat4("model", model);
		appShader.setVec3("viewPos", camera.Position);
		appShader.setVec3("lightColor", lightColor);
		appShader.setFloat("shininess", 2);
		//appShader.setFloat("cutOff", glm::cos(glm::radians(12.5f)));
		//appShader.setFloat("outerCutOff", glm::cos(glm::radians(17.5f)));

		// Directional Lighting
		appShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -0.20f, -0.3f));
		appShader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		appShader.setVec3("dirLight.specular", glm::vec3(0.8f, 0.8f, 0.8f));

		// Point Lighting 1
		appShader.setVec3("pointLights[0].position", pointLights[0]);
		appShader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[0].diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		appShader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[0].constant", 1.0f);
		appShader.setFloat("pointLights[0].linear", 0.09f);
		appShader.setFloat("pointLights[0].quadratic", 0.032f);

		// Point Lighting 1
		appShader.setVec3("pointLights[1].position", pointLights[1]);
		appShader.setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[1].diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		appShader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[1].constant", 1.0f);
		appShader.setFloat("pointLights[1].linear", 0.09f);
		appShader.setFloat("pointLights[1].quadratic", 0.032f);

		// Point Lighting 1
		appShader.setVec3("pointLights[2].position", pointLights[2]);
		appShader.setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[2].diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		appShader.setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[2].constant", 1.0f);
		appShader.setFloat("pointLights[2].linear", 0.09f);
		appShader.setFloat("pointLights[2].quadratic", 0.032f);

		// Point Lighting 4
		appShader.setVec3("pointLights[3].position", pointLights[3]);
		appShader.setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[3].diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		appShader.setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[3].constant", 1.0f);
		appShader.setFloat("pointLights[3].linear", 0.09f);
		appShader.setFloat("pointLights[3].quadratic", 0.032f);

		// Spot Lighting 1
		appShader.setVec3("spotLights[1].position", spotLights[0]);
		appShader.setVec3("spotLights[0].direction", glm::vec3(-1.0f, -0.5f, 0.70f));
		appShader.setVec3("spotLights[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		appShader.setVec3("spotLights[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setVec3("spotLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("spotLights[0].constant", 1.0f);
		appShader.setFloat("spotLights[0].linear", 0.09f);
		appShader.setFloat("spotLights[0].quadratic", 0.32f);
		appShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		appShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(24.5f)));

		appShader.setMat4("projection", projection);

		
		// Cylinder: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(cylinderVAO);
		ProcessTexture(GL_TEXTURE0, cylinderTexID);
		glm::mat4 cylindermodel = glm::mat4(1.0f);
		cylindermodel = glm::translate(cylindermodel, glm::vec3(1.05f, -0.75f, 1.12));
		appShader.setMat4("model", cylindermodel);

		static_meshes_3D::Cylinder c(0.25, 30, 0.5, true, true, true);
		c.render();
		glBindVertexArray(0);

		// Plane: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		ProcessTexture(GL_TEXTURE0, planeTexID);
		glBindVertexArray(planeVAO);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.00f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.75f));
		appShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Chalk: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(chalkVAO);
		ProcessTexture(GL_TEXTURE0, chalkTexID);
		glm::mat4 chalkmodel = glm::mat4(1.0f);
		chalkmodel = glm::translate(model, glm::vec3(1.4f, -4.65f, 1.5));
		chalkmodel = glm::scale(chalkmodel, glm::vec3(0.43f, 0.43f, 0.43f));
		appShader.setMat4("model", chalkmodel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Balls: Render
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(ball2VAO);
		ProcessTexture(GL_TEXTURE0, ball2TexID);
		glm::mat4 ball2model = glm::mat4(1.0f);
		ball2model = glm::translate(ball2model, glm::vec3(-2.35f, -0.52f, -0.9f));
		ball2model = glm::scale(ball2model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball2model = glm::rotate(ball2model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		appShader.setMat4("model", ball2model);

		static_meshes_3D::Sphere ball2(2.0f, 80, 20);
		ball2.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball3VAO);
		ProcessTexture(GL_TEXTURE0, ball3TexID);
		glm::mat4 ball3model = glm::mat4(1.0f);
		ball3model = glm::translate(ball3model, glm::vec3(-0.25f, -0.52f, 1.25f));
		ball3model = glm::scale(ball3model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball3model = glm::rotate(ball3model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		appShader.setMat4("model", ball3model);

		static_meshes_3D::Sphere ball3(2.0f, 80, 20);
		ball3.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball4VAO);
		ProcessTexture(GL_TEXTURE0, ball4TexID);
		glm::mat4 ball4model = glm::mat4(1.0f);
		ball4model = glm::translate(ball4model, glm::vec3(-1.9f, -0.52f, -3.00f));
		ball4model = glm::scale(ball4model, glm::vec3(0.25f, 0.25f, 0.25f));
		appShader.setMat4("model", ball4model);

		static_meshes_3D::Sphere ball4(2.0f, 80, 20);
		ball4.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball5VAO);
		ProcessTexture(GL_TEXTURE0, ball5TexID);
		glm::mat4 ball5model = glm::mat4(1.0f);
		ball5model = glm::translate(ball5model, glm::vec3(1.7f, -0.52f, -3.2f));
		ball5model = glm::scale(ball5model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball5model = glm::rotate(ball5model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		appShader.setMat4("model", ball5model);

		static_meshes_3D::Sphere ball5(2.0f, 80, 20);
		ball5.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball12VAO);
		ProcessTexture(GL_TEXTURE0, ball12TexID);
		glm::mat4 ball12model = glm::mat4(1.0f);
		ball12model = glm::translate(ball12model, glm::vec3(1.45f, -0.42f, -0.3f));
		ball12model = glm::rotate(ball12model, glm::radians(-60.0f), glm::vec3(0.5f, -1.43f, 1.0f));
		ball12model = glm::scale(ball12model, glm::vec3(0.25f, 0.25f, 0.25f));
		appShader.setMat4("model", ball12model);

		static_meshes_3D::Sphere ball12(2.0f, 80, 20);
		ball12.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball13VAO);
		ProcessTexture(GL_TEXTURE0, ball13TexID);
		glm::mat4 ball13model = glm::mat4(1.0f);
		ball13model = glm::translate(ball13model, glm::vec3(-2.3f, -0.52f, 2.15f));
		ball13model = glm::scale(ball13model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball13model = glm::rotate(ball13model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ball13model = glm::rotate(ball13model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ball13model = glm::rotate(ball13model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		appShader.setMat4("model", ball13model);

		static_meshes_3D::Sphere ball13(2.0f, 80, 20);
		ball13.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball14VAO);
		ProcessTexture(GL_TEXTURE0, ball14TexID);
		glm::mat4 ball14model = glm::mat4(1.0f);
		ball14model = glm::translate(ball14model, glm::vec3(2.25f, -0.52f, 2.65f));
		ball14model = glm::scale(ball14model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball14model = glm::rotate(ball14model, glm::radians(-60.0f), glm::vec3(1.0f,	-0.43f, 0.0f));
		//ball14model = glm::rotate(ball13model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//ball14model = glm::rotate(ball13model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		appShader.setMat4("model", ball14model);
		static_meshes_3D::Sphere ball14(2.0f, 80, 20);
		ball14.render();
		glBindVertexArray(0);

		appShader.use();
		glBindVertexArray(ball15VAO);
		ProcessTexture(GL_TEXTURE0, ball15TexID);
		glm::mat4 ball15model = glm::mat4(1.0f);
		ball15model = glm::translate(ball15model, glm::vec3(0.0f, -0.52f, -1.8f));
		ball15model = glm::scale(ball15model, glm::vec3(0.25f, 0.25f, 0.25f));
		appShader.setMat4("model", ball15model);

		static_meshes_3D::Sphere ball15(2.0f, 80, 20);
		ball15.render();
		glBindVertexArray(0);
		
		// GLFW: Swap Buffers & Poll IO Events
		// --------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		// Delete Buffers & Vertex Arrays
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &cylinderVAO);
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
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		camera.ProcessKeyboard(DOWN, deltaTime);
		camera.SetTempSpeed();
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
		camera.ProcessKeyboard(UP, deltaTime);
		camera.SetTempSpeed();
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera.IncreaseMovement();
		sleep(250);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera.DecreaseMovement();
		sleep(250);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera.DecreaseSensitivity();
		sleep(250);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera.IncreaseSensitivity();
		sleep(250);
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

// Input: Keyboard Key Callback
// ----------------------------------------------------------------------
void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			orthographic = !orthographic;
			string mode;
			if (orthographic)
				mode = "Orthographic";
			else
				mode = "Perspective";
			sleep(500);
	}
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



