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
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"

//Potential bugs:
// - Objects using same VBO/VAO make their own modifications that don't carry over to other objects (ex. attribute start)
//   * solved by making these attributes pointers

//Things an Object object should have:
// - VBO (vertices immediately stored in here and then disgarded)
// - EBO
// - VAO
// - Ability to add textures
// - Ability to get VBO/EBO/VAO ID
// - Draw function (could provide a function object (drawArrays() in default settings if NULL) )


Object::Object(int vertexCount, Shader shader) {
    *(this->vertexAttributeLoc) = 0;
    *(this->vertexAttributeStart) = 0;
    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
}

Object::Object(unsigned int VBO, unsigned int VAO, GLuint* vertexAttributeLoc, GLuint* vertexAttributeStart, int vertexCount, Shader shader) {
    *(this->VBO) = VBO;
    *(this->VAO) = VAO;
    this->vertexAttributeLoc = vertexAttributeLoc;
    this->vertexAttributeStart = vertexAttributeStart;
    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
}

void Object::generate_buffers(float vertices[], GLenum drawType) {
    glGenVertexArrays(1, &*((this->VAO)));
    glBindVertexArray(*(this->VAO));

    glGenBuffers(1, &*((this->VBO)));
    glBindBuffer(GL_ARRAY_BUFFER, *(this->VBO));
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
}

void Object::set_EBO(unsigned int EBO) {
	*(this->EBO) = EBO;
}

void Object::set_VBO(unsigned int VBO) {
    *(this->VBO) = VBO;
}

void Object::set_VAO(unsigned int VAO) {
    *(this->VAO) = VAO;
}
unsigned int* Object::get_EBO() {
    return this->EBO;
}
unsigned int* Object::get_VBO() {
    return this->VBO;
}
unsigned int* Object::get_VAO() {
    return this->VAO;
}
GLuint* Object::get_vertexAttributeLoc() {
    return this->vertexAttributeLoc;
}
GLuint* Object::get_vertexAttributeStart() {
    return this->vertexAttributeStart;
}

void Object::add_vertex_attribute(Attribute attribute) {
    assert(is_object(*this));

    GLint size = 0;
    GLenum type = 0;
    GLboolean isNormalized = GL_FALSE;
    GLsizei attributeSize = 0;
    const void* attributeStart = (void*)0;

    switch (attribute) {
        case Vec3: //0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)
            size = 3;
            type = GL_FLOAT;
            isNormalized = GL_FALSE;
            attributeSize = 5 * sizeof(float);
            attributeStart = (void*)*(this->vertexAttributeStart);
            break;
        case Texture: //1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))
            size = 2;
            type = GL_FLOAT;
            isNormalized = GL_FALSE;
            attributeSize = 5 * sizeof(float);
            attributeStart = (void*)*(this->vertexAttributeStart);
            break;
        case Color: //1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))
            size = 3;
            type = GL_FLOAT;
            isNormalized = GL_FALSE;
            attributeSize = 8 * sizeof(float);
            attributeStart = (void*)*(this->vertexAttributeStart);
            break;
    }
    bind_object_buffers(*this);
    glVertexAttribPointer(*(this->vertexAttributeLoc), size, type, isNormalized, attributeSize, attributeStart);
    unbind_buffers();
    *(this->vertexAttributeStart) += attributeSize;
    *(this->vertexAttributeLoc) += 1;
}
void Object::set_position(glm::vec3 position) {
    glm::translate(this->model, position);
}

void Object::draw_object() {
    assert(is_object(*this));
    bind_VAO(*this);
    this->shader.setMat4("model", this->model);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}