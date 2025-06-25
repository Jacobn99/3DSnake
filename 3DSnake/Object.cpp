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