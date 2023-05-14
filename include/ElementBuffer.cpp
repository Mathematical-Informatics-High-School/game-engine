#include "ElementBuffer.h"


ElementBuffer::ElementBuffer(const GLuint* data, GLuint size, GLenum type)
    : Type(type)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    if (type == GL_UNSIGNED_SHORT)
        Count = size / sizeof(GLushort);
    else if (type == GL_UNSIGNED_INT)
        Count = size / sizeof(GLuint);
    else
        Count = 0;
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &bufferID);
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

