/* Main file for Module 3 Milestone
* Contains two objects a pyramid and a cylinder
*/

// Includes
//----------------------------------

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "cylinder.h"
#include "camera.h"

// Shader Program
//----------------------------------
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

using namespace std;


namespace {
	// Variables
	// ---------------------------------------------
	int windowWidth = 1920;
	int windowHeight = 1080;
	const char* windowTitle = "Module 3 Milestone";

	GLFWwindow* window = nullptr;

	glm::vec3 cameraPos = glm::vec3(4.0f, 0.0f, -15.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	unsigned int VBO, VAO;
	unsigned int VBO2, VAO2;

	GLuint appShader;

} 

// Function Declarations
// ---------------------------------------------
bool CreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& appShader);
bool Initialize(int, char* [], GLFWwindow** window);
void CreateObjects();
void ProcessInput(GLFWwindow* window);
void Render();
void DeleteArrays();
void DeleteProgram(GLuint appShader);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

// Shader Source Code
// ---------------------------------------------
const GLchar* vertexShaderSource = GLSL(440,
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
const GLchar* fragmentShaderSource = GLSL(440,
	in vec4 vertexColor; 
out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(vertexColor);
}
);



// Entry point of application
// ---------------------------------------------
int main(int argc, char* argv[]) {

	// Initialize program
	if (!Initialize(argc, argv, &window))
		return EXIT_FAILURE;

	// Create objects
	CreateObjects();

	// Create Shader
	if (!CreateShaderProgram(vertexShaderSource, fragmentShaderSource, appShader))
		return EXIT_FAILURE;

	

	// Loop while window being shown
	while (!glfwWindowShouldClose(window)) {

		// Listen For Keypress
		ProcessInput(window);

		// Render Objects
		Render();

		glfwPollEvents();
	}

	// Delete Arrays, Buffers & Shader Program
	// ---------------------------------------------
	DeleteArrays();
	DeleteProgram(appShader);
}

