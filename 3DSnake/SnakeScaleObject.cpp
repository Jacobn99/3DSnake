#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\stb_image.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"
//								  V V In row, col order V V
SnakeScaleObject::SnakeScaleObject(glm::vec2 tileLocation, Direction direction, int vertexCount, Shader& shader, AppContext appContext)
	: PrismObject(vertexCount, shader, appContext) {
	GameManager gameManager = appContext.get_game_manager();
	//this->tileLocation = tileLocation;
	this->direction = direction;
	this->currentPosition = gameManager.board_to_vec3(tileLocation.x, tileLocation.y)
		+ gameManager.get_orientation_offset(direction);
}

Direction SnakeScaleObject::get_direction() {
	return this->direction;
}
void SnakeScaleObject::set_adjusted_position(glm::vec3 position, AppContext appContext) {
	this->currentPosition = position + appContext.get_game_manager().get_orientation_offset(this->direction);
	this->isQueuedTransformation = true;

}

void generate_snake_scale(SnakeScaleObject& snakeScale, AppContext appContext) {
	set_orientation(snakeScale, snakeScale.get_direction(), appContext);
	std::vector<float>& vertices = appContext.get_object_manager().get_orientation(snakeScale.get_direction());
	generate_prism(snakeScale, vertices, appContext);
}
glm::vec3 get_initial_scaling(Direction direction) {
	switch (direction) {
	case FORWARD:
		return glm::vec3(1.0f, 1.0f, 0.0f);
	case BACKWARD:
		return glm::vec3(1.0f, 1.0f, 0.0f);
	case RIGHT:
		return glm::vec3(0.0f, 1.0f, 1.0f);
	case LEFT:
		return glm::vec3(0.0f, 1.0f, 1.0f);
	}
}
void SnakeScaleObject::set_direction(Direction newDirection) {
	this->direction = newDirection;
}