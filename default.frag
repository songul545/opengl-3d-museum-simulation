#version 330 core
out vec4 FragColor; // Output color to framebuffer
in vec3 color; // Input color from vertex shader

void main()
{
   FragColor = vec4(color, 1.0f); // we add our color ýnput add 1 for opacity and now our output vec4 ready

}