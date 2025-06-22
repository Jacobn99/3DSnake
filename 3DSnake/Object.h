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
	Object();
	Object(unsigned int VBO, unsigned int VAO, GLuint* vertexAttributeLoc, GLuint* vertexAttributeStart);
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

private:
	unsigned int* VBO;
	unsigned int* VAO;
	unsigned int* EBO;
	GLuint* vertexAttributeLoc;
	GLuint* vertexAttributeStart;
};

#endif
