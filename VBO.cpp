#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{   
	glGenBuffers(1, &ID);
	// Bind VBO and specify it as a GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	// LOAD the vertices data into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}