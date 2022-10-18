#include <iostream>
#include <cstdlib>
#include <GL/glew.h> // GLEW library
#include <GLFW/glfw3.h> // GLFW library

#include "shader.hpp"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Module 3 Assignment"

// Resize window
void ResizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

// Entry point of application
int main(void) {

	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit()) {
		return -1;
	};

	glfwWindowHint(GLFW_SAMPLES, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Just in case macOS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Open window and create OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (!window) {
		std::cout << "Error:  " << stderr << " Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the Window Context Current
	glfwMakeContextCurrent(window);

	// Window resize
	glfwSetFramebufferSizeCallback(window, ResizeWindow);

	// Initialize GLEW and needed for core profile
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << stderr << " Failed to initialize GLEW\n" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Set input mode to capture escape key
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set background to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable dept test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if too close to camera
	glDepthFunc(GL_LESS);

	// Create vertex array ID variable
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//  Create and Compile GLSL program from shaders
	GLuint programID = LoadShaders("includes/shaderfiles/TransformVertexShader.vertexshader", "includes/shaderfiles/ColorFragmentShader.fragmentshader");

	// Get a handle for the model, view, projection (MVP) uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Create perspective projection
	glm::mat4 projection = glm::perspective(glm::radians(30.0f), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Transforms the camera:  Move camera backwards
		//glm::mat4 view = glm::translate(glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 view = glm::lookAt(
		glm::vec3(4.0f, 3.0f, -3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	// Model matrix: Identity matrix
	glm::mat4 model = glm::mat4(1.0f);

	// Scales the shape down by 2
	glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

	// Rotate shape by 15 degrees on y axis
	glm::mat4 rotationY = glm::rotate(glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Rotate shape by 15 degrees on z axis
	glm::mat4 rotationZ = glm::rotate(glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	// Move object to origin
	glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.5f, 0.0f));

	// Transformations are applied right-to-left
	model = translation * rotationY * rotationZ * scale;

	// Model View Projection : Multiplication of two triangles
	glm::mat4 MVP = projection * view * model;

	// Vertices used to create the triangles
	static const GLfloat vertices[] = {
       -0.5f,  -0.5f,  -0.5f,
        0.5f,  -0.5f,  -0.5f,
        0.0f,	0.5f,	0.0f,

       -0.5f,  -0.5f,	1.0f,
        0.5f,  -0.5f,	0.5f,
        0.0f,	0.5f,	0.0f,

       -0.5f,  -0.5f,  -0.5f,
	   -0.5f,  -0.5f,	0.5f,
		0.0f,	0.5f,	0.0f,

		0.5f,  -0.5f,  -0.5f,
		0.5f,  -0.5f,	0.5f,
		0.0f,	0.5f,	0.0f,

		0.5f,  -0.5f,  -0.5f,
		0.5f,  -0.5f,	0.5f,
		0.0f,	0.5f,	0.0f,

	   -0.5f,  -0.5f,	0.5f,
	   -0.5f,  -0.5f,  -0.5f,
		0.0f,	0.5f,	0.0f,
	};

	// Colors of triangles
	static const GLfloat colors[] = {
		
		1.0f,	0.9f,	0.38f,	// Yellow
		1.0f,	0.37f,	0.95f,	// Pink
		1.0f,	0.9f,	0.93f,	// White

		0.31f,	0.89f,	1.0f,	// Bright Blue
		1.0f,	0.37f,	0.95f,	// Pink
		0.91f,	0.96f,	1.0f,	// White

		1.0f,	0.9f,	0.38f,	// Yellow
		1.0f,	0.37f,	0.95f,	// Pink
		1.0f,	0.9f,	0.93f,	// White 

		1.0f,	0.9f,	0.38f,	// Yellow
		1.0f,	0.37f,	0.95f,	// Pink
		1.0f,	0.9f,	0.93f,	// White

		0.31f,	0.89f,	1.0f,	// Bright Blue
		1.0f,	0.37f,	0.95f,	// Pink
		0.91f,	0.96f,	1.0f,	// White

		0.31f,	0.89f,	1.0f,	// Bright Blue
		1.0f,	0.37f,	0.95f,	// Pink
		0.91f,	0.96f,	1.0f,	// White
	};

	// Generate buffers for vertices
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Generate buffers for colors
	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// Loop while window being shown
	while (!glfwWindowShouldClose(window)) {

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use shader
		glUseProgram(programID);

		// Send transformation to the currently bound shader
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// First attribute buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		// Create Vertex Attribute Pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Second attribute buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

		// Create Verte Attribute Pointer
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 9 * 6);

		// Disable Attribute Arrays
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		// Swap buffers
		glfwSwapBuffers(window);

		// Poll events
		glfwPollEvents();

		// Detect escape key being pressed and close window
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
	}
}

	