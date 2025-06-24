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
    this->VBO = new unsigned int;
    this->VAO = new unsigned int;
    this->EBO = new unsigned int;

    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = this->default_color;
}

Object::Object(unsigned int VBO, unsigned int VAO,  int vertexCount, Shader shader) {
    this->VBO = new unsigned int;
    this->VAO = new unsigned int;
    this->EBO = new unsigned int;

    *(this->VBO) = VBO;
    *(this->VAO) = VAO;

    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = this->default_color;
}

void Object::generate_buffers(float vertices[], size_t size, GLenum drawType) {
    glGenVertexArrays(1, &*((this->VAO)));
    glBindVertexArray(*(this->VAO));

    glGenBuffers(1, &*((this->VBO)));
    glBindBuffer(GL_ARRAY_BUFFER, *(this->VBO));
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
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
void Object::set_color(glm::vec3 color) {
    this->color = color;
}

void Object::add_default_attributes() {
    bind_VAO(*this);
    //Add vec3 as attribute to vertex object (position attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coords attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unbind_buffers();
}

void Object::set_position(glm::vec3 position) {
    this->model = glm::translate(this->model, position);
}

void Object::draw_object() {
    assert(is_object(*this) && this->VAO != NULL);
    bind_VAO(*this);
    this->shader.setVec3("inputColor", this->color);
    this->shader.setMat4("model", this->model);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
    this->shader.setVec3("inputColor", this->default_color);
}