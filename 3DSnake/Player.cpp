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
#include <unordered_set>

//TODO:
// - Every tile the snake comes across will have its own snake cube
// - Remove the faces the are unecessary while playing

void initialize_body(Player& player, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	glm::vec2 gridStart = glm::vec2(gameManager.sizeInTiles / 2, gameManager.sizeInTiles / 2);
	SnakeScaleObject head = generate_snake_scale(gridStart,
		gameManager.defaultDirection, appContext.get_shader(), appContext);
		
		/*SnakeScaleObject(gridStart,
		gameManager.defaultDirection, 36, appContext.get_shader(), appContext);*/

	player.set_head_grid_position(gridStart);

	//generate_snake_scale(head, appContext);
	player.add_body_part(head, gameManager.startIndex, true);
}

Player::Player(AppContext appContext) {
	this->bodyIndexes = std::queue<int>();
	this->bodyCubes = std::deque<SnakeScaleObject>();
	this->length = 0;
	this->speed = 0.75f; // units per second
	this->headDirection = appContext.get_game_manager().defaultDirection;
	this->queuedHeadDirection = this->headDirection;
	this->isQueuedGrow = false;
	/*this->headGridPosition = glm::vec2(0.0f, 0.0f);*/

	initialize_body(*this, appContext);
}
unsigned int Player::get_length() {
	return this->length;
}
std::queue<int> Player::get_body_indexes() {
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
float Player::get_speed() {
	return this->speed;
}

void Player::move_body(float deltaTime, AppContext appContext) {
	SnakeScaleObject& head = this->bodyCubes.back();
	SnakeScaleObject& tail = this->bodyCubes.front();
	bool inNewTile = false;
	GameManager& gameManager = appContext.get_game_manager();
	printf("scales: %d\n", this->bodyIndexes.size());


	//If snake has multiple scales
	if (this->length > 1 && this->bodyCubes.size() > 1) { 
		glm::vec3 headScaleChange = getMovementScaleChange(this->speed, head.get_direction(), deltaTime);
		glm::vec3 tailScaleChange = getMovementScaleChange(this->speed, tail.get_direction(), deltaTime);
		glm::vec3 oldScale;
		glm::vec3 newScale;
		bool hasRowChanged;
		bool hasColumnChanged;

		
		oldScale = head.get_scale();
		head.set_scale(head.currentScale + headScaleChange);
		tail.set_scale(tail.currentScale - tailScaleChange);
		newScale = head.get_scale();
		int newScaleXInt = (static_cast<int>(newScale.x));
		int newScaleZInt = (static_cast<int>(newScale.z));
		hasRowChanged = newScaleZInt > static_cast<int>(oldScale.z);
		hasColumnChanged = newScaleXInt > static_cast<int>(oldScale.x);
		//Checks if current tail is gone
		if (tail.currentScale.x < 0 || tail.currentScale.z < 0) {
			this->bodyCubes.pop_front();
			tail.delete_object(false);
			if(this->bodyIndexes.size() > 0) this->bodyIndexes.pop();

		}

		// Checks if head location must be updated
		if (hasRowChanged || hasColumnChanged) {
			inNewTile = true;
			bool isTurning = this->queuedHeadDirection != this->headDirection;

			if (this->isQueuedGrow) {
				this->add_body_part(appContext, this->get_head_direction(), true, false);
				this->isQueuedGrow = false;
			}
			else if (isTurning) turn_snake(*this, this->queuedHeadDirection, appContext);
			else set_head_grid_position(get_head_grid_position() + appContext.get_game_manager().get_tile_offset(this->headDirection));
		}
	}
	//If snake is a singleton
	else {
		glm::vec3 singletonPositionChange = getSingletonPositionChange(*this, deltaTime);
		glm::vec3 oldPosition = head.get_position();
		glm::vec3 currentPosition = head.get_position() + singletonPositionChange;
		glm::vec2 oldGridPosition = gameManager.vec3_to_adjusted_grid_position(*this, oldPosition);
		glm::vec2 currentGridPosition = gameManager.vec3_to_adjusted_grid_position(*this,currentPosition);
		
		head.set_position(currentPosition);
		this->set_head_grid_position(currentGridPosition);

		if (oldGridPosition != currentGridPosition) {
			inNewTile = true;

			//Edit bodyCubes and bodyIndexes
			this->bodyIndexes.push(gameManager.row_col_to_index(currentGridPosition.x, currentGridPosition.y));
			if (this->bodyIndexes.size() > 1)this->bodyIndexes.pop();

			if (this->queuedHeadDirection != this->headDirection) turn_snake(*this, this->queuedHeadDirection, appContext);
			if (this->isQueuedGrow) {
				this->add_body_part(appContext, this->get_head_direction(), true, false);
				this->isQueuedGrow = false;
			}
		
			/*glm::vec3 normalizedPosition = (glm::vec3(currentPosition.x + gameManager.unitsPerTile - gameManager.boardCenter.x,
				0.0f, currentPosition.z + 3 * gameManager.unitsPerTile / 2 - gameManager.boardCenter.z));

			int row = static_cast<int>(normalizedPosition.z / gameManager.unitsPerTile + gameManager.sizeInTiles / 2) - 1;
			int column = static_cast<int>(normalizedPosition.x / gameManager.unitsPerTile + gameManager.sizeInTiles / 2) - 1;
			glm::vec2 result = glm::vec2(row, column);*/

			//printf("\t\t\t\t\t\t\t\t\tcurrent pos | x: %f, y: %f\n", this->get_head_grid_position().x, this->get_head_grid_position().y);

			//printf("\t\t\t\t\t\t\t\t\tcol = %f, (int) col: %d\n", (normalizedPosition.z / gameManager.unitsPerTile + gameManager.sizeInTiles / 2) - 1, column);
			//printf("\t\t\t\t\t\t\t\t\tresult | x: %f, z: %f\n", result.x, result.y);
		}
		//if(inNewTile) head.set_adjusted_position(gameManager.board_to_vec3(newGridPosition), appContext);
	}
	//printf("current pos | x: %f, y: %f\n", this->get_head_grid_position().x, this->get_head_grid_position().y);
	if (inNewTile && checkTileDuplicates(*this)) printf("\t\t\t\t\t\t\t\t\tfart\n");
	this->i += 1;
}
void Player::queue_growth() {
	this->isQueuedGrow = true;
}
void Player::draw_body(AppContext appContext) {
	for (SnakeScaleObject scale : this->bodyCubes) {
		appContext.get_object_manager().draw_prism(scale);
	}
}
void Player::add_body_part(SnakeScaleObject scale, unsigned int tableIndex, bool isGrowing) {
	this->bodyCubes.push_back(scale);
	this->bodyIndexes.push(tableIndex);
	//this->bodyIndexes.push_back(tableIndex);
	if (isGrowing) this->length++;
}
void Player::add_body_part(AppContext appContext, Direction direction, bool isGrowing, bool startAsPlane) {
	GameManager gameManager = appContext.get_game_manager();

	glm::vec2 boardPosition = get_new_head_position(*this, direction, appContext);
	SnakeScaleObject newHead = generate_snake_scale(boardPosition, direction, appContext.get_shader(), appContext);
	
	/*SnakeScaleObject(boardPosition, direction, 36, appContext.get_shader(), appContext);*/
	glm::vec3 startLoc = gameManager.board_to_vec3(boardPosition);
	SnakeScaleObject& oldHead = this->bodyCubes.back();

	//generate_snake_scale(newHead, appContext);
	if (startAsPlane) newHead.set_scale(get_initial_scaling(direction)); //Start with no scale
	else boardPosition += gameManager.get_tile_offset(direction);

	set_snake_orientation_with_offset(oldHead, gameManager.get_opposite_direction(oldHead.get_direction()), true, appContext);\
	newHead.set_direction(direction);

	//Edit bodyCubes and bodyIndexes
	this->bodyCubes.push_back(newHead);
	this->bodyIndexes.push(gameManager.row_col_to_index(boardPosition.x, boardPosition.y));
	if(this->bodyIndexes.size() > 1) this->bodyIndexes.pop();

	if(isGrowing) this->length++;
	this->set_head_grid_position(boardPosition);
}
void Player::queue_turn(Direction direction, AppContext appContext) {
	this->queuedHeadDirection = direction;
}
glm::vec2 get_new_head_position(Player& player, Direction direction, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	glm::vec2 tileOffset = gameManager.get_tile_offset(direction);
	glm::vec2 result;

	float unitsPerTile = gameManager.unitsPerTile;
	SnakeScaleObject head = player.get_body_cubes().back();
	glm::vec2 prevHeadPosition = gameManager.vec3_to_grid_position(head.get_prev_position());

	//printf("\t\t\t\t\t\t\t\t\tprevHeadPos | row: %f, col: %f\n", prevHeadPosition.x, prevHeadPosition.y);

	if(player.get_length() == 1) result = prevHeadPosition + tileOffset;
	else result = player.get_head_grid_position() + tileOffset;
	//printf("----------------------\n");
	//printf("headGridPosition | x: %f, y: %f\n", player.get_head_grid_position().x, player.get_head_grid_position().y);
	//printf("result | x: %f, y: %f\n", result.x, result.y);


	return result;
}

void turn_snake(Player& player, Direction direction, AppContext appContext) {
	if (player.get_length() > 1) {
		player.add_body_part(appContext, direction, false, true);
		SnakeScaleObject& newHead = player.get_body_cubes().back();
		set_orientation(newHead, direction, appContext);
		player.set_head_direction(direction);
	}
	else player.set_head_direction(direction);
}

glm::vec3 getSingletonPositionChange(Player player, double deltaTime) {
	//assert(player.get_length() == 1);
	float speed = player.get_speed();
	glm::vec3 singletonPositionChange;

	switch (player.get_head_direction()) {
	case FORWARD:
		singletonPositionChange = glm::vec3(0.0f, 0.0f, -speed * deltaTime);
		break;
	case BACKWARD:
		singletonPositionChange = glm::vec3(0.0f, 0.0f, speed * deltaTime);
		break;
	case LEFT:
		singletonPositionChange = glm::vec3(-speed * deltaTime, 0.0f, 0.0f);
		break;
	case RIGHT:
		singletonPositionChange = glm::vec3(speed * deltaTime, 0.0f, 0.0f);
		break;
	}
	return singletonPositionChange;
}
glm::vec3 getMovementScaleChange(float speed, Direction direction, double deltaTime) {
	glm::vec3 scaleChange;

	switch (direction) {
	case FORWARD:
		scaleChange = glm::vec3(0.0f, 0.0f, speed * deltaTime);
		break;
	case BACKWARD:
		scaleChange = glm::vec3(0.0f, 0.0f, speed * deltaTime);
		break;
	case LEFT:
		scaleChange = glm::vec3(speed * deltaTime, 0.0f, 0.0f);
		break;
	case RIGHT:
		scaleChange = glm::vec3(speed * deltaTime, 0.0f, 0.0f);
		break;

	}
	return scaleChange;
}
bool checkTileDuplicates(Player& player) {
	std::queue<int> tmp = player.get_body_indexes();
	std::unordered_set<int> set = std::unordered_set<int>();
	while (!tmp.empty()) {
		int current = tmp.front();
		if (set.count(current) > 0) return true;
		set.insert(current);
		tmp.pop();
	}
	return false;
}
