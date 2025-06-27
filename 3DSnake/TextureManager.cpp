//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <stdio.h>
//#include <iostream>
//#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
//#include "stb_image.h"
//
//
//int TextureManager::get_texture_count() {
//    return this->texture_count;
//}
//
//void TextureManager::set_texture_count(int count) {
//    this->texture_count = count;
//}
//
//void TextureManager::generate_texture_2D(Texture texture, const char* file_path, GLenum wrapType, GLenum filterType) {
//    int width, height, nrChannels;
//    unsigned char* data;
//
//    glBindTexture(GL_TEXTURE_2D, texture.get_ID());
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
//
//    data = stbi_load(file_path,
//        &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//        std::cerr << "Failed to load container.jpg\n";
//
//    //Frees texture from memory
//    stbi_image_free(data);
//}