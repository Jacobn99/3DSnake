#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class AppContext; // Forward declaration of AppContext

class GameManager {
public:
	GameManager() = default;
	GameManager(unsigned int sizeInUnits, unsigned int sizeInTiles);
	unsigned int index_to_column(unsigned int index);
	unsigned int index_to_row(unsigned int index);
	unsigned int row_column_to_index(unsigned int row, unsigned int column);
	unsigned int startIndex;
	unsigned int sizeInTiles;
	unsigned int sizeInUnits;
	float tileSizeInUnits;
private:

};

#endif
