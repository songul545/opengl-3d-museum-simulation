#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <cmath>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 0.9f, 0.7f, 1.0f);\n"

"}\n\0";


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

	// Create a vertex shader object and get ýts ID 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// load the vertex shader source code into the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	// Create a fragment shader object and get its ID
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// load the fragment shader source code into the fragment shader object 
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	// create shader program object and get its ID 
	// A shader program is a holder(container) of vertex and fragment shaders
	// it is used to link the shaders together so that they can work in harmony
	GLuint shaderProgram = glCreateProgram();
	// Attach the vertex shader to the shader program	
	glAttachShader(shaderProgram, vertexShader);
	// Attach the fragment shader to the shader program
	glAttachShader(shaderProgram, fragmentShader);
	// Links the vertex and fragment shaders into one executable shader program.
	glLinkProgram(shaderProgram);

	// Delete the vertex and fragment shaders as they are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates;
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] = {
		0, 3, 5 , //left triangle
		3, 2, 4 , //top triangle
		5, 4, 1 , //right triangle
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO,EBO;
	//// Generate the VAO, VBO, EBO with only 1 object each get its ID
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind VBO and specify it as a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// LOAD the vertices data into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Bind EBO and specify it as a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Load indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// configure the vertex attributes so openGL knows how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Enable the vertex attribute array at index 0 and now opengl knows to use ýt 
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO so that we don't accidentally modify them if we bind another VBO or VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// Specify the color of the background This color will be used to clear the back buffer
	// The parameters are the red, green, blue and alpha values .The values are between 0.0 and 1.0 
	// alpha is the transparency of the color
	glClearColor(0.80f, 0.50f, 0.70f, 1.00f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background This color will be used to clear the back buffer
		glClearColor(0.80f, 0.50f, 0.70f, 1.00f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell opengl which shader program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so that opengl knows which vertex array object to use
		glBindVertexArray(VAO);
		// Draw the triangle using the indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete object we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}