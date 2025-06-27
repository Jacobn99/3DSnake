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
    this->VBO = 0;
    this->VAO = 0;
    this->EBO = 0;

    this->VBO_set = false;
    this->VAO_set = false;
    this->EBO_set = false;

    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = this->default_color;
    //this->texture = nullptr;
}

Object::Object(unsigned int VBO, unsigned int VAO,  int vertexCount, Shader shader) {
    this->VBO = 0;
    this->VAO = 0;
    this->EBO = 0;

    this->VBO = VBO;
    this->VAO = VAO;

    this->VBO_set = true;
    this->VAO_set = true;
    this->EBO_set = false;

    this->vertexCount = vertexCount;
    this->shader = shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = this->default_color;
}

void Object::set_EBO(unsigned int EBO) {
	this->EBO = EBO;
    this->EBO_set = true;
}

void Object::set_VBO(unsigned int VBO) {
    this->VBO = VBO;
    this->EBO_set = true;
}

void Object::set_VAO(unsigned int VAO) {
    this->VAO = VAO;
    this->VAO_set = true;
}
unsigned int Object::get_EBO() {
    assert(this->EBO_set);
    return this->EBO;
}
unsigned int Object::get_VBO() {
    assert(this->VBO_set);
    return this->VBO;
}
unsigned int Object::get_VAO() {
    assert(this->VAO_set);
    return this->VAO;
}
bool Object::is_EBO_set() {
    return this->EBO_set;
}
bool Object::is_VBO_set() {
    return this->VBO_set;
}
bool Object::is_VAO_set() {
    return this->VAO_set;
}
void Object::set_color(glm::vec3 color) {
    this->color = color;
}
glm::vec3 Object::get_color() {
    return this->color;
}
Shader Object::get_shader() {
    return this->shader;
}
glm::mat4 Object::get_model() {
    return this->model;
}
int Object::get_vertexCount() {
    return this->vertexCount;
}
void Object::set_position(glm::vec3 position) {
    this->model = glm::translate(this->model, position);
}
void Object::generate_buffers(float vertices[], size_t size, GLenum drawType) {
    glGenVertexArrays(1, &(this->VAO));
    this->VAO_set = true;
    glBindVertexArray(this->get_VAO());

    glGenBuffers(1, &(this->VBO));
    this->VBO_set = true;
    glBindBuffer(GL_ARRAY_BUFFER, this->get_VBO());
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
    printf("4\n");
}
void Object::delete_buffers() {
    if (this->is_VAO_set()) {
        glDeleteBuffers(1, &(this->VBO));
    }
    if (this->is_EBO_set()) {
        glDeleteBuffers(1, &(this->EBO));
	}
    if (this->is_VAO_set()) {
        glDeleteVertexArrays(1, &(this->VAO));
    }
}