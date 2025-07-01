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
// - Reduce scale amount depending on how much the snake part has already grown
// - Make it so a new prism is added to vector ONLY if the snake changes direction
// - Add code to update the mesh of just the snake head and tail

void initialize_body(Player* player, AppContext appContext) {
	GameManager gameManager = *appContext.get_game_manager();
	PrismObject prism = PrismObject(36, *appContext.get_shader(), *appContext.get_texture_manager());
	glm::vec3 startLoc = gameManager.board_to_vec3(gameManager.sizeInTiles / 2, gameManager.sizeInTiles / 2);
	float tileSizeInUnits = gameManager.unitsPerTile;

	generate_prism(&prism, -(tileSizeInUnits / 2), (tileSizeInUnits / 2),
		-0.5f, 0.5f, -(tileSizeInUnits / 2), (tileSizeInUnits / 2), gameManager.sizeInTiles);
	prism.set_position(startLoc);

	(*player).add_body_part(prism, gameManager.startIndex);
}

Player::Player(AppContext appContext) {
	this->bodyIndexes = std::vector<int>();
	this->bodyCubes = std::vector<PrismObject>();
	this->length = 0;

	GameManager gameManager = *appContext.get_game_manager();
	initialize_body(this, appContext);
}
unsigned int Player::get_length() {
	return this->length;
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
void Player::move_body(float deltaTime) {
	PrismObject* prism = &this->bodyCubes.front();

	/*prism.set_model(glm::scale(prism.get_model(), glm::vec3(1.0f, 1.0f, 2.0f)));*/
	(*prism).set_scale((*prism).currentScale + glm::vec3(0.0f,0.0f, 0.5f * deltaTime));
}
void Player::draw_body() {
	for (PrismObject prism : this->bodyCubes) {
		draw_object(&prism);
	}
}
void Player::add_body_part(PrismObject prism, unsigned int tableIndex) {
	this->bodyCubes.push_back(prism);
	this->bodyIndexes.push_back(tableIndex);
	this->length++;
}