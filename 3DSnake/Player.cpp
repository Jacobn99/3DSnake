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
bool canSnap = true;
bool movementQueued = false;

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
	this->speed = 1.0f; // units per second
	this->headDirection = appContext.get_game_manager().defaultDirection;
	this->queuedHeadDirection = this->headDirection;
	this->isQueuedGrow = false;
	this->canPopIndexes = false;
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
	this->previousGridPosition = this->get_head_grid_position();
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

//Add indexes if start scale is 1.0f and when scale rounds to new number

void Player::move_body(float deltaTime, AppContext appContext) {
	GameManager& gameManager = appContext.get_game_manager();
	glm::vec2 gridPosition = this->get_head_grid_position();
	update_body_indexes(*this, appContext);

	if (gridPosition.x < 0 || gridPosition.x >= gameManager.sizeInTiles ||
		gridPosition.y < 0 || gridPosition.y >= gameManager.sizeInTiles) gameManager.end_game();

	//If snake has multiple scales
	if (this->length > 1 && this->bodyCubes.size() > 1) { 
		move_multi_segment(*this, deltaTime, appContext);
	}
	//If snake is a singleton
	else {
		move_singleton(*this, deltaTime, appContext);
	}
	if (this->inNewTile && check_collision(*this, false)) {
		printf("\t\t\t\t\t\t\t\t\tTriggered at | row: %f, col: %f\n", this->get_head_grid_position().x, this->get_head_grid_position().y);
		printf("\t\t\t\t\t\t\t\t\t");
		printf("\t\t\t\t\t\t\t\t\t----------------------------\n");
		gameManager.end_game();
	}
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
	if (isGrowing) this->length++;
}
void Player::add_body_part(AppContext appContext, Direction direction, bool isGrowing, bool startAsPlane) {
	GameManager gameManager = appContext.get_game_manager();
	glm::vec2 boardPosition = get_new_head_position(*this, direction, appContext);
	SnakeScaleObject newHead = generate_snake_scale(boardPosition, direction, appContext.get_shader(), appContext);	
	glm::vec3 startLoc = gameManager.board_to_vec3(boardPosition);
	SnakeScaleObject& oldHead = this->bodyCubes.back();
	glm::vec3 oldScale = oldHead.get_scale();

	//Make sure old head is aligned with grid
	Direction oldHeadDirection = oldHead.get_direction();
	oldHead.set_position(gameManager.board_to_vec3(this->get_head_grid_position()));
	set_snake_orientation_with_offset(oldHead, oldHeadDirection, false, appContext);

	if (startAsPlane) newHead.set_scale(get_initial_scaling(direction)); //Start with no scale
	else boardPosition += gameManager.get_tile_offset(direction);

	set_snake_orientation_with_offset(oldHead, gameManager.get_opposite_direction(oldHead.get_direction()), true, appContext);
	newHead.set_direction(direction);
	
	oldHead.set_scale(glm::round(oldScale));

	//Edit bodyCubes
	this->bodyCubes.push_back(newHead);

	if (isGrowing) { 
		this->length++;
	}
	this->set_head_grid_position(boardPosition);
}
void Player::push_body_index(glm::vec2 boardPosition, AppContext appContext) {
	int index = appContext.get_game_manager().row_col_to_index(boardPosition.x, boardPosition.y);
	this->bodyIndexes.push(index);
}
void Player::pop_body_index() {
	assert(this->bodyIndexes.size() > 0);
	this->bodyIndexes.pop();
}
void Player::queue_turn(Direction direction, AppContext appContext) {
	this->queuedHeadDirection = direction;
}
Direction Player::get_queued_head_direction() {
	return this->queuedHeadDirection;
}
glm::vec2 get_new_head_position(Player& player, Direction targetDirection, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	Direction currentDirection = player.get_head_direction();
	glm::vec2 tileOffset = gameManager.get_tile_offset(targetDirection);
	glm::vec2 movementOffset = -gameManager.get_tile_offset(currentDirection);
	glm::vec2 currentGridPosition = player.get_head_grid_position();
	glm::vec2 result = currentGridPosition + tileOffset;

	return result;
}
glm::vec2 Player::get_previous_grid_position() {
	return this->get_previous_grid_position();
}

void turn_snake(Player& player, Direction direction, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	SnakeScaleObject& head = player.get_body_cubes().back();
	glm::vec2 currentGridPosition = player.get_head_grid_position();

	printf("\t\t\t\t\t\t\t\t\tregistered | row: %f, col: %f\n", currentGridPosition.x, currentGridPosition.y);

	if (player.get_length() > 1) {
		player.add_body_part(appContext, direction, false, true);
		SnakeScaleObject& newHead = player.get_body_cubes().back();
		set_orientation(newHead, direction, appContext);
		player.set_head_direction(direction);
	}
	else {
		set_snake_orientation_with_offset(head, direction, true, appContext);
		player.set_head_direction(direction);
	}
}

glm::vec3 getSingletonPositionChange(Player player, double deltaTime) {
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
bool check_collision(Player& player, bool isDebug) {
	std::queue<int> tmp = player.get_body_indexes();
	std::unordered_set<int> set = std::unordered_set<int>();
	while (!tmp.empty()) {
		int current = tmp.front();
		if (isDebug) printf("%d, ", current);
		if (set.count(current) > 0) return true;
		set.insert(current);
		tmp.pop();
	}
	return false;
}
void update_body_indexes(Player& player, AppContext appContext) {
	std::queue<int> bodyIndexes = player.get_body_indexes();
	glm::vec2 boardPosition = player.get_head_grid_position();
	int index = appContext.get_game_manager().row_col_to_index(boardPosition.x, boardPosition.y);

	//Update pushes
	if (bodyIndexes.size() == 0 || bodyIndexes.back() != index) {
		player.push_body_index(boardPosition, appContext);
	}
	//Update pops
	if (bodyIndexes.size() > player.get_length()) player.pop_body_index();
}