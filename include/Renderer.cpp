#include "Renderer.h"

Renderer::Renderer()
{
    drawType = DrawType::TRIANGLES;
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray& vao, const Shader& shader) const
{
    shader.bind();
    vao.bind();

    for (ElementBuffer* ebo : vao.getElementBuffers())
    {
        ebo->bind();
        glDrawElements(drawType, ebo->getCount(), ebo->getType(), 0);
    }
}

void Renderer::DrawArr(const VertexArray& vao, const Shader& shader) const
{
    shader.bind();
    vao.bind();

    for (VertexBuffer* vbo : vao.getBuffers())
    {
        vbo->bind();
        glDrawArrays(drawType, 0, vbo->getCount());
    }
}


void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setDrawType(DrawType type)
{
    drawType = type;
}