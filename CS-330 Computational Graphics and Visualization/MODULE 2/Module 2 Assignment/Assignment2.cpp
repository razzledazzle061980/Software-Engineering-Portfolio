#include <iostream>
#include <cstdlib>
#include <GL/glew.h> // GLEW library
#include <GLFW/glfw3.h> // GLFW library

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Module 2 Assignment"

int main(void) {

	GLFWwindow* window;

	// Initialize the Library
	if (!glfwInit()) {
		return -1;
	}

	// Create Window
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, NULL, NULL);

	// Get Frame Buffer Size of Window
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the Window Context Current
	glfwMakeContextCurrent(window);

	// Area to Which OpenGL Will Draw Objects
	glViewport(0, 0, screenWidth, screenHeight);

	// Define Properties Of Camera
	glMatrixMode(GL_PROJECTION);

	// Replace Matrix with Identity Matrix
	glLoadIdentity();

	// Create Coordinate System
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 600);

	// Default matrix Mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Vertices of Left Triangle
	GLfloat left[9] = {
		0,600,0,
		200, 300, 0,
		0, 300, 0
	};

	// Vertices of Right Triangle
	GLfloat right[9] = {
		200, 300, 0,
		400, 300, 0,
		400, 0, 0
	};

	// Color Left Triangle
	GLfloat lColor[9] = {
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	// Color Right Triangle
	GLfloat rColor[9] = {
		0, 255, 0,
		255, 0, 0,
		0, 255, 0
	};

	// Loop Until User Closes Window
	while (!glfwWindowShouldClose(window)) {
		
		glClear(GL_COLOR_BUFFER_BIT);

		// Render OpenGL
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// Left Triangle Points
		glVertexPointer(3, GL_FLOAT, 0, left);
		glColorPointer(3, GL_FLOAT, 0, lColor); // Left Triangle Color
		glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw the Triangle

		// Right Triangle Points
		glVertexPointer(3, GL_FLOAT, 0, right);
		glColorPointer(3, GL_FLOAT, 0, rColor); // Right Triangle Color
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the Triangle


		// Disable Client State - Color
		glDisableClientState(GL_COLOR_ARRAY);

		// Disable Client State - Vertex
		glDisableClientState(GL_VERTEX_ARRAY);

		// Swap Front and Back Buffers
		glfwSwapBuffers(window);

		// Poll Events
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}

	}
}