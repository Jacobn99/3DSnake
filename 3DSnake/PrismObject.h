#ifndef PRISM_OBJECT_H
#define PRISM_OBJECT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include <vector>
#include <stdio.h>
#include <iostream>

//enum Direction { FORWARD, BACKWARD, LEFT, RIGHT }; // Define the Direction enum

class PrismObject : public Object {
public:
	using Object::Object;
	PrismObject(int vertexCount, Shader& shader, AppContext appContext);
	std::vector<float>* vertices;
	bool orientationChanged;
private:
	bool changeQueued;
};

class SnakeScaleObject : public PrismObject {
public:
	using PrismObject::PrismObject;
	SnakeScaleObject(glm::vec2 tileIndex, int vertexCount, Shader& shader, AppContext appContext);
private:
	glm::vec2 tileLocation;
};

void generate_prism(PrismObject& prism, AppContext appContext, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
void generate_prism(PrismObject& prism, std::vector<float>& vertices, AppContext appContext);
void set_orientation(PrismObject& prism, Direction direction, AppContext appContext);
std::vector<float> generate_prism_vertices(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);


#endif
