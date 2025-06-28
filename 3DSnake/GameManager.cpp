#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"

GameManager::GameManager(unsigned int sizeInUnits, unsigned int sizeInTiles) {
	this->sizeInTiles = sizeInTiles;
	this->sizeInUnits = sizeInUnits;
	this->startIndex = (this->sizeInTiles * this->sizeInTiles) / 2;
	this->tileSizeInUnits = sizeInUnits / this->sizeInTiles;
}
unsigned int GameManager::index_to_row(unsigned int index) {
	assert(index < this->sizeInTiles * this->sizeInTiles);
	return index / this->sizeInTiles;
}
unsigned int GameManager::index_to_column(unsigned int index) {
	assert(index < sizeInTiles * sizeInTiles);
	return index % this->sizeInTiles;
}
unsigned int GameManager::row_column_to_index(unsigned int row, unsigned int column) {
	assert(row < this->sizeInTiles && column < this->sizeInTiles);
	return row * this->sizeInTiles + column;
}