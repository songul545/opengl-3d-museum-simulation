#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}                                            //vec3->3,vec4->4    //data type // total sizeof vertex // starting byte
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Bind the VBO so we can link it to the VAO
	VBO.Bind();
	// Specify the layout of the vertex attributes
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the vertex attribute array at index layout
	glEnableVertexAttribArray(layout);
	// Unbind the VBO so we don't accidentally modify it
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}