#include <vector>
#ifndef OBJECT_H
#define OBJECT_H

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
	void add_default_attributes();
	void generate_buffers(float vertices[], size_t size, GLenum drawType);
	void draw_object();
	void set_position(glm::vec3 position);
	void set_color(glm::vec3 color);
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
};

#endif
