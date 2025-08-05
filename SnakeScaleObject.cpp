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
#include <algorithm>
//								  V V In row, col order V V

SnakeScaleObject::SnakeScaleObject(glm::vec2 tileLocation, Direction direction, int vertexCount, Shader& shader, AppContext appContext)
	: PrismObject(vertexCount, shader, appContext) {
	GameManager gameManager = appContext.get_game_manager();
	//this->tileLocation = tileLocation;
	this->direction = direction;
	this->currentAssignedPosition = gameManager.board_to_vec3(tileLocation);
	//this->set_color(glm::vec3(30,80,20) / 255.0f);
	this->set_texture(gameManager.get_generated_texture(SNAKE));
}
void SnakeScaleObject::set_position(glm::vec3 position) {
	this->prevPosition = this->currentAssignedPosition;
	this->currentAssignedPosition = position;
	this->isQueuedTransformation = true;
}
glm::vec3 SnakeScaleObject::get_prev_position() {
	return this->prevPosition;
}
Direction SnakeScaleObject::get_direction() {
	return this->direction;
}
void SnakeScaleObject::set_adjusted_position(glm::vec3 position, AppContext appContext) {
	this->currentAssignedPosition = position + appContext.get_game_manager().get_orientation_offset(this->direction);
	this->isQueuedTransformation = true;
}
float SnakeScaleObject::get_largest_dimension()
{
	glm::vec3 scale = get_scale();
	//return 1.0f;
	return std::max(scale.y, std::max(scale.x, scale.z));
}

SnakeScaleObject generate_snake_scale(glm::vec2 tileLocation, Direction direction, 
	Shader& shader, AppContext appContext) {
	GameManager gameManager = appContext.get_game_manager();
	SnakeScaleObject snakeScale = SnakeScaleObject(tileLocation, direction, 36, shader, appContext);

	//set_orientation(snakeScale, direction, appContext);
	std::vector<float>& vertices = appContext.get_object_manager().get_orientation(direction);
	generate_prism(snakeScale, vertices, appContext);
	set_orientation(snakeScale, direction, appContext);
	snakeScale.set_position(snakeScale.get_position() + gameManager.get_orientation_offset(snakeScale.get_direction()));

	//set_orientation_with_offset(snakeScale, direction, appContext);

	return snakeScale;
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

void set_snake_orientation_with_offset(SnakeScaleObject& scale, Direction direction, bool wasOffset, AppContext appContext) {
	assert(scale.get_scale().x > 0.0f && scale.get_scale().y > 0.0f && scale.get_scale().z > 0.0f);
	
	GameManager gameManager = appContext.get_game_manager();
	Direction oldDirection = scale.get_direction();
	set_orientation(scale, direction, appContext);

	// Revert previous orientation offset
	if(wasOffset) scale.set_position(scale.get_position() - gameManager.get_orientation_offset(scale.get_direction()));
	scale.set_direction(direction);

	// Set new orientation offset
	scale.set_position(scale.get_position() + gameManager.get_orientation_offset(scale.get_direction()));

	// Account for length of scale
	scale.set_position(scale.get_position() - get_scaled_grid_vector(scale.get_direction(),
		scale.get_scale(), gameManager.unitsPerTile));
}

glm::vec3 centered_vec3_to_edge(SnakeScaleObject snakeScale, glm::vec3 position, AppContext appContext) {
	float length/* = std::round(scale.get_largest_dimension())*/;
	glm::vec3 scale = snakeScale.get_scale();	
	Direction direction = snakeScale.get_direction();

	if (direction == FORWARD || direction == BACKWARD) length = std::round(scale.z);
	else length = std::round(scale.x);

	glm::vec3 offsetUnitVector = get_vec3_directional_grid_offset(snakeScale.get_direction(), appContext);
	glm::vec3 offset = offsetUnitVector * (length);

	//offset = offset + (offsetUnitVector * 0.5f);
	
	return position + offset;
}