#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
// these all declarations we implement in the VBO.cpp file
class VBO {
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);
	// bind the VBO
	void Bind();
	// Unbind the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif 
