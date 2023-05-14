#pragma once

#include "OpenGL.h"

class VertexBuffer
{
private:
    // The ID of the Vertex Buffer Object
    GLuint bufferID;
    // The count of elements in the buffer
    std::size_t Count;
    std::size_t Size;
public:
    /*
        @brief Creates a Vertex Buffer Object, unbinds after creation
        @param data: The data to be stored in the buffer
        @param size: The size of the data in bytes
        @param usage: The usage of the buffer static/dynamic, defaults to GL_STATIC_DRAW
    */
    VertexBuffer(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();

    /*
        @brief Binds(selects) the Vertex Buffer Object
    */
    void bind()   const;
    /*
        @brief Unbinds(unselects) the Vertex Buffer Object
    */
    void unbind() const;

    // Sets the number of elements in a single vertex
    inline void setCount(std::size_t count) { this->Count = (Size/sizeof(GLfloat))/count; }

    // Returns the count of elements in the buffer
    inline const std::size_t getCount() const { return Count; }
};