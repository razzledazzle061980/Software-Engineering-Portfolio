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

using namespace std;

namespace {
	glm::vec3 cameraPos = glm::vec3(-4.71f, 0.41f, 6.30f);
	glm::vec3 cameraFront = glm::vec3(0.66f, 1.65f, -0.75f);
	glm::vec3 cameraUp = glm::vec3(1.089f, 1.0f, 1.234f);

	GLuint pyramidTexID;
	GLuint planeTexID;
	GLuint cylinderTexID;
	GLuint ball8TexID;
	GLuint ball13TexID;
	GLuint chalkTexID;
	GLuint ball2TexID;
	GLuint ball3TexID;

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	int NUM_LIGHTS = 6;
}

// Functions
// --------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);
void ChangeView();

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

	/// Ball8: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int ball8VBO, ball8VAO;
	glGenVertexArrays(1, &ball8VAO);
	glGenBuffers(1, &ball8VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball8VBO);
	glBindVertexArray(ball8VAO);

	// Ball8 Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* ball8TexFilename = "includes/images/ball-8.jpg";
	ball8TexID = CreateTexture(ball8TexFilename);
	
	// ball13: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("ball8TexID", 4);

	/// ball13: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int ball13VBO, ball13VAO;
	glGenVertexArrays(1, &ball13VAO);
	glGenBuffers(1, &ball13VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball13VBO);
	glBindVertexArray(ball13VAO);

	// ball13 Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* ball13TexFilename = "includes/images/ball-13.jpg";
	ball13TexID = CreateSphereTexture(ball13TexFilename);

	// ball13: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("ball13TexID", 6);

	/// ball2: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int ball2VBO, ball2VAO;
	glGenVertexArrays(1, &ball2VAO);
	glGenBuffers(1, &ball2VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball2VBO);
	glBindVertexArray(ball2VAO);

	// ball2 Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* ball2TexFilename = "includes/images/ball-2.jpg";
	ball2TexID = CreateTexture(ball2TexFilename);

	// ball2: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("ball2TexID", 7);

	/// ball2: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int ball3VBO, ball3VAO;
	glGenVertexArrays(1, &ball3VAO);
	glGenBuffers(1, &ball3VBO);

	glBindBuffer(GL_ARRAY_BUFFER, ball3VBO);
	glBindVertexArray(ball3VAO);

	// ball2 Texture: Create the texture using custom class
	// --------------------------------------------------
	const char* ball3TexFilename = "includes/images/ball-3.jpg";
	ball3TexID = CreateSphereTexture(ball3TexFilename);

	// ball2: Set the texture
	// --------------------------------------------------
	appShader.use();
	appShader.setInt("ball3TexID", 8);

	// PointLights: Positions
