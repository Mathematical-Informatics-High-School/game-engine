#include "OpenGL.h"
#include "Shader.h"

#include <vector>


struct Attribute
{
    u_char count;
    GLenum type;
};

class Mesh
{
public:
    Mesh(u_char VertexSize);
    ~Mesh();

    GLenum mode;
    GLenum vboUsage;
    GLenum eboUsage;

    void addAttribute(u_char count, GLenum type);
    void setVertices(const void* data, size_t size);
    void setIndices(const void* data, size_t size);

    Shader Program;

    void build() const;

    void select() const;
    void deselect() const;

    void draw() const;


private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    u_char _vertexSize;

    u_char _vertexCount;
    size_t _indicesCount;

    std::vector<Attribute> _attributes;

};