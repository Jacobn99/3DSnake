#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"

class AppContext; // Forward declaration of AppContext

class Player {
public:
	Player() = default;
	Player(AppContext appContext);
	unsigned int get_length();
	std::vector<int>& get_body_indexes();
	std::vector<PrismObject> get_body_cubes();
	void remove_tail();
	void move_body(float deltaTime);
	void draw_body(AppContext appContext);
	void add_body_part(PrismObject prism, unsigned int tableIndex);
	void change_direction(Direction direction, AppContext appContext);
	Direction get_direction();

private:
	int headIndex;
	Direction currentDirection; // has dy, dx
	int length;
	std::vector<int> bodyIndexes;
	std::vector<PrismObject> bodyCubes;
	float speed;
};

#endif
