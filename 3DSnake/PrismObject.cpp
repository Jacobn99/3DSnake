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

//After making vertices, go through every one and look for value where x = xNeg, x = xPos and so one for each coordinate. 
//Then store xNeg, xPos, yNeg, yPos, zNeg, zPos lists of indexes to edit when extending a prism in that direction
void generate_prism(PrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range) {
    (*prism).vertices = {
        // Each row is a vertex
        // X,Y,Z coords and texture coordinates (U,V)
        //Front
        xNeg, yNeg, zNeg,  0.0f, 0.0f,
        xPos, yNeg, zNeg,  range, 0.0f,
        xPos, yPos, zNeg,  range, range,
        xPos, yPos, zNeg,  range, range,
        xNeg, yPos, zNeg,  0.0f, range,
        xNeg, yNeg, zNeg,  0.0f, 0.0f,

        //Back
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xPos, yNeg, zPos,  range, 0.0f,
        xPos, yPos, zPos,  range, range,
        xPos, yPos, zPos,  range, range,
        xNeg, yPos, zPos,  0.0f, range,
        xNeg, yNeg, zPos,  0.0f, 0.0f,

        //Left
        xNeg, yPos, zPos,  range, 0.0f,
        xNeg, yPos, zNeg,  range, range,
        xNeg, yNeg, zNeg,  0.0f, range,
        xNeg, yNeg, zNeg,  0.0f, range,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yPos, zPos,  range, 0.0f,

        //Right
        xPos, yPos, zPos,  range, 0.0f,
        xPos, yPos, zNeg,  range, range,
        xPos, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zPos,  0.0f, 0.0f,
        xPos, yPos, zPos,  range, 0.0f,

        //Bottom
        xNeg, yNeg, zNeg,  0.0f, range,
        xPos, yNeg, zNeg,  range, range,
        xPos, yNeg, zPos,  range, 0.0f,
        xPos, yNeg, zPos,  range, 0.0f,
        xNeg, yNeg, zPos,  0.0f, 0.0f,
        xNeg, yNeg, zNeg,  0.0f, range,

        //Top
        xNeg, yPos, zNeg,  0.0f, range,
        xPos, yPos, zNeg,  range, range,
        xPos, yPos, zPos,  range, 0.0f,
        xPos, yPos, zPos,  range, 0.0f,
        xNeg, yPos, zPos,  0.0f, 0.0f,
        xNeg, yPos, zNeg,  0.0f, range
    };

    (*prism).generate_buffers((*prism).vertices.data(), sizeof((*prism).vertices) * (*prism).vertices.size(), GL_STATIC_DRAW);
    add_default_attributes((*prism));
}
void label_indices(ExtendablePrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos) {
    std::vector<float> vertices = (*prism).vertices;
    (*prism).xNegIndices = std::vector<unsigned int>();
    (*prism).xPosIndices = std::vector<unsigned int>();
    (*prism).yNegIndices = std::vector<unsigned int>();
    (*prism).yPosIndices = std::vector<unsigned int>();
    (*prism).zNegIndices = std::vector<unsigned int>();
    (*prism).zPosIndices = std::vector<unsigned int>();

    for (int i = 0; i < vertices.size(); i += 5) {
        if (vertices[i] == xNeg) (*prism).xNegIndices.push_back(i);
        else if (vertices[i] == xPos) (*prism).xPosIndices.push_back(i);
    }
    for (int i = 1; i < vertices.size(); i += 5) {
        if (vertices[i] == yNeg) (*prism).yNegIndices.push_back(i);
        else if (vertices[i] == yPos) (*prism).yPosIndices.push_back(i);
    }
    for (int i = 2; i < vertices.size(); i += 5) {
        if (vertices[i] == zNeg) (*prism).zNegIndices.push_back(i);
        else if (vertices[i] == zPos) (*prism).zPosIndices.push_back(i);
    }
}
void generate_extendable_prism(ExtendablePrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range) {
    generate_prism(prism, xNeg, xPos, yNeg, yPos, zNeg, zPos, range);
    label_indices(prism, xNeg, xPos, yNeg, yPos, zNeg, zPos);
}

void ExtendablePrismObject::extrude_face(Faces face, float change) {
	switch (face) {
		case TOP:
            for (unsigned int i : this->yPosIndices) {
                this->vertices[i] += change;
                }
			break;
		case BOTTOM:
            for (unsigned int i : this->yNegIndices) {
                this->vertices[i] -= change;
            }
			break;
		case RIGHT:
            for (unsigned int i : this->xPosIndices) {
                this->vertices[i] += change;
            }
			break;
		case LEFT:
            for (unsigned int i : this->xNegIndices) {
                this->vertices[i] -= change;
            }
			break;
		case FRONT:
            for (unsigned int i : this->zNegIndices) {
                this->vertices[i] -= change;
            }
			break;
		case BACK:
            for (unsigned int i : this->zPosIndices) {
                this->vertices[i] += change;
            }
			break;
	}
    glBindBuffer(GL_ARRAY_BUFFER, this->get_VBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
}