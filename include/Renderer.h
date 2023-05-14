#pragma once

#include "OpenGL.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

enum DrawType {
    // treats 3 vertices as a triangle
    TRIANGLES = GL_TRIANGLES,
    // treats 2 vertices as a line
    LINES = GL_LINES,
    // treats 1 vertex as a point
    POINTS = GL_POINTS,
};

class Renderer {
public:
     Renderer();
    ~Renderer();

    /*
        @brief Draws the Vertex Array Object to the screen using its Element Buffers
        @param vao The Vertex Array Object to draw
        @param shader The shader program to use
    */
    void Draw(const VertexArray& vao, const Shader& shader) const;

    /*
        @brief Draws the Vertex Array Object to the screen using its Vertex Buffers
        @param vao The Vertex Array Object to draw
        @param shader The shader program to use
    */
    void DrawArr(const VertexArray& vao, const Shader& shader) const;
    // Clears the screen (BLACK)
    void Clear() const;

    // Sets the draw mode for the renderer
    void setDrawType(DrawType mode);

private:
    unsigned int eboIndex;
    DrawType drawType;
};