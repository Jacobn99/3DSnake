#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"

class AppContext; // Forward declaration of AppContext

class GameManager {
public:
	GameManager() = default;
	GameManager(float sizeInUnits, unsigned int sizeInTiles);
	unsigned int index_to_column(unsigned int index);
	unsigned int index_to_row(unsigned int index);
	unsigned int row_col_to_index(unsigned int row, unsigned int col);
	glm::vec3 board_to_vec3(unsigned int row, unsigned int col);
	glm::vec3 get_orientation_offset(Direction direction);
	unsigned int startIndex;
	unsigned int sizeInTiles;
	float sizeInUnits;
	glm::vec3 boardCenter;
	glm::vec3 boardTopLeft;
	float unitsPerTile;
	Direction defaultDirection;
private:
	glm::vec3 frontPositionOffset;
	glm::vec3 backPositionOffset;
	glm::vec3 leftPositionOffset;
	glm::vec3 rightPositionOffset;
};

#endif
