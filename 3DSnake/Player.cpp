#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Player.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"

//TODO:
// - Every tile the snake comes across will have its own snake cube
// - Remove the faces the are unecessary while playing

void initialize_body(Player& player, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	glm::vec2 gridStart = glm::vec2(gameManager.sizeInTiles / 2, gameManager.sizeInTiles / 2);
	SnakeScaleObject head = SnakeScaleObject(gridStart,
		gameManager.defaultDirection, 36, appContext.get_shader(), appContext);

	player.set_head_grid_position(gridStart);

	generate_snake_scale(head, appContext);
	player.add_body_part(head, gameManager.startIndex, true);
}

Player::Player(AppContext appContext) {
	this->bodyIndexes = std::vector<int>();
	this->bodyCubes = std::deque<SnakeScaleObject>();
	this->length = 0;
	this->speed = 0.5f; // 0.5 units per second
	this->headDirection = appContext.get_game_manager().defaultDirection;
	this->queuedHeadDirection = this->headDirection;
	this->isQueuedGrow = false;

	initialize_body(*this, appContext);
}
unsigned int Player::get_length() {
	return this->length;
}
std::vector<int>& Player::get_body_indexes() {
	return this->bodyIndexes;
}
std::deque<SnakeScaleObject>& Player::get_body_cubes() {
	return this->bodyCubes;
}
glm::vec2 Player::get_head_grid_position() {
	return this->headGridPosition;
}
void Player::set_head_grid_position(glm::vec2 newPosition) {
	this->headGridPosition = newPosition;
}
Direction Player::get_head_direction() {
	return this->headDirection;
}
void Player::set_head_direction(Direction newDirection) {
	this->headDirection = newDirection;
}
//void Player::set_queued_head_direction(Direction newDirection) {
//	this->queuedHeadDirection = newDirection;
//}
//void Player::remove_tail() {
//	assert(!this->bodyIndexes.empty() && !this->bodyCubes.empty());
//	//HOW DO I POP FROM FRONT!!!???
//	/*this->bodyIndexes.pop_back();
//	this->bodyCubes.pop_back();*/
//;}
void Player::move_body(float deltaTime, AppContext appContext) {
	SnakeScaleObject& head = this->bodyCubes.back();

	glm::vec3 scaleChange;
	glm::vec3 singletonPositionChange;
	bool isScalingX = false;
	bool isScalingZ = false;
	GameManager& gameManager = appContext.get_game_manager();

	switch (this->headDirection) {
		case FORWARD:
			scaleChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			singletonPositionChange = glm::vec3(0.0f, 0.0f, -this->speed * deltaTime);
			isScalingZ = true;
			break;
		case BACKWARD:
			scaleChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			singletonPositionChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			isScalingZ = true;
			break;
		case LEFT: 
			scaleChange = glm::vec3(this->speed * deltaTime, 0.0f, 0.0f);
			singletonPositionChange = glm::vec3(-this->speed * deltaTime, 0.0f, 0.0f);
			isScalingX = true;
			break;
		case RIGHT:
			scaleChange = glm::vec3(this->speed * deltaTime, 0.0f, 0.0f);
			singletonPositionChange = glm::vec3(this->speed * deltaTime, 0.0f, 0.0f);
			isScalingX = true;
			break;
	}
	if (length > 1) { 
		glm::vec3 oldScale;
		glm::vec3 newScale;
		bool hasRowChanged;
		bool hasColumnChanged;
		
		oldScale = head.get_scale();
		head.set_scale(head.currentScale + scaleChange);
		newScale = head.get_scale();
		int newScaleXInt = (static_cast<int>(newScale.x));
		int newScaleZInt = (static_cast<int>(newScale.z));
		/*printf("(int) oldScale | x: %d, y: %d, z: %d\n", static_cast<int>(oldScale.x), static_cast<int>(oldScale.y), static_cast<int>(oldScale.z));
		printf("(int) newScale | x: %d, y: %d, z: %d\n", static_cast<int>(newScale.x), static_cast<int>(newScale.y), static_cast<int>(newScale.z));*/

		hasRowChanged = newScaleZInt > static_cast<int>(oldScale.z);
		hasColumnChanged = newScaleXInt > static_cast<int>(oldScale.x);

		// Checks if head location must be updated
		if (hasRowChanged || hasColumnChanged) {
			this->headGridPosition += appContext.get_game_manager().get_tile_offset(this->headDirection);
			if (this->queuedHeadDirection != this->headDirection) turn_snake(*this, this->queuedHeadDirection, appContext);
		}
	}
	else {
		//if (this->queuedHeadDirection != this->headDirection) turn_snake(*this, this->headDirection, appContext);
		glm::vec3 oldPosition = head.get_position();
		head.set_position(head.get_position() + singletonPositionChange);
		glm::vec2 oldGridPosition = gameManager.vec3_to_grid_position(oldPosition);
		glm::vec2 newGridPosition = gameManager.vec3_to_grid_position(head.get_position());

		if (gameManager.vec3_to_grid_position(oldPosition) != gameManager.vec3_to_grid_position(head.get_position())) {
			turn_snake(*this, this->queuedHeadDirection, appContext);
			this->headGridPosition = gameManager.vec3_to_grid_position(head.get_position());
		}
	}
}
void Player::draw_body(AppContext appContext) {
	for (SnakeScaleObject scale : this->bodyCubes) {
		appContext.get_object_manager().draw_prism(scale);
	}
}
void Player::add_body_part(SnakeScaleObject scale, unsigned int tableIndex, bool isGrowing) {
	this->bodyCubes.push_back(scale);
	//this->bodyIndexes.push_back(tableIndex);
	if (isGrowing) this->length++;
}
void Player::add_body_part(AppContext appContext, Direction direction, bool isGrowing) {
	GameManager gameManager = appContext.get_game_manager();
	SnakeScaleObject newHead = SnakeScaleObject(get_new_head_position(*this, direction, appContext), direction,
		36, appContext.get_shader(), appContext);
	glm::vec2 boardPosition = this->get_head_grid_position();
	glm::vec3 startLoc = gameManager.board_to_vec3(boardPosition.x, boardPosition.y);
	glm::vec3 initialScale = get_initial_scaling(direction);

	generate_snake_scale(newHead, appContext);
	newHead.set_scale(initialScale); //Start with no scale
	//newHead.set_adjusted_position(startLoc, appContext);
	newHead.set_direction(direction);
	//printf("scale | x: %f, y: %f, z: %f\n", newHead.get_scale().x, newHead.get_scale().y, newHead.get_scale().z);

	this->bodyCubes.push_back(newHead);
	if(isGrowing) this->length++;
}
void Player::queue_turn(Direction direction, AppContext appContext) {
	this->queuedHeadDirection = direction;
	//if(length > 1) {
	//	add_body_part(appContext, false);
	//	SnakeScaleObject& newHead = this->bodyCubes.back();
	//	set_orientation(newHead, direction, appContext);
	//	//Undo previous position offset
	//	newHead.set_position(newHead.get_position() - appContext.get_game_manager().get_orientation_offset(this->headDirection));
	//	this->headDirection = direction;
	//	newHead.set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
	//	newHead.set_position(newHead.get_position() + appContext.get_game_manager().get_orientation_offset(direction));
	//}
	//else this->headDirection = direction;
}
glm::vec2 get_new_head_position(Player& player, Direction direction, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	//Direction headDirection = player.get_head_direction();
	glm::vec2 tileOffset = gameManager.get_tile_offset(direction);
	float unitsPerTile = gameManager.unitsPerTile;
	SnakeScaleObject head = player.get_body_cubes().back();
	glm::vec2 result = player.get_head_grid_position() + tileOffset;

	return result;
}

void turn_snake(Player& player, Direction direction, AppContext appContext) {
	if (player.get_length() > 1) {
		player.add_body_part(appContext, direction, false);
		SnakeScaleObject& newHead = player.get_body_cubes().back();
		set_orientation(newHead, direction, appContext);
		player.set_head_direction(direction);
	}
	else player.set_head_direction(direction);
}
