#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Vertex color input and set layout location
layout (location = 2) in vec2 aTex; // Texture coordinate input
out vec3 color; // Output color to fragment shader
out vec2 TexCoord; // Output texture coordinate to fragment shader

uniform mat4 camMatrix; // Camera matrix
void main()
{   
   // Transform the vertex position using the camera matrix
   gl_Position = camMatrix * vec4(aPos, 1.0);
   color = aColor;
   TexCoord = aTex; // Pass texture coordinates to fragment shader

}