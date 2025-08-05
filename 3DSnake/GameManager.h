#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"

class AppContext; // Forward declaration of AppContext
class Player;
class SnakeScaleObject;

enum GeneratedTextures {
	FLOOR,
	GREEN_SQUARE
};

class GameManager {
public:
	GameManager() = default;
	GameManager(float sizeInUnits, unsigned int sizeInTiles);
	unsigned int index_to_column(unsigned int index);
	unsigned int index_to_row(unsigned int index);
	unsigned int row_col_to_index(unsigned int row, unsigned int col);
	glm::vec3 board_to_vec3(glm::vec2 boardLoc);
	glm::vec3 get_orientation_offset(Direction direction);
	glm::vec2 get_tile_offset(Direction direction);
	glm::vec2 vec3_to_grid_position(glm::vec3 position, bool isDebug);
	glm::vec2 vec3_to_length_adjusted_tile(Player& player, glm::vec3 position, bool isDebug);
	Direction get_opposite_direction(Direction direction);
	Texture get_generated_texture(GeneratedTextures texture);
	void set_generated_texture(GeneratedTextures gen, Texture texture);
	//const char* direction_to_string(Direction direction);
	unsigned int startIndex;
	unsigned int sizeInTiles;
	float sizeInUnits;
	glm::vec3 boardCenter;
	glm::vec3 boardTopLeft;
	float unitsPerTile;
	Direction defaultDirection;
private:
	Texture floorTexture;
	Texture greenSquareTexture;
	glm::vec3 frontPositionOffset;
	glm::vec3 backPositionOffset;
	glm::vec3 leftPositionOffset;
	glm::vec3 rightPositionOffset;
};

void snap_to_grid(SnakeScaleObject& scale, AppContext appContext);
glm::vec3 get_directional_offset(Direction direction);
glm::vec3 get_scaled_grid_vector(Direction direction, glm::vec3 scale, float tileSize, int lengthOffset);
const char* direction_to_string(Direction direction);

#endif
