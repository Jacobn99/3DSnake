#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Texture.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"

enum Attribute {
	VEC3,
	COLOR,
	TEXTURE
};

class Object 
{
public:
	Object(int vertexCount, Shader shader);
	Object(unsigned int VBO, unsigned int VAO, int vertexCount, Shader shader);
	void set_EBO(unsigned int EBO);
	void set_VBO(unsigned int VBO);
	void set_VAO(unsigned int VAO);
	unsigned int* get_EBO();
	unsigned int* get_VBO();
	unsigned int* get_VAO();
	void set_position(glm::vec3 position);
	void set_color(glm::vec3 color);
	glm::vec3 get_color();
	Shader get_shader();
	glm::mat4 get_model();
	int get_vertexCount();
	//void apply_texture(Texture texture);
	void free_object();

	glm::vec3 default_color = glm::vec3(0.0f, 0.0f, 0.0f);

private:
	unsigned int* VBO;
	unsigned int* VAO;
	unsigned int* EBO;
	bool isTextured;
	glm::vec3 color;
	glm::mat4 model;
	int vertexCount;
	Shader shader;
	//Texture* texture;
};

#endif
