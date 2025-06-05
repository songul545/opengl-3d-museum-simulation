#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Quad (plane) geometry
float quadVertices[] = {
    // positions          // texCoords
    -0.5f, 0.0f, -0.5f,   0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,   8.0f, 0.0f,
     0.5f, 0.0f,  0.5f,   8.0f, 8.0f,
    -0.5f, 0.0f,  0.5f,   0.0f, 8.0f
};
unsigned int quadIndices[] = {
    0, 1, 2,
    2, 3, 0
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Museum Scene", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);

    Shader shaderProgram("default.vert", "default.frag");

    // Floor and wall textures
    Texture floorTex("stone_floor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture wallTex("brick_wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    floorTex.texUnit(shaderProgram, "tex0", 0);  // Link uniform tex0 to GL_TEXTURE0

    // Quad VAO/VBO/EBO
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(quadVertices, sizeof(quadVertices));
    EBO EBO1(quadIndices, sizeof(quadIndices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glEnable(GL_DEPTH_TEST);
    Camera camera(width, height, glm::vec3(0.0f, 1.0f, 3.0f));

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shaderProgram, "camMatrix");

        VAO1.Bind();

        float wallHeight = 80.0f;
        float wallLength = 80.0f;

        // === Floor ===
        floorTex.Bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(80.0f, 1.0f, 80.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // === Walls ===
        wallTex.Bind();

        // === Ceiling 
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, wallHeight / 2, 0.0f));
        model = glm::scale(model, glm::vec3(80.0f, 1.0f, 160.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
		// Back wall
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -80.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
            model = glm::scale(model, glm::vec3(wallLength, 0.0f, wallHeight)); 
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        
		// front wall
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 80.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
            model = glm::scale(model, glm::vec3(wallLength, 0.0f, wallHeight));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
		// Left wall
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
            model = glm::scale(model, glm::vec3(wallLength*2, 0.0f, wallHeight));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
		// Right wall
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(40.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
            model = glm::scale(model, glm::vec3(wallLength*2, 0.0f, wallHeight));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    floorTex.Delete();
    wallTex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
