#ifndef PRISM_OBJECT_H
#define PRISM_OBJECT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"

class PrismObject : public Object {
public:
	using Object::Object;
	void generate_prism(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
private:

};

#endif
