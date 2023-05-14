#include "Texture.h"

#include <SOIL/SOIL.h>


Texture::Texture(const std::string& path) 
    : textureID(0), filePath(path), buffer(nullptr), width(0), height(0), bpp(0) 
{
    // Flip the image vertically
    buffer = SOIL_load_image(path.c_str(), &width, &height, &bpp, SOIL_LOAD_RGBA);


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    

    // Configurations
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (buffer) {
        SOIL_free_image_data(buffer);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}