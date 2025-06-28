#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include <glad/glad.h>

class Texture; // Forward declaration of Texture
class AppContext; // Forward declaration of AppContext

class TextureManager {

public:
	TextureManager() = default;
	void set_next_location(int count);
	int get_next_location();
	Texture generate_texture_2D(const char* file_path, GLenum imageDataType, GLenum wrapType, GLenum filterType);
	void use_2D_texture(Texture texture, Shader shader);
private:
	int next_texture_slot = 0;
};
#endif