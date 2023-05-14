#pragma once

#include "OpenGL.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include <vector>

/*
    @brief Returns the size of a type
    @param type OpenGL type
*/
unsigned int getSizeOfType(const GLenum type);

// A single attribute in the layout
struct VertexBufferAttrib {
    GLuint count;
    GLenum type;
    GLboolean normalized;
};

class VertexBufferLayout {
private:
    // List of all the attributes in the layout
    std::vector<VertexBufferAttrib> attributes;
    // The combined size of all the attributes
    unsigned int Stride;

public:
     VertexBufferLayout() : Stride(0) {}
    ~VertexBufferLayout() {}

    /*
        @brief Adds an attribute to the layout
        @param count The number of components, same as the size of vec
        @param type The type of the attribute
        @param normalized Whether the attribute is normalized, default is false
    */
    void addAttribute(const GLuint count, const GLenum type, GLboolean normalized=GL_FALSE);

    inline const std::vector<VertexBufferAttrib>& getAttributes() const { return attributes; }
    inline unsigned int getStride() const { return Stride; }
};


class VertexArray {
private:
    // The ID of the Vertex Array Object
    GLuint arrayID;
    // A vector that holds pointers to all the Vertex Buffer Objects
    // WARNING: remember to delete the pointers if they go out of scope
    std::vector<VertexBuffer*> buffers;
    // A vector that holds pointers to all the Element Buffer Objects
    // WARNING: remember to delete the pointers if they go out of scope
    std::vector<ElementBuffer*> ebuffers;

public:
    /*
        @brief Creates a Vertex Array Object
    */
     VertexArray();
    ~VertexArray();

    /*
        @brief Binds(selects) the Vertex Array Object
    */
    void bind() const;
    /*
        @brief Unbinds(unselects) the Vertex Array Object
    */
    void unbind() const;

    /*
        @brief Adds a Vertex Buffer Object to the Vertex Array Object
        @param vbo The Vertex Buffer Object to be added
        @param layout The layout of the Vertex Buffer Object
    */
    void addBuffer(VertexBuffer* vbo, const VertexBufferLayout& layout);
    /*
        @brief Adds an Element Buffer Object to the Vertex Array Object
        @param ebo The Element Buffer Object to be added
    */
    void addElementBuffer(ElementBuffer* ebo);

    /*
        @brief Sets an OpenGL attribute for the link between the vertx data and the shader attribute
        @param index The index of the attribute, first attribute starts at 0
        @param size The number of components, same as the size of vec
        @param type The type of the attribute
        @param normalized Whether the attribute is normalized
        @param stride The stride is the number of bytes between consecutive vertex attributes, aka the size of one vertex
        @param offset The offset is the number of bytes until the first vertex attribute, aka the size of elements before this attribute
    */
    void setAttribute(const int index, const int size, const GLenum type, const bool normalized, const int stride, const void* offset) const;

    // Binds the buffer at the given index
    void selectBuffer(const int index) const;

    // Binds element buffer at the given index
    void selectElementBuffer(const int index) const;

    inline std::vector<VertexBuffer*>  getBuffers()        const { return buffers;  }
    inline std::vector<ElementBuffer*> getElementBuffers() const { return ebuffers; }
};





