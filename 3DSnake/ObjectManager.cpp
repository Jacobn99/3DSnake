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

//bool is_object(Object object) {
//    return true;
//        //object.get_vertexAttributeLoc() != NULL/* && object.get_vertexAttributeStart() != NULL*/;
//}

void unbind_buffers() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void bind_object_buffers(Object object) {
    assert(object.is_VAO_set() && object.is_VBO_set());
    if (object.is_EBO_set()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.get_EBO());
    }
    glBindVertexArray(object.get_VAO());
    glBindBuffer(GL_ARRAY_BUFFER, object.get_VBO());
}
void bind_VAO(Object object) {
    assert(object.is_VAO_set());
    glBindVertexArray(object.get_VAO());
}
void bind_VBO(Object object) {
    assert(object.is_VBO_set());
    glBindBuffer(GL_ARRAY_BUFFER, object.get_VBO());
}
void bind_EBO(Object object) {
    assert(object.is_EBO_set());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.get_EBO());
}
void add_default_attributes(Object object) {
	assert(object.is_VAO_set() && object.is_VBO_set() && object.get_vertexCount() > 0);
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
    assert(object.is_VBO_set() && object.is_VAO_set());
    bind_VAO(object);
    object.get_shader().setVec3("inputColor", object.get_color());
    object.get_shader().setMat4("model", object.get_model());
    if (object.is_textured()) {
        object.get_texture_manager()->use_2D_texture(object.get_texture(), object.get_shader());
    }
    glDrawArrays(GL_TRIANGLES, 0, object.get_vertexCount());
    object.get_shader().setVec3("inputColor", object.default_color);
}