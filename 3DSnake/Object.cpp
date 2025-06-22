#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\stb_image.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"

//Things an Object object should have:
// - VBO (vertices immediately stored in here and then disgarded)
// - EBO
// - VAO
// - Ability to add textures
// - Ability to get VBO/EBO/VAO ID
// - Draw function (could provide a function object (drawArrays() in default settings if NULL) )


enum Attribute {
    Vec3,
    Color,
    Texture
};


Object::Object(float vertices[]) {
    glGenVertexArrays(1, &(this->VAO));
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &(this->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    this->EBO = -1;
}
Object::Object(unsigned int VBO, unsigned int VAO) {
    this->VBO = VBO;
    this->VAO = VAO;
    this->EBO = -1;
}

void Object::set_EBO(unsigned int EBO) {
	this->EBO = EBO;
}

void Object::add_vertex_attribute(Attribute attribute, GLuint location) {
    GLint size;
    GLenum type;
    GLboolean isNormalized;
    GLsizei attributeSize;
    const void* attributeStart;

    switch (attribute) {
        case Vec3: //0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)
            size = 3;
            type = GL_FLOAT;
            isNormalized = GL_FALSE;
            attributeSize = 5 * sizeof(float);
            attributeStart = size of things before;
            break;
        case Color:
            break;
        case Texture:
            break;
    }
}



