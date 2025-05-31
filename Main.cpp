#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include<stb/stb_image.h>

// Vertices coordinates;
GLfloat vertices[] =
{
	// Positions                                // Colors
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   0.41f, 0.8f, 0.5f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   0.7f, 0.03f, 0.12f,  // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   0.41f, 0.96f, 0.5f, // Upper 
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,   0.91f, 0.35f, 0.65f, // left middle
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    0.51f, 0.82f, 0.5f, // right middle
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,    0.41f, 0.87f, 0.12f, // bottom middle

};

GLuint indices[] = {
	3, 2, 4 , //top triangle
	5, 4, 1 , //right triangle
	0, 3, 5 , //left triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();
    
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//To learn about our monitor size
	//GLFWmonitor* monitor = glfwGetPrimaryMonitor();        // get the main monitor
	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);    // get the video mode of the monitor
	//std::cout << "Width: " << mode->width << std::endl;     // >> 1920
	//std::cout << "Height: " << mode->height << std::endl;   // >> 1080
	//std::cout << "Refresh rate: " << mode->refreshRate << " Hz" << std::endl;// >>144



	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800,800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);



	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1; // Create a VAO object and bind
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices)); // Generate vbo object and load vertices data into it
	EBO EBO1(indices, sizeof(indices)); // Generate EBO object and load indices data into it

	// tell OpenGL how to interpret the vertex data and link the VBO to the VAO
	// for the first attribute (position)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	// for the second attribute (color)
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 *sizeof(GLfloat)));


	//unbind them all not to accidentally modify them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Get the uniform location ýd of the scale variable in the shader
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background This color will be used to clear the back buffer
		glClearColor(0.80f, 0.50f, 0.70f, 1.00f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell opengl which shader program we want to use
		shaderProgram.Activate();
		// assinging a value to unýform and always before activating the shaderprogram
		glUniform1f(uniID, 0.6f);
		// Bind the VAO so that opengl knows which vertex array object to use
		VAO1.Bind();
		// Draw the triangle using the indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete object we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}