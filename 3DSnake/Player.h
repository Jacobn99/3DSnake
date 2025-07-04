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
enum ActionTypes {TURN, GROW, MOVE, NO_CHANGE};

class Player {
public:
	Player() = default;
	Player(AppContext appContext);
	unsigned int get_length();
	std::vector<int>& get_body_indexes();
	std::deque<PrismObject>& get_body_cubes();
	void remove_tail();
	void move_body(float deltaTime);
	void draw_body(AppContext appContext);
	void add_body_part(PrismObject prism, unsigned int tableIndex, bool isGrowing);
	void add_body_part(unsigned int tableIndex, AppContext appContext, bool isGrowing);
	void change_direction(Direction direction, AppContext appContext);
	Direction get_head_direction();

private:
	int headIndex;
	Direction headDirection;
	Direction tailDirection;
	int length;
	std::vector<int> bodyIndexes;
	std::deque<PrismObject> bodyCubes;
	float speed;
};

glm::vec3 get_new_head_position(Player& player, AppContext appContext);
glm::vec3 get_grid_clamped_position(glm::vec3 position);

#endif
