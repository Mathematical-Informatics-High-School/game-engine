#pragma once

#include "OpenGL.h"
#include "Shader.h"
#include <algorithm>

class Mesh
{
public:
    // the vertex attribute
    enum Attrib
    {
        CORDS = 0,
        COLORS,
        NORMALS,
        TEXTURES,
    };

    /*
        @brief  Sets the mesh mode and the size of the vertex attributes.
        @param  mode         The mesh mode (STATIC_DRAW/STREAM_DRAW/DYNAMIC_DRAW).
        @param  cordCount    the number of vertex coordinates(2D/3D).
        @param  colorCount   the number of vertex colors(RGBA or 0 for no colors).
        @param  normalCount  the number of vertex normals(3D or 0 for no normals).
        @param  textureCount the number of vertex texture coordinates(2D/3D or 0 for no texture).
    */
     Mesh(GLenum mode, GLubyte cordCount, GLubyte colorCount, GLubyte normalCount, GLubyte textureCount);
    ~Mesh();

    /*
        @brief declares the specified attribute as dynamic, it will be stored in a seppareate buffer.
    */
    void setAttribMode(Attrib attrib, GLenum mode);

    /*
        @brief  Sets the vertex attribute data.
        @param  attrib  The vertex attribute to set.
        @param  data    The data to set.
        @param  size    The size of the data.
    */
    void setAttribData(Attrib attrib, const void* data, GLsizeiptr size);

    void setElements(const unsigned int* data, GLsizeiptr size);

    // Adds a shader of the specified type to the shader program.
    void setShader(const char* file, GLenum type);

    // builds the Mesh.
    void build();

    void bind() const;
    void unbind() const;

    void defineUniform(const char* name, unsigned short count, GLenum type);
    void setUniform(const char* name, float v1=0, float v2=0, float v3=0, float v4=0);
    void setUniformMat(const char* name, glm::mat4 mat);

    void draw() const;


private:
    // the draw mode
    GLenum Mode;

    // the vertex attribute sizes
    GLubyte attribSizes[4];
    // the vertex attribute modes
    GLenum attribModes[4];

    // the Vertex Array Object
    GLuint vao;
    // the Vertex Buffer Object
    GLuint vbo[5];
    // the Element Buffer Object
    GLuint ebo;

    // the shader program
    Shader shader;

    // coordinates buffer
    float* cords;
    // colors buffer
    float* colors;
    // normals buffer
    float* normals;
    // texture coordinates buffer
    float* textures;

    // the number of vertices
    unsigned int vertexCount;

    // element buffer
    unsigned int* elements;
    unsigned int elementCount;
    GLenum elementType;
};



