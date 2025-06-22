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
    return object.get_VBO() != NULL && object.get_VAO() != NULL &&
        object.get_vertexAttributeLoc() != NULL && object.get_vertexAttributeStart() != NULL;
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