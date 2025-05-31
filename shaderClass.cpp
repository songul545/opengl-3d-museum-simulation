#include"shaderClass.h"
// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create a vertex shader object and get ýts ID 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// load the vertex shader source code into the vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	// Create a fragment shader object and get its ID
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// load the fragment shader source code into the fragment shader object 
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	// create shader program object and get its ID 
	// A shader program is a holder(container) of vertex and fragment shaders
	// it is used to link the shaders together so that they can work in harmony
    ID = glCreateProgram();
	// Attach the vertex shader to the shader program	
	glAttachShader(ID, vertexShader);
	// Attach the fragment shader to the shader program
	glAttachShader(ID, fragmentShader);
	// Links the vertex and fragment shaders into one executable shader program.
	glLinkProgram(ID);

	// Delete the vertex and fragment shaders as they are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Shader::Activate()
{
	// Use the shader program
	glUseProgram(ID);
}	
void Shader::Delete()
{
	// Delete the shader program
	glDeleteProgram(ID);
}