#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"


class Player {
public:
	Player(GameManager gameManager);
	unsigned int get_length();
	glm::vec2 get_movement_direction();
	std::queue<int>* get_body_parts();
	void remove_tail();
	void move_head();
	void draw_body();
	//void add_body_part();

private:
	int headIndex;
	glm::vec2 movementDirection; // has dy, dx
	int length;
	std::queue<int> bodyParts;

};

#endif
