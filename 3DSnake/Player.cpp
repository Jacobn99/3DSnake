#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Player.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>

Player::Player(GameManager gameManager) {

}
unsigned int Player::get_length() {
	return this->length;
}
glm::vec2 Player::get_movement_direction() {
	return this->movementDirection;
}
std::queue<int>* Player::get_body_parts() {
	return &bodyParts;
}
void Player::remove_tail() {
	this->bodyParts.pop();
}
//void Player::move_head() {
//	this->bodyParts.push()
//}
//void Player::draw_body();