#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

class Object;
class PrismObject;

//bool is_object(Object object);
void unbind_buffers();
void bind_object_buffers(Object object);
void bind_VAO(Object object);
void bind_VBO(Object object);
void bind_EBO(Object object);
void add_default_attributes(Object object);
void draw_object(Object* object);

#endif
