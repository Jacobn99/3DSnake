#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Player.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"
#include <cmath>



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
	/*this->snakeTexture = appContext.get_texture_manager().generate_texture_2D(
		"C:\\Users\\jacob\\source\\repos\\3DSnake\\3DSnake\\Textures\\snake_scale.png",
		GL_RGBA, GL_REPEAT, GL_LINEAR);*/
}
Texture GameManager::get_generated_texture(GeneratedTextures texture) {
	switch (texture) {
	case FLOOR:
		return this->floorTexture;
	case GREEN_SQUARE:
		return this->greenSquareTexture;
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
	case GREEN_SQUARE:
		this->greenSquareTexture = texture;
		break;	
	default:
		printf("ERROR: GeneratedTextures enum bigger than switch statement 2\n");
	}
	this->floorTexture = texture;
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
	glm::vec3 normalizedPosition = (glm::vec3(position.x - this->boardCenter.x,
		0.0f, position.z - this->boardCenter.z));

	float rowFloat = (normalizedPosition.z / this->unitsPerTile + this->sizeInTiles / 2);
	float columnFloat = (normalizedPosition.x / this->unitsPerTile + this->sizeInTiles / 2);

	/*if (-1.0f < rowFloat && rowFloat < 0.0f) rowFloat = 0.0f;
	if (-1.0f < columnFloat && columnFloat < 0.0f) columnFloat = 0.0f;*/
	int row;
	int column;
	if (rowFloat - std::floor(rowFloat) < 0.07) row = std::floor(rowFloat);
	else row = std::ceil(rowFloat);
	if (columnFloat - std::floor(columnFloat) < 0.07f) column = std::floor(columnFloat);
	else column = std::ceil(columnFloat);
	
	/*int row = static_cast<int>(rowFloat);
	int column = static_cast<int>(columnFloat);*/
	
	if (rowFloat - row > 0.95) row++;
	if (columnFloat - column > 0.95) column++;

	glm::vec2 result = glm::vec2(row, column);

	//printf("\t\t\t\t\t\t\t\trowFloat = %f, colFloat = %f, row: %d, col: %d\n", rowFloat, columnFloat, row, column);


	/*assert(result.x >= 0 && result.x < this->sizeInTiles);
	assert(result.y >= 0 && result.y < this->sizeInTiles);*/
	//printf("FIX MIDDLE BEING SKIPPED!!!!!\n");
	//printf("-----------------------\n");
	/*printf("row = %f, col = %f, (int) row: %d, (int) col: %d,\n", normalizedPosition.z / this->unitsPerTile + this->sizeInTiles / 2,
		normalizedPosition.x / this->unitsPerTile + this->sizeInTiles / 2, row, column);
	printf("result | x: %f, z: %f\n", result.x, result.y);*/
	return result;
}

glm::vec2 GameManager::vec3_to_length_adjusted_tile(Player& player, glm::vec3 position) {
	if (player.get_body_cubes().size() == 1) {
		glm::vec2 gridPos = vec3_to_grid_position(position);
		glm::vec2 result = gridPos + get_tile_offset(player.get_head_direction()).operator*=(player.get_length() - 1);
		//printf("result | x: %f, z: %f\n", result.x, result.y);
		return result;
	}
	else return vec3_to_grid_position(position);
}

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

glm::vec3 get_scaled_grid_vector(Direction direction, glm::vec3 scale, float tileSize, int lengthOffset) {
	//assert(scale.x > 0.0f && scale.y > 0.0f && scale.z > 0.0f);

	glm::vec3 vect;
	//glm::vec3 adjustedScale = scale;

	switch (direction) {
	case LEFT:
		vect = glm::vec3(-tileSize * (scale.x - lengthOffset), 0.0f, 0.0f);
		break;
	case RIGHT:
		vect = glm::vec3(tileSize * (scale.x - lengthOffset), 0.0f, 0.0f);
		break;
	case FORWARD:
		vect = glm::vec3(0.0f, 0.0f, -tileSize * (scale.z - lengthOffset));
		break;
	case BACKWARD:
		vect = glm::vec3(0.0f, 0.0f, tileSize * (scale.z - lengthOffset));
		break;
	}

	return vect;
}
glm::vec3 get_directional_offset(Direction direction) {
	glm::vec3 vect;
	switch (direction) {
	case LEFT:
		vect = glm::vec3(-1.0f, 0.0f, 0.0f);
		break;
	case RIGHT:
		vect = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case FORWARD:
		vect = glm::vec3(0.0f, 0.0f, -1.0f);
		break;
	case BACKWARD:
		vect = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	}
	return vect;
}

void snap_to_grid(SnakeScaleObject& scale, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	glm::vec3 frontCenter = edge_to_front_center(scale.get_position(), scale, appContext);

	glm::vec3 normalizedPosition = (glm::vec3(frontCenter.x - gameManager.boardCenter.x,
		0.0f, frontCenter.z - gameManager.boardCenter.z));

	float rowFloat = (normalizedPosition.z / gameManager.unitsPerTile + gameManager.sizeInTiles / 2);
	float columnFloat = (normalizedPosition.x / gameManager.unitsPerTile + gameManager.sizeInTiles / 2);
	
	glm::vec2 currentGridPosition = gameManager.vec3_to_grid_position(frontCenter);
	float row = currentGridPosition.x;
	float column = currentGridPosition.y;

	if ((scale.get_direction() == FORWARD || scale.get_direction() == BACKWARD) 
		&& std::abs(columnFloat - column) < 0.1) {
		scale.set_position(scale.get_position() - glm::vec3(0.0f,0.0f, (columnFloat - column)));
	}
	else if((scale.get_direction() == LEFT || scale.get_direction() == RIGHT) 
		&& std::abs(rowFloat - row) < 0.1){
		scale.set_position(scale.get_position() - glm::vec3((rowFloat - row), 0.0f, 0.0f));
	}
}