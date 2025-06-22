#ifndef OBJECT_H
#define OBJECT_H


class Object 
{
public:
	Object(float vertices[]);
	Object(unsigned int VBO, unsigned int VAO);
	void set_EBO(unsigned int EBO);

private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	void is_object(Object ob);
};

#endif
