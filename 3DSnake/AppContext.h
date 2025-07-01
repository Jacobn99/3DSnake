#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"

// Add other manager includes as needed

class AppContext {
public:
    AppContext(GameManager& gameManager, TextureManager& textureManager, Shader& shader, ObjectManager& objectManager);

    GameManager& get_game_manager();
    TextureManager& get_texture_manager();
    Shader& get_shader();
    ObjectManager& get_object_manager();
    // Add more getters as needed

private:
    GameManager& gameManager;
    TextureManager& textureManager;
    Shader& shader;
    ObjectManager& objectManager;
    // Add more manager pointers as needed
};

#endif
