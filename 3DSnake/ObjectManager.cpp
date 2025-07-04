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
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"

//bool is_object(Object object) {
//    return true;
//        //object.get_vertexAttributeLoc() != NULL/* && object.get_vertexAttributeStart() != NULL*/;
//}

std::vector<float>& ObjectManager::get_front_orientation() { return this->front_orientation; }
std::vector<float>& ObjectManager::get_back_orientation() { return this->back_orientation; }
std::vector<float>& ObjectManager::get_right_orientation() { return this->right_orientation; }
std::vector<float>& ObjectManager::get_left_orientation() { return this->left_orientation; }

void ObjectManager::generate_default_vertices(AppContext appContext) {
    GameManager gameManager = appContext.get_game_manager();
    float tileSizeInUnits = gameManager.unitsPerTile;

    this->front_orientation = generate_prism_vertices(-(tileSizeInUnits/2), (tileSizeInUnits / 2), 
        -(tileSizeInUnits / 2),(tileSizeInUnits / 2), -(tileSizeInUnits), 0.0f, gameManager.sizeInTiles);

    this->back_orientation = generate_prism_vertices(-(tileSizeInUnits / 2), (tileSizeInUnits / 2),
        -(tileSizeInUnits / 2), (tileSizeInUnits / 2), 0.0f, (tileSizeInUnits), gameManager.sizeInTiles);

    this->left_orientation = generate_prism_vertices(-(tileSizeInUnits / 2), 0.0f, -(tileSizeInUnits / 2), 
        tileSizeInUnits / 2, -(tileSizeInUnits / 2), tileSizeInUnits / 2, gameManager.sizeInTiles);

    this->right_orientation = generate_prism_vertices(0.0f, tileSizeInUnits / 2, -(tileSizeInUnits / 2),
        tileSizeInUnits / 2, -(tileSizeInUnits / 2), tileSizeInUnits / 2, gameManager.sizeInTiles);
}

void ObjectManager::unbind_buffers() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void ObjectManager::bind_object_buffers(Object object) {
    assert(object.is_VAO_set() && object.is_VBO_set());
    if (object.is_EBO_set()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.get_EBO());
    }
    glBindVertexArray(object.get_VAO());
    glBindBuffer(GL_ARRAY_BUFFER, object.get_VBO());
}
void ObjectManager::bind_VAO(Object object) {
    assert(object.is_VAO_set());
    glBindVertexArray(object.get_VAO());
}
void ObjectManager::bind_VBO(Object object) {
    assert(object.is_VBO_set());
    glBindBuffer(GL_ARRAY_BUFFER, object.get_VBO());
}
void ObjectManager::bind_EBO(Object object) {
    assert(object.is_EBO_set());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.get_EBO());
}
void ObjectManager::add_default_attributes(Object object) {
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
void ObjectManager::draw_object(Object& object) {
    assert(object.is_VBO_set() && object.is_VAO_set());
    //printf("scale.z: %f\n", (*object).queuedScale.z);
    //(*object).set_model(glm::scale(glm::translate((*object).get_model(), (*object).queuedTranslation), (*object).queuedScale));
    if (object.isQueuedTransformation) {
        object.set_model(glm::scale(glm::translate(object.get_model(), object.currentPosition), object.currentScale));
        object.isQueuedTransformation = false;
    }

    bind_VAO(object);
    object.get_shader().setVec3("inputColor", object.get_color());
    object.get_shader().setMat4("model", object.get_model());
    if (object.is_textured()) {
        object.get_texture_manager().use_2D_texture(object.get_texture(), object.get_shader());
    }
    glDrawArrays(GL_TRIANGLES, 0, object.get_vertexCount());
    object.get_shader().setVec3("inputColor", object.get_color());
}

void ObjectManager::update_VBO(Object& object, std::vector<float>& vertices, GLenum drawType) {
    assert(object.is_VBO_set());
	bind_VBO(object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), vertices.data(), drawType);
    unbind_buffers();

}
void ObjectManager::draw_prism(PrismObject& prism) {
    if (prism.orientationChanged) {
        update_VBO(prism, *(prism.vertices), GL_STATIC_DRAW);
        prism.orientationChanged = false;
    }
    draw_object(prism);
}
glm::vec3 ObjectManager::get_default_color() { 
    return this->default_color;
}