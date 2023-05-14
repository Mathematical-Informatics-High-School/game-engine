#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum usage)
    : Size(size)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}


VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferID);
}


void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}


void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

