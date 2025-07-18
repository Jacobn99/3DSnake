#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <vector>

class Object;
class PrismObject;
class AppContext;
class SnakeScaleObject;

class ObjectManager {
public:
	//bool is_object(Object object);
	void generate_default_vertices(AppContext appContext);
	glm::vec3 get_default_color();
	void unbind_buffers();
	void update_VBO(Object& object, std::vector<float>& vertices, GLenum drawType);
	void bind_object_buffers(Object object);
	void bind_VAO(Object object);
	void bind_VBO(Object object);
	void bind_EBO(Object object);
	void add_default_attributes(Object object);
	void draw_object(Object& object);
	void draw_prism(PrismObject& prismObject);
	std::vector<float>& get_orientation(Direction direction);
private:
	glm::vec3 default_color = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<float> front_orientation;
	std::vector<float> back_orientation;
	std::vector<float> right_orientation;
	std::vector<float> left_orientation;
};

#endif
