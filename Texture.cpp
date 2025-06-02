#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	// texture
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true); // Flip the image vertically so it displays correctly in OpenGL
	// assigned width, height and number of color channels to the variables above and returns pixel data
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	std::cout << "Image name: " << image << " Image width: " << widthImg << ", height: " << heightImg << ", channels: " << numColCh << std::endl;
	 glGenTextures(1, &ID); // Generate a texture object
	// Activate the texture unit specified by slot
	glActiveTexture(slot);
	// bind the texture object to the textype target
	glBindTexture(texType, ID);


	// set the texture parameters when the texture  ýs mýnified or magnified
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // nearest neighbor pixel for minification
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // nearest neighbor pixel for magnification
	//Controls what happens when texture coordinates go beyond 0.0 - 1.0
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT); // repeat the texture horizontally
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT); // repeat the texture vertically

	// Load the texture data into the texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generate mipmaps for the texture ýt helps with texture filtering when the texture is viewed at different distances
	glGenerateMipmap(texType);


	stbi_image_free(bytes); // Free the pixel data after loading it into the texture object
	// Unbind the texture object so we don't accidentally modify it
	glBindTexture(texType, 0);
}

	void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
	{
		GLuint unitex = glGetUniformLocation(shader.ID, uniform);
		// Assign the texture unit to the uniform variable  in the shader
		shader.Activate(); // Activate the shader program before setting the uniform
		glUniform1i(unitex, unit); // set the uniform to the texture unit
		if (unitex == -1) {
			std::cout << "Warning: tex0 uniform not found or not used in shader." << std::endl;
		}
	}

	void Texture::Bind()
	{
		glBindTexture(type, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(type, 0);
	}
	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}