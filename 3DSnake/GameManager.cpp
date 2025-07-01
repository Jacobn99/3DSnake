#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"

GameManager::GameManager(float sizeInUnits, unsigned int sizeInTiles) {
	this->sizeInTiles = sizeInTiles;
	this->sizeInUnits = sizeInUnits;
	this->startIndex = (this->sizeInTiles * this->sizeInTiles) / 2;
	this->unitsPerTile = this->sizeInUnits / this->sizeInTiles;
	this->boardCenter = glm::vec3(0.0f, 0.0f, -4.0f);
	this->boardTopLeft = this->boardCenter - glm::vec3((this->sizeInUnits / 2.0f) - this->unitsPerTile/2, 
		0.0f, (this->sizeInUnits / 2.0f) - this->unitsPerTile / 2);
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
	assert(row < this->sizeInTiles && column < this->sizeInTiles);
	return row * this->sizeInTiles + column;
}
glm::vec3 GameManager::board_to_vec3(unsigned int row, unsigned int column) {
	glm::vec3 boardTopLeft = this->boardTopLeft;
	float unitsPerTile = this->unitsPerTile;

	glm::vec3 result = glm::vec3(boardTopLeft.x + (float)column * unitsPerTile, 0.0f, boardTopLeft.z +	row * unitsPerTile);
	return result;
}