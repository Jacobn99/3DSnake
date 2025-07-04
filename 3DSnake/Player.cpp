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
	PrismObject prism = PrismObject(36, appContext.get_shader(), appContext);
	glm::vec3 startLoc = gameManager.board_to_vec3(gameManager.sizeInTiles / 2, gameManager.sizeInTiles / 2) + 
		gameManager.get_orientation_offset(player.get_head_direction());

	std::vector<float>& vertices = appContext.get_object_manager().get_front_orientation();
	generate_prism(prism, vertices, appContext);
	prism.set_position(startLoc);

	player.add_body_part(prism, gameManager.startIndex, true);
}

Player::Player(AppContext appContext) {
	this->bodyIndexes = std::vector<int>();
	this->bodyCubes = std::deque<PrismObject>();
	this->length = 0;
	this->speed = 0.5f; // 0.5 units per second
	this->headDirection = FORWARD;

	initialize_body(*this, appContext);
}
unsigned int Player::get_length() {
	return this->length;
}
std::vector<int>& Player::get_body_indexes() {
	return this->bodyIndexes;
}
std::deque<PrismObject>& Player::get_body_cubes() {
	return this->bodyCubes;
}
//void Player::remove_tail() {
//	assert(!this->bodyIndexes.empty() && !this->bodyCubes.empty());
//	//HOW DO I POP FROM FRONT!!!???
//	/*this->bodyIndexes.pop_back();
//	this->bodyCubes.pop_back();*/
//;}
void Player::move_body(float deltaTime) {
	PrismObject& prism = this->bodyCubes.back();

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
	if(length > 1) (prism).set_scale((prism).currentScale + scaleChange);
	else prism.set_position(prism.get_position() + singletonPositionChange);
}
void Player::draw_body(AppContext appContext) {
	for (PrismObject prism : this->bodyCubes) {
		appContext.get_object_manager().draw_prism(prism);
	}
}
void Player::add_body_part(PrismObject prism, unsigned int tableIndex, bool isGrowing) {
	this->bodyCubes.push_back(prism);
	this->bodyIndexes.push_back(tableIndex);
	if (isGrowing) this->length++;
}
//void Player::add_body_part(unsigned int tableIndex, AppContext appContext, bool isGrowing) {
//	GameManager gameManager = appContext.get_game_manager();
//	PrismObject prism = PrismObject(36, appContext.get_shader(), appContext);
//
//	
//	glm::vec3 headLoc = this->bodyCubes.back().get_position()
//	glm::vec3 startLoc = 
//
//	set_orientation(prism, this->headDirection, appContext);
//	generate_prism(prism, *prism.vertices, appContext);
//	prism.set_position(startLoc);
//
//	this->bodyCubes.push_back(prism);
//	this->bodyIndexes.push_back(tableIndex);
//	if(isGrowing) this->length++;
//}
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

//glm::vec3 get_new_head_position(Player& player, AppContext appContext) {
//	glm::vec3 positionOffset;
//	Direction headDirection = player.get_head_direction();
//	float unitsPerTile = appContext.get_game_manager().unitsPerTile;
//	PrismObject head = player.get_body_cubes().back();
//
//	switch (headDirection) {
//	case FORWARD:
//		positionOffset = glm::vec3(0.0f, 0.0f, unitsPerTile / 2);
//		break;
//	case BACKWARD:
//		positionOffset = glm::vec3(0.0f, 0.0f, unitsPerTile / 2);
//		break;
//	case LEFT:
//		positionOffset = glm::vec3(unitsPerTile, 0.0f, 0.0f);
//		break;
//	case RIGHT:
//		positionOffset = glm::vec3(unitsPerTile / 2, 0.0f, 0.0f);
//		break;
//	}
//	
//	return head.get_grid_position() + positionOffset);
//}
