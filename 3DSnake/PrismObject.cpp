#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\stb_image.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"


//After making vertices, go through every one and look for value where x = xNeg, x = xPos and so one for each coordinate. 
//Then store xNeg, xPos, yNeg, yPos, zNeg, zPos lists of indexes to edit when extending a prism in that direction
std::vector<float> generate_prism_vertices(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range) {
    std::vector<float> vertices = {
        // Each row is a vertex
        // X,Y,Z coords and texture coordinates (U,V)
        //Front
        xNeg, yNeg, zNeg, 0.0f, 0.0f,
        xPos, yNeg, zNeg, range, 0.0f,
        xPos, yPos, zNeg, range, range,
        xPos, yPos, zNeg, range, range,
        xNeg, yPos, zNeg, 0.0f, range,
        xNeg, yNeg, zNeg, 0.0f, 0.0f,

        //Back
        xNeg, yNeg, zPos, 0.0f, 0.0f,
        xPos, yNeg, zPos, range, 0.0f,
        xPos, yPos, zPos, range, range,
        xPos, yPos, zPos, range, range,
        xNeg, yPos, zPos, 0.0f, range,
        xNeg, yNeg, zPos, 0.0f, 0.0f,

        //Left
        xNeg, yPos, zPos, range, 0.0f,
        xNeg, yPos, zNeg, range, range,
        xNeg, yNeg, zNeg, 0.0f, range,
        xNeg, yNeg, zNeg, 0.0f, range,
        xNeg, yNeg, zPos, 0.0f, 0.0f,
        xNeg, yPos, zPos, range, 0.0f,

        //Right
        xPos, yPos, zPos, range, 0.0f,
        xPos, yPos, zNeg, range, range,
        xPos, yNeg, zNeg, 0.0f, range,
        xPos, yNeg, zNeg, 0.0f, range,
        xPos, yNeg, zPos, 0.0f, 0.0f,
        xPos, yPos, zPos, range, 0.0f,

        //Bottom
        xNeg, yNeg, zNeg, 0.0f, range,
        xPos, yNeg, zNeg, range, range,
        xPos, yNeg, zPos, range, 0.0f,
        xPos, yNeg, zPos, range, 0.0f,
        xNeg, yNeg, zPos, 0.0f, 0.0f,
        xNeg, yNeg, zNeg, 0.0f, range,

        //Top
        xNeg, yPos, zNeg, 0.0f, range,
        xPos, yPos, zNeg, range, range,
        xPos, yPos, zPos, range, 0.0f,
        xPos, yPos, zPos, range, 0.0f,
        xNeg, yPos, zPos, 0.0f, 0.0f,
        xNeg, yPos, zNeg, 0.0f, range
    };
    return vertices;
}
void generate_prism(PrismObject& prism, AppContext appContext, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range) {
    std::vector<float> vertices = generate_prism_vertices(xNeg, xPos, yNeg, yPos, zNeg, zPos, range);
    prism.vertices = &vertices;

    prism.generate_buffers((*prism.vertices).data(), sizeof(prism.vertices) * (*prism.vertices).size(), GL_STATIC_DRAW);
    appContext.get_object_manager().add_default_attributes(prism);
    prism.orientationChanged = false;
}

void generate_prism(PrismObject& prism, std::vector<float> vertices, AppContext appContext) {
    prism.vertices = &vertices;
    prism.generate_buffers(vertices.data(), (vertices).size() * sizeof(*(prism.vertices)), GL_STATIC_DRAW);

    prism.generate_buffers((*prism.vertices).data(), sizeof(prism.vertices) * (*prism.vertices).size(), GL_STATIC_DRAW);
    appContext.get_object_manager().add_default_attributes(prism);
    prism.orientationChanged = false;
}

void change_orientation(PrismObject& prism, Direction direction, AppContext appContext) {
	ObjectManager& objectManager = appContext.get_object_manager();
    switch (direction) {
    case FORWARD:
        prism.vertices = &objectManager.get_front_orientation();
        break;
    case BACKWARD:
        prism.vertices = &objectManager.get_back_orientation();
        break;
    case LEFT:
        prism.vertices = &objectManager.get_left_orientation();
        break;
    case RIGHT:
        prism.vertices = &objectManager.get_right_orientation();
        break;
    }
    prism.orientationChanged = true;
    //objectManager.update_VBO(prism, *(prism.vertices), GL_STATIC_DRAW);
}