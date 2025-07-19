#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Player.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"



GameManager::GameManager(float sizeInUnits, unsigned int sizeInTiles) {
	this->sizeInTiles = sizeInTiles;
	this->sizeInUnits = sizeInUnits;
	this->startIndex = (this->sizeInTiles * this->sizeInTiles) / 2;
	this->unitsPerTile = this->sizeInUnits / this->sizeInTiles;
	this->boardCenter = glm::vec3(0.0f, 0.0f, -4.0f);
	this->boardTopLeft = this->boardCenter - glm::vec3((this->sizeInUnits / 2.0f) - this->unitsPerTile/2, 
		0.0f, (this->sizeInUnits / 2.0f) - this->unitsPerTile / 2);
	this->leftPositionOffset = glm::vec3(this->unitsPerTile / 2, 0.0f, 0.0f);
	this->rightPositionOffset = glm::vec3(-(float)(this->unitsPerTile / 2), 0.0f, 0.0f);
	this->frontPositionOffset = glm::vec3(0.0f, 0.0f, this->unitsPerTile / 2);
	this->backPositionOffset = glm::vec3(0.0f, 0.0f, -(float)((this->unitsPerTile / 2)));
	this->defaultDirection = FORWARD;
	this->gameRunning = false;
	this->player = Player();
	this->board = PrismObject();
	/*this->snakeTexture = appContext.get_texture_manager().generate_texture_2D(
		"C:\\Users\\jacob\\source\\repos\\3DSnake\\3DSnake\\Textures\\snake_scale.png",
		GL_RGBA, GL_REPEAT, GL_LINEAR);*/
}

void GameManager::start_game(AppContext appContext) {
	Texture tileTexture = this->get_generated_texture(FLOOR);
	this->gameRunning = true;

	//Object creation
	this->board = PrismObject(36, appContext.get_shader(), appContext);
	generate_prism(this->board, appContext, -(sizeInUnits / 2), (sizeInUnits / 2),
		-0.5f, 0.5f, -(sizeInUnits / 2), (sizeInUnits / 2), this->sizeInTiles);
	this->board.set_position(this->boardCenter - glm::vec3(0.0f, 1.01f, 0.0f));
	this->board.set_texture(tileTexture);

	//Player creation
	this->player = Player(appContext);
}

Player& GameManager::get_player() {
	assert(this->gameRunning);
	return this->player;
}

PrismObject& GameManager::get_board() {
	assert(this->gameRunning);
	return this->board;
}


Texture GameManager::get_generated_texture(GeneratedTextures texture) {
	switch (texture) {
	case FLOOR:
		return this->floorTexture;
	case SNAKE:
		return this->snakeTexture;
	default:
		printf("ERROR: GeneratedTextures enum bigger than switch statement 1\n");
		Texture texture = Texture();
		return texture;
	}
}
void GameManager::set_generated_texture(GeneratedTextures gen, Texture texture) {
	switch (gen) {
	case FLOOR:
		this->floorTexture = texture;
		break;
	case SNAKE:
		this->snakeTexture = texture;
		break;	
	default:
		printf("ERROR: GeneratedTextures enum bigger than switch statement 2\n");
		break;
	}
}
unsigned int GameManager::index_to_row(unsigned int index) {
	assert(index < this->sizeInTiles * this->sizeInTiles);
	return index / this->sizeInTiles;
}
unsigned int GameManager::index_to_column(unsigned int index) {
	assert(index < sizeInTiles * sizeInTiles);
	return index % this->sizeInTiles;
}
unsigned int GameManager::row_col_to_index(unsigned int row, unsigned int column) {
	//assert(row < this->sizeInTiles && column < this->sizeInTiles);
	return row * this->sizeInTiles + column;
}
glm::vec3 GameManager::board_to_vec3(glm::vec2 boardLoc) {
	glm::vec3 boardTopLeft = this->boardTopLeft;
	float unitsPerTile = this->unitsPerTile;
	int row = static_cast<int>(boardLoc.x);
	int column = static_cast<int>(boardLoc.y);

	glm::vec3 result = glm::vec3(boardTopLeft.x + (float)column * unitsPerTile, 0.0f, boardTopLeft.z + row * unitsPerTile);
	return result;
}
glm::vec3 GameManager::get_orientation_offset(Direction direction) {
	switch (direction) {
	case FORWARD: 
		return this->frontPositionOffset;
		break;
	case BACKWARD:
		return this->backPositionOffset;
		break;
	case LEFT:
		return this->leftPositionOffset;
		break;
	case RIGHT:
		return this->rightPositionOffset;
		break;
	}

}

glm::vec2 GameManager::vec3_to_grid_position(glm::vec3 position) {
	glm::vec3 normalizedPosition = (glm::vec3(position.x + this->unitsPerTile - this->boardCenter.x,
		0.0f, position.z + 3*this->unitsPerTile/2 - this->boardCenter.z));

	int row = static_cast<int>(normalizedPosition.z / this->unitsPerTile + this->sizeInTiles / 2) - 1;
	int column = static_cast<int>(normalizedPosition.x / this->unitsPerTile + this->sizeInTiles / 2) - 1;

	glm::vec2 result = glm::vec2(row, column);
	return result;
}

