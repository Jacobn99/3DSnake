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


void PrismObject::generate_prism(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range) {
    float vertices[] = {
        xNeg, yNeg, zNeg,  0.0f, 0.0f,
        xPos, yNeg, zNeg,  range, 0.0f,
        xPos, yPos, zNeg,  range, range,
        xPos, yPos, zNeg,  range, range,
        xNeg, yPos, zNeg,  0.0f, range,
        xNeg, yNeg, zNeg,  0.0f, 0.0f,

        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xPos, yNeg, zPos,  range, 0.0f,
        xPos, yPos, zPos,  range, range,
        xPos, yPos, zPos,  range, range,
        xNeg, yPos, zPos,  0.0f, range,
        xNeg, yNeg, zPos,  0.0f, 0.0f,

        xNeg, yPos, zPos,  range, 0.0f,
        xNeg, yPos, zNeg,  range, range,
        xNeg, yNeg, zNeg,  0.0f, range,
        xNeg, yNeg, zNeg,  0.0f, range,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yPos, zPos,  range, 0.0f,

        xPos, yPos, zPos,  range, 0.0f,
        xPos, yPos, zNeg,  range, range,
        xPos, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zPos,  0.0f, 0.0f,
        xPos, yPos, zPos,  range, 0.0f,

        xNeg, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zNeg,  range, range,
        xPos, yNeg, zPos,  range, 0.0f,
        xPos, yNeg, zPos,  range, 0.0f,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yNeg, zNeg,  0.0f, range,

        xNeg, yPos, zNeg,  0.0f, range,
        xPos, yPos, zNeg,  range, range,
        xPos, yPos, zPos,  range, 0.0f,
        xPos, yPos, zPos,  range, 0.0f,
        xNeg, yPos, zPos,  0.0f, 0.0f,
        xNeg, yPos, zNeg,  0.0f, range
    };

    this->generate_buffers(vertices, sizeof(vertices), GL_STATIC_DRAW);
    add_default_attributes(*this);
}