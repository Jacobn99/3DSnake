#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <vector>

class Object;
class PrismObject;
class AppContext;

class ObjectManager {
public:
	//bool is_object(Object object);
	void generate_default_vertices(AppContext appContext);
	void unbind_buffers();
	void bind_object_buffers(Object object);
	void bind_VAO(Object object);
	void bind_VBO(Object object);
	void bind_EBO(Object object);
	void add_default_attributes(Object object);
	void draw_object(Object& object);
	std::vector<float>& get_front_orientation();
	std::vector<float>& get_back_orientation();
	std::vector<float>& get_right_orientation();
	std::vector<float>& get_left_orientation();
private:
	std::vector<float> front_orientation;
	std::vector<float> back_orientation;
	std::vector<float> right_orientation;
	std::vector<float> left_orientation;
};

#endif
