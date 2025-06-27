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


void PrismObject::generate_prism(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos) {
    float vertices[] = {
        xNeg, yNeg, zNeg,  0.0f, 0.0f,
        xPos, yNeg, zNeg,  1.0f, 0.0f,
        xPos, yPos, zNeg,  1.0f, 1.0f,
        xPos, yPos, zNeg,  1.0f, 1.0f,
        xNeg, yPos, zNeg,  0.0f, 1.0f,
        xNeg, yNeg, zNeg,  0.0f, 0.0f,

        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xPos, yNeg, zPos,  1.0f, 0.0f,
        xPos, yPos, zPos,  1.0f, 1.0f,
        xPos, yPos, zPos,  1.0f, 1.0f,
        xNeg, yPos, zPos,  0.0f, 1.0f,
        xNeg, yNeg, zPos,  0.0f, 0.0f,

        xNeg, yPos, zPos,  1.0f, 0.0f,
        xNeg, yPos, zNeg,  1.0f, 1.0f,
        xNeg, yNeg, zNeg,  0.0f, 1.0f,
        xNeg, yNeg, zNeg,  0.0f, 1.0f,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yPos, zPos,  1.0f, 0.0f,

        xPos, yPos, zPos,  1.0f, 0.0f,
        xPos, yPos, zNeg,  1.0f, 1.0f,
        xPos, yNeg, zNeg,  0.0f, 1.0f,
        xPos, yNeg, zNeg,  0.0f, 1.0f,
        xPos, yNeg, zPos,  0.0f, 0.0f,
        xPos, yPos, zPos,  1.0f, 0.0f,

        xNeg, yNeg, zNeg,  0.0f, 1.0f,
        xPos, yNeg, zNeg,  1.0f, 1.0f,
        xPos, yNeg, zPos,  1.0f, 0.0f,
        xPos, yNeg, zPos,  1.0f, 0.0f,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yNeg, zNeg,  0.0f, 1.0f,

        xNeg, yPos, zNeg,  0.0f, 1.0f,
        xPos, yPos, zNeg,  1.0f, 1.0f,
        xPos, yPos, zPos,  1.0f, 0.0f,
        xPos, yPos, zPos,  1.0f, 0.0f,
        xNeg, yPos, zPos,  0.0f, 0.0f,
        xNeg, yPos, zNeg,  0.0f, 1.0f
    };

    this->generate_buffers(vertices, sizeof(vertices), GL_STATIC_DRAW);
    add_default_attributes(*this);
}