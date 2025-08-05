#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include "Player.h"

class AppContext; // Forward declaration of AppContext
class Player;
enum GeneratedTextures {
	FLOOR,
	SNAKE
};

class GameManager {
public:
	GameManager() = default;
	GameManager(float sizeInUnits, unsigned int sizeInTiles);
	unsigned int index_to_column(unsigned int index);
	unsigned int index_to_row(unsigned int index);
	unsigned int row_col_to_index(unsigned int row, unsigned int col);
	void start_game(AppContext appContext);
	Player& get_player();
	glm::vec3 board_to_vec3(glm::vec2 boardLoc);
	glm::vec3 get_orientation_offset(Direction direction);
	glm::vec2 get_tile_offset(Direction direction);
	glm::vec2 vec3_to_grid_position(glm::vec3 position);
	void singleton_tile_check(Player& player, glm::vec3 currentAdjustedPosition);
	bool singleton_in_new_tile(Player& player, glm::vec3 currentAdjustedPosition);
	glm::vec2 vec3_to_length_adjusted_tile(SnakeScaleObject head, glm::vec3 position, AppContext appContext);
	//glm::vec2 vec3_to_direction_adjusted_grid_position(Direction direction, glm::vec3 position);
	Direction get_opposite_direction(Direction direction);
	Texture get_generated_texture(GeneratedTextures texture);
	void set_generated_texture(GeneratedTextures gen, Texture texture);
	PrismObject& get_board();
	//const char* direction_to_string(Direction direction);
	unsigned int startIndex;
	unsigned int sizeInTiles;
	float sizeInUnits;
	glm::vec3 boardCenter;
	glm::vec3 boardTopLeft;
	float unitsPerTile;
	Direction defaultDirection;
	bool gameRunning;
private:
	Texture floorTexture;
	Texture snakeTexture;
	glm::vec3 frontPositionOffset;
	glm::vec3 backPositionOffset;
	glm::vec3 leftPositionOffset;
	glm::vec3 rightPositionOffset;
	Player player;
	PrismObject board;
};

glm::vec3 get_vec3_directional_grid_offset(Direction direction, AppContext appContext);
glm::vec3 get_scaled_grid_vector(Direction direction, glm::vec3 scale, float tileSize);
const char* direction_to_string(Direction direction);

#endif
