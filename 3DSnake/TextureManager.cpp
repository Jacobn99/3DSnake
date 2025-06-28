#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Texture.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "stb_image.h"


int TextureManager::get_next_location() {
    return this->next_texture_slot;
}

void TextureManager::set_next_location(int count) {
    this->next_texture_slot = count;
}

Texture TextureManager::generate_texture_2D(const char* file_path, GLenum imageDataType, GLenum wrapType, GLenum filterType) {
    int width, height, nrChannels;
    unsigned char* data;
    
    Texture texture = Texture();
    texture.set_texture_loc(this->get_next_location());
    this->set_next_location(this->get_next_location() + 1);
    unsigned int ID = 0;

    glGenTextures(1, &ID);
    texture.set_ID(ID);
    glBindTexture(GL_TEXTURE_2D, texture.get_ID());
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);

    data = stbi_load(file_path,
        &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, imageDataType, width, height, 0, imageDataType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cerr << "Failed to load container.jpg\n";

    //Frees texture from memory
    stbi_image_free(data);

    /*glActiveTexture(GL_TEXTURE0 + texture.get_texture_loc());
    glBindTexture(GL_TEXTURE_2D, texture.get_ID());*/
    texture.set_is_generated(true);
    return texture;
}
void TextureManager::use_2D_texture(Texture texture, Shader shader) {
    assert(texture.get_is_generated());
    shader.setBool("isTextured", true);
	shader.setInt("texture1", texture.get_texture_loc());
    glActiveTexture(GL_TEXTURE0 + texture.get_texture_loc());
    glBindTexture(GL_TEXTURE_2D, texture.get_ID());
}