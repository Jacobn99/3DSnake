#ifndef PRISM_OBJECT_H
#define PRISM_OBJECT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include <vector>
#include <stdio.h>
#include <iostream>

//enum Direction { FORWARD, BACKWARD, LEFT, RIGHT }; // Define the Direction enum

class PrismObject : public Object {
public:
	using Object::Object;
	PrismObject() = default;
	PrismObject(int vertexCount, Shader& shader, AppContext appContext);
	std::vector<float>* vertices;
	bool orientationChanged;
private:
	bool changeQueued;
};

class SnakeScaleObject : public PrismObject {
public:
	using PrismObject::PrismObject;
	SnakeScaleObject(glm::vec2 tileLocation, Direction direction, int vertexCount, Shader& shader, AppContext appContext);
	Direction get_direction();
	void set_direction(Direction newDirection);
	void set_adjusted_position(glm::vec3 position, AppContext appContext); // Adjusts position based on object orientation to be centered
	glm::vec3 get_prev_position();
	void set_position(glm::vec3 position) override;
	float get_largest_dimension();
private:
	//glm::vec Locations;
	Direction direction;
	glm::vec3 prevPosition;
};

glm::vec3 centered_vec3_to_edge(SnakeScaleObject scale, glm::vec3 position, AppContext appContext);
glm::vec3 get_length_offset(Direction direction, float length, bool scalePositive, AppContext appContext);
glm::vec3 get_initial_scaling(Direction direction);
void set_snake_orientation_with_offset(SnakeScaleObject& scale, Direction direction, bool wasOffset, AppContext appContext);
SnakeScaleObject generate_snake_scale(glm::vec2 tileLocation, Direction direction, Shader& shader, AppContext appContext);
void generate_prism(PrismObject& prism, AppContext appContext, float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);
void generate_prism(PrismObject& prism, std::vector<float>& vertices, AppContext appContext);
void set_orientation(PrismObject& prism, Direction direction, AppContext appContext);
std::vector<float> generate_prism_vertices(float xNeg, float xPos, float yNeg, float yPos, float zNeg, float zPos, float range);


#endif
