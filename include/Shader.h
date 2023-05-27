#pragma once

#include "OpenGL.h"

#include <vector>
#include <map>
typedef unsigned int uint;

// TODO: 
// - Add default shaders
// - fix setUniformXXv function for vectors

class Shader 
{
public:
     Shader();
    ~Shader();

    void addShader(const char* path, GLenum shaderType);
    void link() const;

    void select() const;
    void deselect() const;

    void defineUniform(const char* name, GLenum type);
    void setUniform(const char* name, 
        const double v1=0, 
        const double v2=0, 
        const double v3=0, 
        const double v4=0
    ) const;
    void setUniform(const char* name, const GLfloat* mat) const;
    // void setUniformVec(const char* name, const double* vec, const uint count) const;
    // void setUniformMat(const char* name, const double* mat, const uint count) const;

private:
    GLuint program;
    std::vector<GLuint> shaders;
    std::map<const char*, GLenum> uniforms;
};