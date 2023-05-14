#include "Mesh.h"

Mesh::Mesh(GLenum mode, GLubyte cordCount, GLubyte colorCount, GLubyte normalCount, GLubyte textureCount)
{
    // set the draw mode
    Mode = mode;

    // set the vertex attribute sizes
    attribSizes[CORDS] = cordCount;
    attribSizes[COLORS] = colorCount;
    attribSizes[NORMALS] = normalCount;
    attribSizes[TEXTURES] = textureCount;

    // set the vertex attribute modes
    attribModes[CORDS] = GL_STATIC_DRAW;
    attribModes[COLORS] = GL_STATIC_DRAW;
    attribModes[NORMALS] = GL_STATIC_DRAW;
    attribModes[TEXTURES] = GL_STATIC_DRAW;

    // set the vertex attribute data
    cords = NULL;
    colors = NULL;
    normals = NULL;
    textures = NULL;

    // set the element data
    elements = NULL;
    elementCount = 0;

    // Initialize the Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

Mesh::~Mesh()
{
    // delete the vertex attribute data
    delete[] cords;
    delete[] colors;
    delete[] normals;
    delete[] textures;
    delete[] elements;

    // delete the vertex buffer objects
    glDeleteBuffers(5, vbo);

    // delete the element buffer object
    glDeleteBuffers(1, &ebo);

    // delete the vertex array object
    glDeleteVertexArrays(1, &vao);
}

void Mesh::setAttribMode(Attrib attrib, GLenum mode)
{
    // set the vertex attribute mode
    attribModes[attrib] = mode;
    if (mode != GL_STATIC_DRAW) {
        // create the vertex buffer object
        glGenBuffers(1, &vbo[attrib]);
    }
}

void Mesh::setAttribData(Attrib attrib, const void* data, GLsizeiptr size)
{
    if (attribModes[attrib] == GL_STATIC_DRAW) {
        switch (attrib) {
        case CORDS:
            cords = new float[size / sizeof(float)];
            memcpy(cords, data, size);
            vertexCount = (size / sizeof(float)) / attribSizes[CORDS];
            break;
        case COLORS:
            colors = new float[size / sizeof(float)];
            memcpy(colors, data, size);
            break;
        case NORMALS:
            normals = new float[size / sizeof(float)];
            memcpy(normals, data, size);
            break;
        case TEXTURES:
            textures = new float[size / sizeof(float)];
            memcpy(textures, data, size);
            break;
        }
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[attrib]);
        glBufferData(GL_ARRAY_BUFFER, size, data, attribModes[attrib]);
    }
}


void Mesh::setElements(const unsigned int* data, GLsizeiptr size)
{
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    unsigned int elementCount = size / sizeof(unsigned int);

    if (*std::max_element(data, data + elementCount) < 256) {
        GLsizeiptr newSize = size / 4;
        unsigned char newData[newSize/1];

        for (unsigned int i = 0; i < elementCount; i++) {
            newData[i] = data[i];
        }

        elementType = GL_UNSIGNED_BYTE;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSize, newData, Mode);

    } else 
    if (*std::max_element(data, data + elementCount) < 65536) {
        GLsizeiptr newSize = size / 2;
        unsigned char newData[newSize/2];

        for (unsigned int i = 0; i < elementCount; i++) {
            newData[i] = data[i];
        }

        elementType = GL_UNSIGNED_SHORT;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSize, newData, Mode);
    } else {
        elementType = GL_UNSIGNED_INT;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, Mode);
    }
}


void Mesh::setShader(const char* file, GLenum type)
{
    shader.addShader(file, type);
}


void Mesh::build() {
    // build the shader program
    try {
        shader.build();
    } catch (const char* error) {
        std::cout << error << std::endl;
    }

    // get all the static vertex attributes in one vbo
    unsigned short nAttribs = 0;
    for (unsigned short i = 0; i < 4; i++) {
        if (attribModes[i] == GL_STATIC_DRAW) {
            nAttribs += attribSizes[i];
        }
    }

    float data[nAttribs*vertexCount];
    unsigned int j = 0;

    for (unsigned int i = 0; i < nAttribs*vertexCount; i += nAttribs) {
        j = 0;

        if (attribSizes[CORDS] > 0) {
            for (unsigned int k = 0; k < attribSizes[CORDS]; k++) {
                data[i + j] = cords[(i / nAttribs) + k];
                j++;
            }
        }
        if (attribSizes[COLORS] > 0) {
            for (unsigned int k = 0; k < attribSizes[COLORS]; k++) {
                data[i + j] = colors[(i / nAttribs) + k];
                j++;
            }
        }
        if (attribSizes[NORMALS] > 0) {
            for (unsigned int k = 0; k < attribSizes[NORMALS]; k++) {
                data[i + j] = normals[(i / nAttribs) + k];
                j++;
            }
        }
        if (attribSizes[TEXTURES] > 0) {
            for (unsigned int k = 0; k < attribSizes[TEXTURES]; k++) {
                data[i + j] = textures[(i / nAttribs) + k];
                j++;
            }
        }
    }

    for (int i =0; i < 12; i += 2) {
        std::cout << data[i] << " " << data[i+1] << std::endl;
    }

    glGenBuffers(1, &vbo[4]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    

    // set the vertex attribute pointers considering all vbos
    if (attribSizes[CORDS] > 0) {
        if (attribModes[CORDS] != GL_STATIC_DRAW) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[CORDS]);
        } else {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        }
        glVertexAttribPointer(0, attribSizes[CORDS], GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
    }

    if (attribSizes[COLORS] > 0) {
        if (attribModes[COLORS] != GL_STATIC_DRAW) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[COLORS]);
        } else {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        }
        glVertexAttribPointer(1, attribSizes[COLORS], GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);
    }

    if (attribSizes[NORMALS] > 0) {
        if (attribModes[NORMALS] != GL_STATIC_DRAW) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMALS]);
        } else {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        }
        glVertexAttribPointer(2, attribSizes[NORMALS], GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);
    }

    if (attribSizes[TEXTURES] > 0) {
        if (attribModes[TEXTURES] != GL_STATIC_DRAW) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXTURES]);
        } else {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        }
        glVertexAttribPointer(3, attribSizes[TEXTURES], GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(3);
    }

    shader.bind();
}

void Mesh::bind() const{
    shader.bind();
    
    glBindVertexArray(vao);
    glBindBuffer(GL_VERTEX_ARRAY, vbo[4]);
}

void Mesh::unbind() const{
    glBindVertexArray(0);
    shader.unbind();
}

void Mesh::defineUniform(const char* name, unsigned short count, GLenum type) {
    shader.defineUniform(name, count, type);
}

void Mesh::setUniform(const char* name, float v1, float v2, float v3, float v4) {
    shader.setUniform(name, v1, v2, v3, v4);
}

void Mesh::setUniformMat(const char* name, glm::mat4 mat) {
    shader.setUniformMat(name, mat);
}

void Mesh::draw() const {
    if (elementCount > 0) {
        glDrawElements(Mode, elementCount, elementType, 0);
    } else {
        glDrawArrays(Mode, 0, vertexCount);
    }
}
