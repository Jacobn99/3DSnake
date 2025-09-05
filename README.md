# 3DSnake
Coded in C++, 3D Snake is a 3D rendered version of Snake made using a custom game engine. OpenGL, glad, GLFW, and the GLM libraries are used to render 3D objects. A vertex and fragment shader were custom-made in GLSL to draw colors and textures.

The camera is modeled as a frustum containing all the renderable coordinates. For each object\mesh local coordinates are stored in a vector for efficient storage. These local coordinates are then converted into world coordinates via a model matrix. 

World coordinates, which are relative to the origin of the whole 3D space, are then modified via a "look-at" matrix. The look-at matrix is combination of a translation matrix to align the camera position with it's origin and a rotation matrix to apply it's rotational properties (pitch, yaw, roll). This process converts world coordinates into view coordinates, or coordinates relative to where the camera is looking.

In the fourth step of the process...

...TO BE CONTINUED...
