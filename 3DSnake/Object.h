#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Texture.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"

enum Attribute {
	VEC3,
	COLOR,
	TEXTURE
};

class Object 
{
public:
	Object(int vertexCount, Shader shader, TextureManager textureManager);
	Object(unsigned int VBO, unsigned int VAO, int vertexCount, Shader shader, TextureManager textureManager);
	void set_EBO(unsigned int EBO);
	void set_VBO(unsigned int VBO);
	void set_VAO(unsigned int VAO);
	unsigned int get_EBO();
	unsigned int get_VBO();
	unsigned int get_VAO();
	void set_texture(Texture texture);
	Texture get_texture();
	TextureManager* get_texture_manager();
	void generate_buffers(float* vertices, size_t size, GLenum drawType);
	void set_position(glm::vec3 position);
	void set_color(glm::vec3 color);
	glm::vec3 get_color();
	Shader get_shader();
	glm::mat4 get_model();
	void set_model(glm::mat4 model);
	int get_vertexCount();
	bool is_EBO_set();
	bool is_VBO_set();
	bool is_VAO_set();
	bool is_textured();
	void delete_object();
	void set_scale(glm::vec3 scale);

	glm::vec3 default_color = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 currentTranslation;
	glm::vec3 currentScale;
	bool isQueuedTransformation;

private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	bool VBO_set;
	bool VAO_set;
	bool EBO_set;

	bool isTextured;
	glm::vec3 color;
	glm::mat4 model;
	/*glm::vec3 queuedTranslation;
	glm::vec3 queuedScale;*/
	int vertexCount;
	Shader shader;
	Texture texture;
	TextureManager textureManager;
};

#endif
