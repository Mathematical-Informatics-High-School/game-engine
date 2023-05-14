#pragma once

#include "OpenGL.h"
#include <string>

class Texture {
private:
    // The ID of the texture
    GLuint textureID;
    // The file path to the texture
    std::string filePath;
    // Local (CPU) buffer for the texture
    unsigned char* buffer;
    // Texture specifications
    int width, height, bpp;

public:
    /*
        @brief Creates a texture from a file
        @param path The file path to the texture
    */
     Texture(const std::string& path);
    ~Texture();

    // Binds(selects) the texture
    void bind(unsigned int slot) const;
    // Unbinds(unselects) the texture
    void unbind()                const;

    inline int getWidth()  const { return width;  }
    inline int getHeight() const { return height; }
};
