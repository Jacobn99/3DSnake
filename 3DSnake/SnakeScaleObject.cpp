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
	this->tileLocation = tileLocation;
	this->direction = direction;
	this->currentPosition = gameManager.board_to_vec3(tileLocation.x, tileLocation.y)
		+ gameManager.get_orientation_offset(direction);
}

Direction SnakeScaleObject::get_direction() {
	return this->direction;
}

glm::vec2 SnakeScaleObject::get_grid_position() {
	return this->tileLocation;
}

void generate_snake_scale(SnakeScaleObject& snakeScale, AppContext appContext) {
	std::vector<float>& vertices = appContext.get_object_manager().get_orientation(snakeScale.get_direction());
	generate_prism(snakeScale, vertices, appContext);
}