#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"Texture.h"
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates;
GLfloat vertices[] =
{
	// Positions            // Colors         // Texture Coords
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	   0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	GLFWwindow* window = glfwCreateWindow(width,height, "YoutubeOpenGL", NULL, NULL);
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
	glViewport(0, 0, width, height);

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
	// for the third attribute (texture coordinates)
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 *sizeof(GLfloat)));


	//unbind them all not to accidentally modify them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Get the uniform location ýd of the scale variable in the shader
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Load the texture from the file and create a texture object
	Texture trflag("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	trflag.texUnit(shaderProgram, "tex0", 0); // Assign the texture unit to the shader uniform

	// Variables that help the rotation of the pyramid
    float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer so ýt doesnt look like the pyramid is going through itself
	glEnable(GL_DEPTH_TEST);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background This color will be used to clear the back buffer
		glClearColor(0.80f, 0.50f, 0.70f, 1.00f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// tell opengl which shader program we want to use
		shaderProgram.Activate();
		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= (1.0 / 60.0)) // If 1/60 seconds have passed, we rotate the pyramid
		{
			rotation += 0.5f; // Rotate the pyramid by 0.5 degrees 
			// both rotatýon and time diffrence affect the speed
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f); // Create a model matrix to transform the object like scaling, rotation, translation etc.
		glm::mat4 view = glm::mat4(1.0f); // Create a view matrix to position the camera
		glm::mat4 proj = glm::mat4(1.0f);  //defining how a 3d object is projected onto a 2d screen

		// Rotate the model around the Y - axis
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); 
		//view = glm::rotate(view, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f),(float)(width/height), 0.1f, 100.0f); 
		// Create a perspective projection matrix with a 45 degree field of view, aspect ratio of width/height, near plane at 0.1 and far plane at 100.0


		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// assinging a value to unýform and always before activating the shaderprogram
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so that opengl knows which vertex array object to use
		trflag.Bind(); // Bind the texture so ýt appears ýn render 
		VAO1.Bind();
		// Draw the triangle using the indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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