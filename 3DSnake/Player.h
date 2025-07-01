#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
//#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"

class AppContext; // Forward declaration of AppContext
enum Faces;

class Player {
public:
	Player(AppContext appContext);
	unsigned int get_length();
	std::vector<int>* get_body_indexes();
	std::vector<PrismObject> get_body_cubes();
	void remove_tail();
	void move_body(float deltaTime);
	void draw_body();
	void add_body_part(PrismObject prism, unsigned int tableIndex);

private:
	int headIndex;
	//Faces currentDirection; // has dy, dx
	int length;
	std::vector<int> bodyIndexes;
	std::vector<PrismObject> bodyCubes;
};

#endif
