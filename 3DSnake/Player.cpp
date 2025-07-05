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
	SnakeScaleObject head = SnakeScaleObject(glm::vec2(gameManager.sizeInTiles / 2, gameManager.sizeInTiles / 2), 
		gameManager.defaultDirection, 36, appContext.get_shader(), appContext);

	generate_snake_scale(head, appContext);
	player.add_body_part(head, gameManager.startIndex, true);
}

Player::Player(AppContext appContext) {
	//this->bodyIndexes = std::vector<int>();
	this->bodyCubes = std::deque<SnakeScaleObject>();
	this->length = 0;
	this->speed = 0.5f; // 0.5 units per second
	this->headDirection = FORWARD;

	initialize_body(*this, appContext);
}
unsigned int Player::get_length() {
	return this->length;
}
//std::vector<int>& Player::get_body_indexes() {
//	return this->bodyIndexes;
//}
std::deque<SnakeScaleObject>& Player::get_body_cubes() {
	return this->bodyCubes;
}
//void Player::remove_tail() {
//	assert(!this->bodyIndexes.empty() && !this->bodyCubes.empty());
//	//HOW DO I POP FROM FRONT!!!???
//	/*this->bodyIndexes.pop_back();
//	this->bodyCubes.pop_back();*/
//;}
void Player::move_body(float deltaTime) {
	SnakeScaleObject& head = this->bodyCubes.back();

	glm::vec3 scaleChange;
	glm::vec3 singletonPositionChange;

	switch (this->headDirection) {
		case FORWARD:
			scaleChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			singletonPositionChange = glm::vec3(0.0f, 0.0f, -this->speed * deltaTime);
			break;
		case BACKWARD:
			scaleChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			singletonPositionChange = glm::vec3(0.0f, 0.0f, this->speed * deltaTime);
			break;
		case LEFT: 
			scaleChange = glm::vec3(-this->speed * deltaTime, 0.0f, 0.0f);
			singletonPositionChange = glm::vec3(-this->speed * deltaTime, 0.0f, 0.0f);
			break;
		case RIGHT:
			scaleChange = glm::vec3(this->speed * deltaTime, 0.0f, 0.0f);
			singletonPositionChange = glm::vec3(this->speed * deltaTime, 0.0f, 0.0f);
			break;
	}
	if(length > 1) (head).set_scale((head).currentScale + scaleChange);
	else head.set_position(head.get_position() + singletonPositionChange);
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
void Player::add_body_part(AppContext appContext, bool isGrowing) {
	GameManager gameManager = appContext.get_game_manager();
	SnakeScaleObject newHead = SnakeScaleObject(get_new_head_position(*this, appContext), this->get_head_direction(), 
		36, appContext.get_shader(), appContext);
	glm::vec2 boardPosition = newHead.get_grid_position();
	glm::vec3 startLoc = gameManager.board_to_vec3(boardPosition.x, boardPosition.y);

	set_orientation(newHead, this->headDirection, appContext);
	generate_snake_scale(newHead, appContext);
	newHead.set_position(startLoc);
	//printf("scale | x: %f, y: %f, z: %f\n", newHead.get_scale().x, newHead.get_scale().y, newHead.get_scale().z);

	this->bodyCubes.push_back(newHead);
	if(isGrowing) this->length++;
}
void Player::change_direction(Direction direction, AppContext appContext) {
	if(length > 1) {
		PrismObject& prism = this->bodyCubes.front();
		set_orientation(prism, direction, appContext);
		//Undo previous position offset
		prism.set_position(prism.get_position() - appContext.get_game_manager().get_orientation_offset(this->headDirection));
		this->headDirection = direction;
		prism.set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
		prism.set_position(prism.get_position() + appContext.get_game_manager().get_orientation_offset(direction));
	}
	else this->headDirection = direction;
}
Direction Player::get_head_direction() {
	return this->headDirection;
}
glm::vec2 get_new_head_position(Player& player, AppContext appContext) {
	glm::vec2 tileOffset;
	glm::vec2 boardStart;
	Direction headDirection = player.get_head_direction();
	float unitsPerTile = appContext.get_game_manager().unitsPerTile;
	SnakeScaleObject head = player.get_body_cubes().back();

	switch (headDirection) {
	case FORWARD:
		tileOffset = glm::vec2(-1.0f, 0.0f);
		break;
	case BACKWARD:
		tileOffset = glm::vec2(1.0f, 0.0f);
		break;
	case LEFT:
		tileOffset = glm::vec2(0.0f, 1.0f);
		break;
	case RIGHT:
		tileOffset = glm::vec2(0.0f, -1.0f);
		break;
	}
	return head.get_grid_position() + tileOffset;
}