// --------------------------------------------------
	glm::vec3 pointLights[] = {
		glm::vec3( 0.7f,	 0.2f,	 2.0f),
		glm::vec3( 2.3f,	-3.3f,	-4.0f),
		glm::vec3(-4.0f,	 2.0f,	-12.0f),
		glm::vec3( 0.0f,	 0.0f,	-3.0f)
	};

	/// pointLight: Configure VAO & VBO
	// --------------------------------------------------
	unsigned int lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
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
		appShader.setVec3("viewPos", camera.Position);
		appShader.setVec3("lightColor", lightColor);
		appShader.setFloat("shininess", 32.0f);
		appShader.setFloat("cutOff", glm::cos(glm::radians(12.5f)));
		appShader.setFloat("outerCutOff", glm::cos(glm::radians(17.5f)));

		// Directional Lighting
		appShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		appShader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		appShader.setVec3("dirLight.specular", glm::vec3(0.7f, 0.7f, 0.7f));

		// Point Lighting 1
		appShader.setVec3("pointLights[0].position", pointLights[0].x, pointLights[0].y, pointLights[0].z);
		appShader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		appShader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[0].constant", 1.0f);
		appShader.setFloat("pointLights[0].linear", 0.09f);
		appShader.setFloat("pointLights[0].quadratic", 0.032f);

		// Point Lighting 1
		appShader.setVec3("pointLights[1].position", pointLights[1].x, pointLights[1].y, pointLights[1].z);
		appShader.setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		appShader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[1].constant", 1.0f);
		appShader.setFloat("pointLights[1].linear", 0.09f);
		appShader.setFloat("pointLights[1].quadratic", 0.032f);

		// Point Lighting 1
		appShader.setVec3("pointLights[2].position", pointLights[2].x, pointLights[2].y, pointLights[2].z);
		appShader.setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		appShader.setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[2].constant", 1.0f);
		appShader.setFloat("pointLights[2].linear", 0.09f);
		appShader.setFloat("pointLights[2].quadratic", 0.032f);

		// Point Lighting 4
		appShader.setVec3("pointLights[3].position", pointLights[3].x, pointLights[3].y, pointLights[3].z);
		appShader.setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		appShader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		appShader.setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("pointLights[3].constant", 1.0f);
		appShader.setFloat("pointLights[3].linear", 0.09f);
		appShader.setFloat("pointLights[3].quadratic", 0.032f);

		// Spot Lighting
		appShader.setVec3("spotLight.position", glm::vec3(-1.0f, 4.0f, 1.0f));
		appShader.setVec3("spotLight.direction", glm::vec3(-0.1f, -1.0f, 0.2f));
		appShader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		appShader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		appShader.setFloat("spotLight.constant", 1.0f);
		appShader.setFloat("spotLight.linear", 0.09f);
		appShader.setFloat("spotLight.quadratic", 0.032f);
		appShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(25.0f)));
		appShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(35.0f)));


		// --------------------------------------------------
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		appShader.setMat4("projection", projection);
		appShader.setMat4("view", view);
		glm::mat4 model;
		appShader.setMat4("model", model);
		
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

		// Ball8: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(ball8VAO);
		ProcessTexture(GL_TEXTURE0, ball8TexID);
		glm::mat4 ball8model = glm::mat4(1.0f);
		ball8model = glm::translate(ball8model, glm::vec3(1.5f, -0.52f, 0.0f));
		ball8model = glm::scale(ball8model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball8model = glm::rotate(ball8model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		appShader.setMat4("model", ball8model);

		static_meshes_3D::Sphere ball8(2.0f, 80, 20, true, true, true);
		ball8.render();
		glBindVertexArray(0);

		// ball13: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(ball13VAO);
		ProcessTexture(GL_TEXTURE0, ball13TexID);
		glm::mat4 ball13model = glm::mat4(1.0f);
		ball13model = glm::translate(ball13model, glm::vec3(-1.5f, -0.52f, 2.15f));
		ball13model = glm::scale(ball13model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball13model = glm::rotate(ball13model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ball13model = glm::rotate(ball13model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		ball13model = glm::rotate(ball13model, glm::radians(30.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		appShader.setMat4("model", ball13model);

		static_meshes_3D::Sphere ball13(2.0f, 80, 20, true, true, true);
		ball13.render();
		glBindVertexArray(0);

		// ball2: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(ball2VAO);
		ProcessTexture(GL_TEXTURE0, ball2TexID);
		glm::mat4 ball2model = glm::mat4(1.0f);
		ball2model = glm::translate(ball2model, glm::vec3(-1.35f, -0.52f, 0.35f));
		ball2model = glm::scale(ball2model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball2model = glm::rotate(ball2model, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
		appShader.setMat4("model", ball2model);

		static_meshes_3D::Sphere ball2(2.0f, 80, 20, true, true, true);
		ball2.render();
		glBindVertexArray(0);


		// ball3: Instantiate & Transformations
		// --------------------------------------------------
		appShader.use();
		glBindVertexArray(ball3VAO);
		ProcessTexture(GL_TEXTURE0, ball3TexID);
		glm::mat4 ball3model = glm::mat4(1.0f);
		ball3model = glm::translate(ball3model, glm::vec3(-0.25f, -0.52f, 1.25f));
		ball3model = glm::scale(ball3model, glm::vec3(0.25f, 0.25f, 0.25f));
		ball3model = glm::rotate(ball3model, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));

		appShader.setMat4("model", ball3model);

		static_meshes_3D::Sphere ball3(2.0f, 80, 20, true, true, true);
		ball3.render();
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
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		camera.SetTempSpeed();
	else
		camera.SetDefaultSpeed();
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

