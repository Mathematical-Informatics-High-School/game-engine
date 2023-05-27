#include "Mesh.h"

Mesh::Mesh(u_char VertexSize)
    : mode(GL_TRIANGLES), vboUsage(GL_STATIC_DRAW), eboUsage(GL_STATIC_DRAW)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    _vbo = 0;
    _ebo = 0;

    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    _vertexSize = VertexSize;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void Mesh::addAttribute(u_char count, GLenum type) {
    _attributes.push_back({count, type});
}

void Mesh::setVertices(const void* data, size_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, vboUsage);

    if (_vertexCount == 0) {
        _vertexCount = size / _vertexSize;
    }
}

void Mesh::setIndices(const void* data, size_t size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, eboUsage);

    if (_indicesCount == 0) {
        _indicesCount = size / sizeof(unsigned int);
    }
}

void Mesh::build() const {
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    for (u_char i = 0; i < _attributes.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, _attributes[i].count, _attributes[i].type, GL_FALSE, _vertexSize, (void*)0);
    }

    Program.link(); 
    Program.select();
}

void Mesh::select() const {
    glBindVertexArray(_vao);
}

void Mesh::deselect() const {
    glBindVertexArray(0);
}

void Mesh::draw() const {
    if (_indicesCount > 0) {
        glDrawElements(mode, _indicesCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mode, 0, _vertexCount);
    }
}


