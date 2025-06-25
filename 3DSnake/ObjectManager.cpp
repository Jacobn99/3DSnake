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

bool is_object(Object object) {
    return object.get_VBO() != NULL && object.get_VAO() != NULL;
        //object.get_vertexAttributeLoc() != NULL/* && object.get_vertexAttributeStart() != NULL*/;
}

void unbind_buffers() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void bind_object_buffers(Object object) {
    assert(is_object(object));
    if (object.get_EBO() != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(object.get_EBO()));
    }
    glBindBuffer(GL_ARRAY_BUFFER, *(object.get_VBO()));
    glBindVertexArray(*(object.get_VAO()));
}
void bind_VAO(Object object) {
    assert(is_object(object));
    glBindVertexArray(*(object.get_VAO()));
}
void bind_VBO(Object object) {
    assert(is_object(object));
    glBindBuffer(GL_ARRAY_BUFFER, *(object.get_VBO()));
}
void bind_EBO(Object object) {
    assert(is_object(object));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(object.get_EBO()));
}

void generate_buffers(Object object, float vertices[], size_t size, GLenum drawType) {
    glGenVertexArrays(1, &*((object.get_VAO())));
    glBindVertexArray(*(object.get_VAO()));

    glGenBuffers(1, &*((object.get_VBO())));
    glBindBuffer(GL_ARRAY_BUFFER, *(object.get_VBO()));
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
}
void add_default_attributes(Object object) {
    bind_VAO(object);
    //Add vec3 as attribute to vertex object (position attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coords attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unbind_buffers();
}
void draw_object(Object object) {
    assert(is_object(object) && object.get_VAO() != NULL);
    bind_VAO(object);
    object.get_shader().setVec3("inputColor", object.get_color());
    object.get_shader().setMat4("model", object.get_model());
    glDrawArrays(GL_TRIANGLES, 0, object.get_vertexCount());
    object.get_shader().setVec3("inputColor", object.default_color);
}