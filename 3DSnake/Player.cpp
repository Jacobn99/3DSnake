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


Player::Player(AppContext appContext) {
	this->bodyIndexes = std::vector<int>();
	this->bodyCubes = std::vector<PrismObject>();
	GameManager gameManager = *appContext.get_game_manager();

	PrismObject prism = PrismObject(36, *appContext.get_shader(), *appContext.get_texture_manager());
	float tileSizeInUnits = gameManager.tileSizeInUnits;
	prism.generate_prism(-(tileSizeInUnits / 2), (tileSizeInUnits / 2), 
		-0.5f, 0.5f, -(tileSizeInUnits / 2), (tileSizeInUnits / 2), gameManager.sizeInTiles);
	prism.set_position(glm::vec3(0.0f, 0.0f, -4.0f));

	this->bodyCubes.push_back(prism);
	this->bodyIndexes.push_back(gameManager.startIndex);
}
unsigned int Player::get_length() {
	return this->length;
}
glm::vec2 Player::get_movement_direction() {
	return this->movementDirection;
}
std::vector<int>* Player::get_body_indexes() {
	return &this->bodyIndexes;
}
void Player::remove_tail() {
	assert(!this->bodyIndexes.empty() && !this->bodyCubes.empty());
	//HOW DO I POP FROM FRONT!!!???
	/*this->bodyIndexes.pop_back();
	this->bodyCubes.pop_back();*/
;}
//void Player::move_head() {
//	this->bodyParts.push()
//}
void Player::draw_body() {
	for (PrismObject prism : this->bodyCubes) {
		draw_object(prism);
	}
}