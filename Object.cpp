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
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"

Object::Object(int vertexCount, Shader& shader, AppContext appContext) {
    this->VBO = 0;
    this->VAO = 0;
    this->EBO = 0;

    this->VBO_set = false;
    this->VAO_set = false;
    this->EBO_set = false;

    this->vertexCount = vertexCount;
    this->shader = &shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = appContext.get_object_manager().get_default_color();
    this->textureManager = &appContext.get_texture_manager();

    this->currentAssignedPosition = glm::vec3(1.0f);
    this->currentScale = glm::vec3(1.0f);
    this->isQueuedTransformation = false;
}

Object::Object(unsigned int VBO, unsigned int VAO,  int vertexCount, Shader& shader, AppContext appContext) {
    this->VBO = 0;
    this->VAO = 0;
    this->EBO = 0;

    this->VBO = VBO;
    this->VAO = VAO;

    this->VBO_set = true;
    this->VAO_set = true;
    this->EBO_set = false;

    this->vertexCount = vertexCount;
    this->shader = &shader;
    this->model = glm::mat4(1.0f);
    this->isTextured = false;
    this->color = appContext.get_object_manager().get_default_color();
    this->textureManager = &appContext.get_texture_manager();

    this->currentAssignedPosition = glm::vec3(1.0f);
    this->currentScale = glm::vec3(1.0f);
    this->isQueuedTransformation = false;
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
Shader& Object::get_shader() {
    return *this->shader;
}
void Object::set_shader(Shader* shader) {
    this->shader = shader;
}
glm::mat4 Object::get_model() {
    return this->model;
}
void Object::set_model(glm::mat4 model) {
    this->model = model;
}
int Object::get_vertexCount() {
    return this->vertexCount;
}
void Object::set_vertexCount(int vertexCount) {
	this->vertexCount = vertexCount;
}
void Object::set_texture(Texture texture) {
    this->texture = texture;
    this->isTextured = true;
}
Texture Object::get_texture() {
	assert(this->isTextured);
    return this->texture;
}
bool Object::is_textured() {
	return this->isTextured;
}
TextureManager& Object::get_texture_manager() {
    return *this->textureManager;
}
void Object::set_texture_manager(TextureManager* textureManager) {
    this->textureManager = textureManager;
}
void Object::generate_buffers(float* vertices, size_t size, GLenum drawType) {
    glGenVertexArrays(1, &(this->VAO));
    this->VAO_set = true;
    glBindVertexArray(this->get_VAO());

    glGenBuffers(1, &(this->VBO));
    this->VBO_set = true;
    glBindBuffer(GL_ARRAY_BUFFER, this->get_VBO());
    assert(vertices != NULL && vertices != nullptr);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
}
void Object::delete_object(bool deleteTexture) {
    if (this->is_VAO_set()) {
        glDeleteBuffers(1, &(this->VBO));
    }
    if (this->is_EBO_set()) {
        glDeleteBuffers(1, &(this->EBO));
	}
    if (this->is_VAO_set()) {
        glDeleteVertexArrays(1, &(this->VAO));
    }
    if(this->isTextured && deleteTexture) {
		this->texture.delete_texture();
	}
}
void Object::set_scale(glm::vec3 scale) {
    this->currentScale = scale;
    this->isQueuedTransformation = true;
}
glm::vec3 Object::get_scale() {
    return this->currentScale;
}
void Object::set_position(glm::vec3 position) {
    this->currentAssignedPosition = position;
    this->isQueuedTransformation = true;
}
glm::vec3 Object::get_position() {
    return this->currentAssignedPosition;
}