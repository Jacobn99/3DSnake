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

void move_multi_segment(Player& player, double deltaTime, AppContext appContext) {
	GameManager& gameManager = appContext.get_game_manager();
	std::deque<SnakeScaleObject>& bodyCubes = player.get_body_cubes();
	SnakeScaleObject& head = bodyCubes.back();
	SnakeScaleObject& tail = bodyCubes.front();

	glm::vec3 headScaleChange = getMovementScaleChange(player.get_speed(), head.get_direction(), deltaTime);
	glm::vec3 tailScaleChange = getMovementScaleChange(player.get_speed(), tail.get_direction(), deltaTime);
	glm::vec3 oldTailScale;
	glm::vec3 newTailScale;
	glm::vec3 oldHeadScale;
	glm::vec3 newHeadScale;
	glm::vec2 tailGridPosition;
	bool hasRowChanged;
	bool hasColumnChanged;

	oldHeadScale = head.get_scale();
	oldTailScale = tail.get_scale();
	head.set_scale(head.currentScale + headScaleChange);
	tail.set_scale(tail.currentScale - tailScaleChange);
	newHeadScale = head.get_scale();
	newTailScale = tail.get_scale();

	int newScaleXInt = (static_cast<int>(newHeadScale.x));
	int newScaleZInt = (static_cast<int>(newHeadScale.z));
	hasRowChanged = newScaleZInt > static_cast<int>(oldHeadScale.z);
	hasColumnChanged = newScaleXInt > static_cast<int>(oldHeadScale.x);
	bool is_eating_apple = (player.get_head_grid_position() == gameManager.applePosition);
	player.inNewTile = false;

	tailGridPosition = gameManager.vec3_to_grid_position(tail.get_position(), false);

	//Checks if snake head is touching tail
	if (player.get_head_grid_position() == tailGridPosition && player.get_length() > 2) {
		printf("\t\t\t\t\t\t\t\t\tHIT!!!\n");
		gameManager.end_game();
	}

	//Checks if current tail is gone
	if (newTailScale.x < 0 || newTailScale.z < 0) {
		bodyCubes.pop_front();
		tail.delete_object(false);
	}

	// Checks if head location must be updated
	if (hasRowChanged || hasColumnChanged) {
		player.inNewTile = true;
		bool isTurning = player.get_queued_head_direction() != player.get_head_direction();

		if (isTurning) turn_snake(player, player.get_queued_head_direction(), appContext);
		else if (player.isQueuedGrow) {
			player.add_body_part(appContext, player.get_head_direction(), true, false);
			player.isQueuedGrow = false;
		}
		else if (is_eating_apple) {
			player.add_body_part(appContext, player.get_head_direction(), true, false);
			gameManager.relocate_apple(appContext);
		}
		else player.set_head_grid_position(player.get_head_grid_position() +
			appContext.get_game_manager().get_tile_offset(player.get_head_direction()));
	}
}

void move_singleton(Player& player, double deltaTime, AppContext appContext) {
	GameManager& gameManager = appContext.get_game_manager();
	std::deque<SnakeScaleObject>& bodyCubes = player.get_body_cubes();
	SnakeScaleObject& head = bodyCubes.back();
	SnakeScaleObject& tail = bodyCubes.front();

	glm::vec3 singletonPositionChange = getSingletonPositionChange(player, deltaTime);
	glm::vec3 currentPosition = head.get_position();
	glm::vec3 targetPosition = head.get_position() + singletonPositionChange;

	glm::vec3 currentFrontCenterPosition = edge_to_front_center(currentPosition, head, appContext);
	glm::vec3 targetFrontCenterPosition = edge_to_front_center(targetPosition, head, appContext);

	glm::vec3 currentFrontBackPosition = currentPosition + get_scaled_grid_vector(head.get_direction(), head.get_scale(),
		gameManager.unitsPerTile, gameManager.unitsPerTile);
	glm::vec3 targetFrontBackPosition = targetPosition + get_scaled_grid_vector(head.get_direction(), head.get_scale(),
		gameManager.unitsPerTile, gameManager.unitsPerTile);

	glm::vec2 currentGridFCPosition = gameManager.vec3_to_length_adjusted_tile(player, currentFrontCenterPosition, false);
	glm::vec2 targetGridFCPosition = gameManager.vec3_to_length_adjusted_tile(player, targetFrontCenterPosition, false);
	glm::vec2 currentGridFBPosition = gameManager.vec3_to_grid_position(currentFrontBackPosition, false);
	glm::vec2 targetGridFBPosition = gameManager.vec3_to_grid_position(targetFrontBackPosition, false);

	head.set_position(targetPosition);

	if (currentGridFBPosition != targetGridFBPosition) {
		player.set_head_grid_position(player.get_head_grid_position() + 
			gameManager.get_tile_offset(head.get_direction()));
	}

	if (currentGridFCPosition != targetGridFCPosition) {
		glm::vec2 difference = targetGridFCPosition - currentGridFCPosition;
		player.inNewTile = true;

		if (player.queuedHeadDirection != player.get_head_direction()) {
			if (player.get_body_cubes().size() == 1 && player.get_length() > 1)
				player.set_head_grid_position(player.get_previous_grid_position());
			turn_snake(player, player.get_queued_head_direction(), appContext);
		}
		if (player.isQueuedGrow) {
			if (bodyCubes.size() == 1 && player.get_length() > 1)
				player.set_head_grid_position(player.get_previous_grid_position());
			player.add_body_part(appContext, player.get_head_direction(), true, false);
			player.isQueuedGrow = false;
		}
		if (player.get_head_grid_position() + gameManager.get_tile_offset(
			player.get_head_direction()) == gameManager.applePosition || 
			player.get_head_grid_position() == gameManager.applePosition) {

			player.add_body_part(appContext, player.get_head_direction(), true, false);
			gameManager.relocate_apple(appContext);
		}
	}
}