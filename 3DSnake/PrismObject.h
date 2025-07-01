#ifndef PRISM_OBJECT_H
#define PRISM_OBJECT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include <vector>
#include <stdio.h>
#include <iostream>

enum Faces {
	TOP,
	BOTTOM,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

class PrismObject : public Object {
public:
	using Object::Object;
	//void generate_prism(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
	std::vector<float> vertices;
private:
	bool changeQueued;
};

class ExtendablePrismObject : public PrismObject {
public:
	using PrismObject::PrismObject;

	void extrude_face(Faces face, float change);

	std::vector<unsigned int> xNegIndices;
	std::vector<unsigned int> xPosIndices;
	std::vector<unsigned int> yNegIndices;
	std::vector<unsigned int> yPosIndices;
	std::vector<unsigned int> zNegIndices;
	std::vector<unsigned int> zPosIndices;
private:
};

void generate_prism(PrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
void generate_extendable_prism(ExtendablePrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
void label_indices(ExtendablePrismObject* prism, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos);


#endif
