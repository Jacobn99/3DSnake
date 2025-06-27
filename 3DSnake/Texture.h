#ifndef TEXTURE_H
#define TEXTURE_H
//#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
class TextureManager;

class Texture {
public:
	Texture() = default;
	//Texture(TextureManager manager, const char* file_path, GLenum wrapType, GLenum filterType);
	unsigned int get_ID();
	void set_ID(unsigned int ID);
	int get_texture_loc();
	void set_texture_loc(int loc);
	void delete_texture();
	bool get_is_generated();
	void set_is_generated(bool is_generated);
private:
	unsigned int ID;
	int texture_loc;
	bool is_generated;
};

#endif
