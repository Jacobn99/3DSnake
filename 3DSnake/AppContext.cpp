#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"


AppContext::AppContext(GameManager* gameManager, TextureManager* textureManager, Shader* shader, ObjectManager* objectManager) {
    this->gameManager = gameManager;
    this->textureManager = textureManager;
	this->shader = shader;
    this->objectManager = objectManager;
}

GameManager& AppContext::get_game_manager() { return *this->gameManager; }
TextureManager& AppContext::get_texture_manager() { return *this->textureManager; }
Shader& AppContext::get_shader() { return *this->shader; }
ObjectManager& AppContext::get_object_manager() { return *this->objectManager; }