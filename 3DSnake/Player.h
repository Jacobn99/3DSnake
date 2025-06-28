#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"

class AppContext; // Forward declaration of AppContext

class Player {
public:
	Player(AppContext appContext);
	unsigned int get_length();
	glm::vec2 get_movement_direction();
	std::vector<int>* get_body_indexes();
	std::vector<PrismObject>* get_body_cubes();
	void remove_tail();
	void move_head();
	void draw_body();
	//void add_body_part();

private:
	int headIndex;
	glm::vec2 movementDirection; // has dy, dx
	int length;
	std::vector<int> bodyIndexes;
	std::vector<PrismObject> bodyCubes;
};

#endif
