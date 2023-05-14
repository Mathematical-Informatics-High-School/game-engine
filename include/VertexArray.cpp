#include "VertexArray.h"
#include <iostream>


unsigned int getSizeOfType(const GLenum type) {
    switch (type) {
        case GL_FLOAT:         return sizeof(GLfloat);
        case GL_UNSIGNED_INT:  return sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
    }
    return 0;
}


void VertexBufferLayout::addAttribute(const GLuint count, const GLenum type, GLboolean normalized) {
    attributes.push_back({ count, type, normalized });
    Stride += count * getSizeOfType(type);
}


// VAO

VertexArray::VertexArray() {
    glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::bind() const {
    glBindVertexArray(arrayID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer* vbo, const VertexBufferLayout& layout) {
    bind();
    vbo->bind();
    buffers.push_back(vbo);


    const auto& attributes = layout.getAttributes();

    int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        
        setAttribute(i, attributes[i].count, attributes[i].type, attributes[i].normalized, layout.getStride(), (const void*)offset);

        offset += attributes[i].count * getSizeOfType(attributes[i].type);  
        // offset incereases as the layout progresses giving each attribute its appropriate offset
    }
}

void VertexArray::addElementBuffer(ElementBuffer* ebo) {
    bind();
    ebo->bind();
    ebuffers.push_back(ebo);
}


void VertexArray::setAttribute(const int index, const int size, const GLenum type, const bool normalized, const int stride, const void* offset) const {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void VertexArray::selectBuffer(const int index) const {
    buffers[index]->bind();
}

void VertexArray::selectElementBuffer(const int index) const {
    ebuffers[index]->unbind();
}
