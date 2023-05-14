#pragma once

#include "OpenGL.h"


class ElementBuffer
{
private:
    // The ID of the Element Buffer Object
    GLuint bufferID;
    // The number of elements in the buffer
    GLuint Count;
    // The type of the elements in the buffer
    GLenum Type;
public:
    /*
        @brief Creates an Element Buffer Object
        @param data The data to be stored in the buffer
        @param size The size of the elements in bytes
        @param type The type of the elements in the buffer, defaults to GL_UNSIGNED_SHORT
    */
     ElementBuffer(const GLuint* data, unsigned int size, GLenum type = GL_UNSIGNED_SHORT);
    ~ElementBuffer();

    /*
        @brief Binds(selects) the Element Buffer Object
    */
    void bind() const;
    /*
        @brief Unbinds(unselects) the Element Buffer Object
    */
    void unbind() const;
    /*
        @brief Returns the number of elements in the buffer
    */
    inline GLuint getCount() const { return Count; }
    /*
        @brief Returns the type of the elements in the buffer
    */
    inline GLenum getType() const { return Type; }
};