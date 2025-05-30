# MUSEUM PROJECT
### BASIC INFORMATION
- GLFW (Graphics Library Framework) is a lightweight, open-source library designed for managing windows, OpenGL contexts, and handling input like keyboard, mouse, and joystick events. It is commonly used in OpenGL, OpenGL ES, and Vulkan development, providing a simple API for creating cross-platform applications.
- GLAD (GLAD Loader) is a lightweight OpenGL function loader that helps manage OpenGL extensions and function pointers. It is commonly used in graphics programming to simplify the process of accessing OpenGL functions across different platforms.
- CMAKE A build system generator is a tool that creates configuration files for a build system, which is responsible for compiling and linking source code into executable programs.
### glwf functions explanation
- glfwInit: Initializes the GLFW library. This function must be called before any other GLFW functions.
- glfwTerminate: Cleans up and closes the GLFW library. This function should be called when you are done using GLFW.
- glfwWindowHint: Sets window hints for the GLFW window. These hints control various aspects of the window's creation, such as its size, context version, and whether it should be resizable.  
`glfwWindowHint (int hint,int value )`  
-> to see possible hint parameters [windowhints](https://www.glfw.org/docs/latest/window_guide.html#window_hints)
- glfwGetPrimaryMonitor: Returns a handle to the primary monitor. This function is used to get the default monitor for the system.
- glfwGetVideoMode: Returns a pointer to the current video mode of a monitor. This function is used to get information about the display mode of a monitor.

#### GLFW typedefs explanation 
- GLFWwindow: A handle to a window created by GLFW. This type is used to represent the window in the GLFW API.
- GLFWmonitor: A handle to a monitor. This type is used to represent a monitor in the GLFW API.   
- GLFWvidmode: A structure that contains information about a video mode, such as width, height, and refresh rate. This structure is used to describe the display mode of a monitor.  
### GLFW functions explanation (cont.)
- glfwMakeContextCurrent: Sets the current OpenGL context for the specified window. This function is used to make the OpenGL context of a window current, allowing OpenGL commands to be executed on that context.
- glfwWindowShouldClose(window): Check if user wants to close the window
- glfwPollEvents: Processes events in the event queue. This function is used to handle input events, such as keyboard and mouse events, and update the window state.  


### creating a triangle  
#### :brain: SHADER STAGE FUNCTIONS
- ` GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); `
  - Creates a new shader object.
  - The `GL_VERTEX_SHADER` tells OpenGL this will be a vertex shader.  
  - Returns an ID (unsigned int) to refer to this shader.    
- `glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);`    
  - Attaches the source code (GLSL) to the shader object.   
  - Parameters:
  `vertexShader`: shader ID  
  `1`: number of source strings  
  `&vertexShaderSource`: pointer to the source code  
  `NULL`: optional array of string lengths (NULL = auto)    
	
Example
- So, the full process would be:

You load your raw materials (vertex data) into the storage bins (VBOs).  
You design your processing machine (write and compile your Vertex Shader and Fragment Shader).
You create the complete assembly line (link the shader program).
You create the instruction manual (VAO) that tells the assembly line exactly how to take materials from the bins (VBOs) and feed them into the machines (shaders).
When you want to produce something (draw your object):
You tell the factory, "Use this assembly line" (glUseProgram).
You tell it, "And here are the instructions for how the material is laid out" (glBindVertexArray).
Then, you say, "Start production!" (glDrawArrays).

