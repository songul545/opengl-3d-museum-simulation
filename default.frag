#version 330 core
out vec4 FragColor; // Output color to framebuffer
in vec3 color; // Input color from vertex shader
in vec2 TexCoord; // Input texture coordinates from vertex shader

uniform sampler2D tex0; // get texture unýt from main function

void main()
{
   FragColor = texture(tex0, TexCoord); 

}