// CreateObjects: Creates Pyramid & Cylinder Arrays & Buffers
// ---------------------------------------------
void CreateObjects() {
	// Pyramid
	GLfloat pyramid[] = {
		// Front Face
		0.f,	 1.f,	0.f,	0.18f,	0.49f,	0.2f,	1.f, // Top Light Green Vertex 0 
	   -1.f,	-1.f,	1.f,	0.27f,	0.63f,	0.29f,	1.f, // Front Left Green Vertex 1
		1.f,	-1.f,	1.f,	0.27f,	0.63f,	0.29f,	1.f, // Front Right Green Vertex 2

		// Right Face
		0.f,	 1.f,	0.f,	0.27f,	0.63f,	0.29f,	1.f, // Top Light Green Vertex 0 
		1.f,	-1.f,	1.f,	0.18f,	0.49f,	0.2f,	1.f, // Front Right Dark Green Vertex 2
		1.f,	-1.f,  -1.f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 3

		// Back Face
		0.f,	 1.f,	0.f,	0.51f,	0.78f,	0.52f,	1.f, // Top Light Green Vertex 0 
		1.f,	-1.f,  -1.f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 3
	   -1.f,	-1.f,  -1.f,	0.3f,	0.69f,	0.31f,	1.f,  // Back Dark Medium Green Vertex 4

	   // Left Face
	   0.f,		1.f,	0.f,	0.51f,	0.78f,	0.52f,	1.f, // Top Light Green Vertex 0 
	  -1.f,	   -1.f,	1.f,	0.27f,	0.63f,	0.29f,	1.f, // Front Left Green Vertex 1
	  -1.f,	   -1.f,   -1.f,	0.18f,	0.49f,	0.2f,	1.f,  // Back Dark Green Vertex 4

	  // First Bottom
	  -1.f,	   -1.f,	1.f,	0.3f,	0.69f,	0.31f,	1.f, // Bottom Left Medium Green Vertex 6
	   1.f,	   -1.f,	1.f,	0.18f,	0.49f,	0.2f,	1.f, // Bottom Front Dark Green Vertex 7
	   1.f,	   -1.f,   -1.f,	0.3f,	0.69f,	0.31f,	1.f,  // Bottom Right Medium Green Vertex 8

	   // Second Bottom
	  -1.f,	   -1.f,	1.f,	0.3f,	0.69f,	0.31f,	1.f, // Bottom Left Medium Green Vertex 6
	   1.f,	   -1.f,   -1.f,	0.3f,	0.69f,	0.31f,	1.f,  // Bottom Right Medium Green Vertex 8
	  -1.f,	   -1.f,   -1.f,	0.51f,	0.78f,	0.52f,	1.f,  // Bottom Back Light Green Vertex 9
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Cylinder
	unsigned int VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

}

// Resize Window callback
// ---------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

// Initialize: Creates the Window, Initialized GLFW
// ---------------------------------------------
bool Initialize(int argc, char* argv[], GLFWwindow** window) {

	// GLFW: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW: window creation
	*window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Event Listeners
	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, FramebufferSizeCallback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// GLAD: Load all glad functions
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Output OpenGL version
	std::cout << "INFO: OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	return true;
}


// Process Input: Listen for escape keypress
// ---------------------------------------------
void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Render: Initializes App Shader & Controls Position Of View
// ---------------------------------------------
void Render() {

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Transform the objects
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

	// Create perspective projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 2.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	

	GLint modelMatrix = glGetUniformLocation(appShader, "model");
	GLint viewMatrix = glGetUniformLocation(appShader, "view");
	GLint projectionMatrix = glGetUniformLocation(appShader, "projection");

	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));

	glUseProgram(appShader);
	glBindVertexArray(VAO);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-.3f, 0.f, 1.3f));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
	model = glm::rotate(model, glm::radians(25.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 18);


	glUseProgram(appShader);
	glBindVertexArray(VAO2);
	glm::mat4 cylinderModel = glm::mat4(1.0f);
	cylinderModel = glm::translate(cylinderModel, glm::vec3(0.0f, -1.4f, 0.f));
	cylinderModel = glm::rotate(cylinderModel, glm::radians(15.f), glm::vec3(1.f, 0.f, 0.f));
	cylinderModel = glm::rotate(cylinderModel, glm::radians(10.f), glm::vec3(0.f, 1.f, 0.f));
	cylinderModel = glm::rotate(cylinderModel, glm::radians(20.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinderModel));
	static_meshes_3D::Cylinder C(1.5, 30, .5, true, true, true);
	C.render();

	glBindVertexArray(0);

	glfwSwapBuffers(window);

}

// DeleteArrays: Deletes Vertex Arrays
// ---------------------------------------------
void DeleteArrays() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
}

// DeleteProgram: Deletes SHader Program
// ---------------------------------------------
void DeleteProgram(GLuint shader) {
	glDeleteProgram(shader);
}

// CreateShaderProgram: Creates Shader Program
// ---------------------------------------------
bool CreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& appShader) {

	// Setup error reporting
	int success = false;
	char infoLog[512];

	// Create shader program object
	appShader = glCreateProgram();

	// Create shader objects
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Get shader sources
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	// Compile the vertex shader and print compilation errors
	glCompileShader(vertexShaderId);

	// Check for shader compile errors
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << stderr << "\n" << infoLog << std::endl;

		return false;
	}

	// Compile fragment shader
	glCompileShader(fragmentShaderId);

	// Check for shader compile errors
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	// Attach compiled shaders to program
	glAttachShader(appShader, vertexShaderId);
	glAttachShader(appShader, fragmentShaderId);

	// Link shader program
	glLinkProgram(appShader);

	// Check linking errors
	glGetProgramiv(appShader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(appShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << stderr << "\n" << infoLog << std::endl;

		return false;
	}

	// User shader program
	glUseProgram(appShader);

	return true;
}
