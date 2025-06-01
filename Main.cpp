#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"Texture.h"
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include<stb/stb_image.h>


// Vertices coordinates;
GLfloat vertices[] =
{
	// Positions            // Colors         // Texture Coords
	-0.5f, -0.5f, 0.0f,   0.41f, 0.8f, 0.9f,   0.0f, 0.0f,// lower left 
	-0.5f, 0.5f, 0.0f,   0.7f, 0.03f, 0.12f,    0.0f, 1.0f,//  upper left
	0.5f, 0.5f, 0.0f,   0.11f, 0.96f, 0.5f,      1.0f, 1.0f,// Upper right
	0.5f, -0.5f, 0.0f,   0.91f, 0.35f, 0.65f,   1.0f, 0.0f// lower right
};

GLuint indices[] = {
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8* sizeof(GLfloat), (void*)0);
	// for the second attribute (color)
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 *sizeof(GLfloat)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 *sizeof(GLfloat)));


	//unbind them all not to accidentally modify them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Get the uniform location ýd of the scale variable in the shader
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Load the texture from the file and create a texture object
	Texture trflag("trflag.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	trflag.texUnit(shaderProgram, "tex0", 0); // Assign the texture unit to the shader uniform



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
		trflag.Bind(); // Bind the texture so ýt appears ýn render 
		VAO1.Bind();
		// Draw the triangle using the indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete object we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	trflag.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}