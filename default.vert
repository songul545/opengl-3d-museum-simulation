#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Vertex color input and set layout location
layout (location = 2) in vec2 aTex; // Texture coordinate input
out vec3 color; // Output color to fragment shader
out vec2 TexCoord; // Output texture coordinate to fragment shader

uniform float scale;		// declared uniform variable for scaling
uniform mat4 model; // Model matrix for transformations
uniform mat4 view; // View matrix for camera transformations
uniform mat4 proj; // Projection matrix for perspective 

void main()
{                      // apply the scale to the vertex position
     gl_Position = proj * view * model * vec4(aPos, 1.0);
   color = aColor;
   TexCoord = aTex; // Pass texture coordinates to fragment shader

}