#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\stb_image.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Texture.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"

Texture::Texture() {
	this->is_generated = false;
	this->ID = 0;
}
unsigned int Texture::get_ID() {
	return this->ID;
}
void Texture::set_ID(unsigned int ID) {
	this->ID = ID;
}
int Texture::get_texture_loc() {
	return this->texture_loc;
}
void Texture::set_texture_loc(int loc) {
	this->texture_loc = loc;
}
void Texture::delete_texture() {
	glDeleteTextures(1, &this->ID);
}
bool Texture::get_is_generated() {
	return this->is_generated;
}
void Texture::set_is_generated(bool is_generated) {
	this->is_generated = is_generated;
}