glm::vec2 GameManager::vec3_to_length_adjusted_tile(SnakeScaleObject head, glm::vec3 position, AppContext appContext) {
	if (player.get_body_cubes().size() == 1) {
		glm::vec3 lengthAdjustedPosition = centered_vec3_to_edge(head, position, appContext);

		return vec3_to_grid_position(lengthAdjustedPosition);
		//return vec3_to_grid_position(lengthAdjustedPosition) + get_tile_offset(player.get_head_direction()).operator*=(player.get_length() - 1);
	}
	else return vec3_to_grid_position(head.get_position());
}

bool GameManager::singleton_in_new_tile(Player& player, glm::vec3 currentAdjustedPosition) {
	assert(player.get_body_cubes().size() == 1);
	float xOffset = 0.0f;
	float zOffset = 0.0f;

	switch (player.get_head_direction()) {
	case FORWARD:
		zOffset = -unitsPerTile / 2;
		break;
	case BACKWARD:
		zOffset = unitsPerTile / 2;
		break;
	case LEFT:
		xOffset = -unitsPerTile / 2;
		break;
	case RIGHT:
		zOffset = unitsPerTile / 2;
		break;
	}

	glm::vec2 tileOffset = this->get_tile_offset(player.get_head_direction());
	glm::vec2 currentTile = player.get_head_grid_position();
	glm::vec2 targetTile = currentTile + tileOffset;
	glm::vec3 directionalOffset = glm::vec3(xOffset, 0.0f, zOffset);

	glm::vec3 targetPosition = this->board_to_vec3(targetPosition) + (directionalOffset);
	glm::vec3 positionChange = glm::abs(targetPosition - (currentAdjustedPosition));

	if (positionChange.x <= 0.1 && positionChange.z <= 0.1) return true;
	else return false;
}

//void GameManager::singleton_tile_check(Player& player, glm::vec3 currentAdjustedPosition) {
//	if (player.get_body_cubes().size() > 1) return;
//
//	if (this->is_in_new_tile(player, currentAdjustedPosition)) {
//		glm::vec2 tileOffset = this->get_tile_offset(player.get_head_direction());
//		player.set_head_grid_position(currentAdjustedPosition.operator+=(tileOffset));
//	}
//
//	//glm::vec3 normalizedPosition = (glm::vec3(position.x + this->unitsPerTile - this->boardCenter.x,
//	//	0.0f, position.z + 3 * this->unitsPerTile / 2 - this->boardCenter.z);
//
//	//int row = static_cast<int>(normalizedPosition.z / this->unitsPerTile + this->sizeInTiles / 2) - 1;
//	//int column = static_cast<int>(normalizedPosition.x / this->unitsPerTile + this->sizeInTiles / 2) - 1;
//
//	//glm::vec2 result = glm::vec2(row, column);
//
//	//if (player.get_body_cubes().size() == 1)
//	//	return vec3_to_grid_position(position) + get_tile_offset(direction/*player.get_head_direction()*/).operator*=(player.get_length() - 1);
//	//else return vec3_to_grid_position(position);
//}

// REMEMBER, IT'S STORED AS ROW,COL
glm::vec2 GameManager::get_tile_offset(Direction direction) {
	switch (direction) {
	case FORWARD:
		return glm::vec2(-1.0f, 0.0f);
	case BACKWARD:
		return glm::vec2(1.0f, 0.0f);
	case LEFT:
		return glm::vec2(0.0f, -1.0f);
	case RIGHT:
		return glm::vec2(0.0f, 1.0f);
	}
}
Direction GameManager::get_opposite_direction(Direction direction) {
	switch (direction) {
	case FORWARD:
		return BACKWARD;
	case BACKWARD:
		return FORWARD;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	}
}
const char* direction_to_string(Direction direction) {
	const char* result = "UNKNOWN DIRECTION";

	switch (direction) {
	case FORWARD:
		result = "FORWARD";
		break;
	case BACKWARD:
		result = "BACKWARD";
		break;
	case LEFT:
		result = "LEFT";
		break;
	case RIGHT:
		result = "RIGHT";
		break;
	default:
		break;
	}
	return result;
}

glm::vec3 get_scaled_grid_vector(Direction direction, glm::vec3 scale, float tileSize) {
	assert(scale.x > 0.0f && scale.y > 0.0f && scale.z > 0.0f);

	glm::vec3 vect;

	switch (direction) {
	case LEFT:
		vect = glm::vec3(-tileSize * (scale.x - 1), 0.0f, 0.0f);
		break;
	case RIGHT:
		vect = glm::vec3(tileSize * (scale.x - 1), 0.0f, 0.0f);
		break;
	case FORWARD:
		vect = glm::vec3(0.0f, 0.0f, -tileSize * (scale.z - 1));
		break;
	case BACKWARD:
		vect = glm::vec3(0.0f, 0.0f, tileSize * (scale.z - 1));
		break;
	}

	return vect;
}

glm::vec3 get_vec3_directional_grid_offset(Direction direction, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	float unitsPerTile = gameManager.unitsPerTile;
	float xOffset = 0.0f;
	float zOffset = 0.0f;

	switch (direction) {
	case FORWARD:
		zOffset = -unitsPerTile;
		break;
	case BACKWARD:
		zOffset = unitsPerTile;
		break;
	case LEFT:
		xOffset = -unitsPerTile;
		break;
	case RIGHT:
		xOffset = unitsPerTile;
		break;
	}
	return glm::vec3(xOffset, 0.0f, zOffset);
}
