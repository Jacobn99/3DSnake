#ifndef PRISM_OBJECT_H
#define PRISM_OBJECT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include <vector>
#include <stdio.h>
#include <iostream>

class PrismObject : public Object {
public:
	using Object::Object;
	std::vector<float> vertices;
	float xNeg;
	float xPos;
	float yNeg;
	float yPos;
	float zNeg;
	float zPos;
private:
	bool changeQueued;
};

void generate_prism(PrismObject* prism, AppContext appContext, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
void apply_orientation_changes(PrismObject* prism);


#endif
