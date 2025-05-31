#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	// Bind the VBO so we can link it to the VAO
	VBO.Bind();
	// Specify the layout of the vertex data
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
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