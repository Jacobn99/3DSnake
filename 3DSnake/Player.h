#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include <functional>

class AppContext; // Forward declaration of AppContext

class Player {
public:
	Player() = default;
	Player(AppContext appContext);
	unsigned int get_length();
	std::queue<int> get_body_indexes();
	std::deque<SnakeScaleObject>& get_body_cubes();
	void move_body(float deltaTime, AppContext appContext);
	void draw_body(AppContext appContext);
	void add_body_part(SnakeScaleObject prism, unsigned int tableIndex, bool isGrowing);
	void add_body_part(AppContext appContext, Direction direction, bool isGrowing, bool startAsPlane);
	void queue_turn(Direction direction, AppContext appContext);
	Direction get_queued_head_direction();
	Direction get_head_direction();
	void set_head_direction(Direction newDirection);
	glm::vec2 get_head_grid_position();
	void set_head_grid_position(glm::vec2 newPosition);
	void push_body_index(glm::vec2 boardPosition, AppContext appContext);
	void pop_body_index();
	void queue_growth();
	float get_speed();
	glm::vec2 get_previous_grid_position();
	bool inNewTile;
	bool isQueuedGrow;
	Direction queuedHeadDirection;
private:
	glm::vec2 headGridPosition;
	glm::vec2 previousGridPosition;
	Direction headDirection;
	Direction tailDirection;
	int length;
	std::queue<int> bodyIndexes;
	std::deque<SnakeScaleObject> bodyCubes;
	bool canPopIndexes;	
	float speed;
};

//Player movement functions
void move_singleton(Player& player, double deltaTime, AppContext appContext);
void move_multi_segment(Player& player, double deltaTime, AppContext appContext);

//Other helper functions
void update_body_indexes(Player& player, AppContext appContext);
bool check_collision(Player& player, bool isDebug);
void turn_snake(Player& player, Direction direction, AppContext appContext);
glm::vec2 get_new_head_position(Player& player, Direction direction, AppContext appContext);
glm::vec3 getSingletonPositionChange(Player player, double deltaTime);
glm::vec3 getMovementScaleChange(float speed, Direction direction, double deltaTime);

#endif
