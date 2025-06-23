#ifndef OBJECT_H
#define OBJECT_H

enum Attribute {
	Vec3,
	Color,
	Texture
};

class Object 
{
public:
	Object(int vertexCount, Shader shader);
	Object(unsigned int VBO, unsigned int VAO, GLuint* vertexAttributeLoc, GLuint* vertexAttributeStart, int vertexCount, Shader shader);
	void set_EBO(unsigned int EBO);
	void set_VBO(unsigned int VBO);
	void set_VAO(unsigned int VAO);
	unsigned int* get_EBO();
	unsigned int* get_VBO();
	unsigned int* get_VAO();
	GLuint* get_vertexAttributeLoc();
	GLuint* get_vertexAttributeStart();
	void add_vertex_attribute(Attribute attribute);
	void generate_buffers(float vertices[], GLenum drawType);
	void draw_object();
	void set_position(glm::vec3 position);

private:
	unsigned int* VBO;
	unsigned int* VAO;
	unsigned int* EBO;
	glm::mat4 model;
	int vertexCount;
	GLuint* vertexAttributeLoc;
	GLuint* vertexAttributeStart;
	Shader shader;
};

#endif
