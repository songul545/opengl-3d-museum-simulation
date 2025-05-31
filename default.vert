#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Vertex color input and set layout location
out vec3 color; // Output color to fragment shader

uniform float scale;		// declared uniform variable for scaling

void main()
{                      // apply the scale to the vertex position
   gl_Position = vec4(aPos.x + aPos.x * scale , aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0); 
   color = aColor;

}