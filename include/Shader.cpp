#include "Shader.h"
#include <iostream>

Shader::Shader()
{
    program = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::addShader(const char* path, GLenum type) {
    std::string shaderString = readFile(path);
    const char* shaderSource = shaderString.c_str();

    shaders.push_back(glCreateShader(type));
    glShaderSource(shaders.back(), 1, &shaderSource, NULL);
    glCompileShader(shaders.back());

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shaders.back(), GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaders.back(), 512, NULL, infoLog);
        std::cout << "Shader compilation failed:\n" << infoLog << std::endl;
    }

    glAttachShader(program, shaders.back());
}

void Shader::link() const {
    glLinkProgram(program);
}

void Shader::select() const {
    glUseProgram(program);
}

void Shader::deselect() const {
    glUseProgram(0);
}

void Shader::defineUniform(const char* name, GLenum type) {
    if (glGetUniformLocation(program, name) == -1) {
        std::cout << "Uniform " << name << " not found!" << std::endl;
        return;
    }
    if (uniforms.find(name) != uniforms.end()) {
        std::cout << "Uniform " << name << " already defined!" << std::endl;
        return;
    }

    uniforms[name] = type;
}

void Shader::setUniform(const char* name, 
    const double v1, 
    const double v2, 
    const double v3, 
    const double v4
) const {
    if (uniforms.find(name) == uniforms.end()) {
        std::cout << "Uniform " << name << " not defined!" << std::endl;
        return;
    }

    switch (uniforms.at(name)) {
        case GL_FLOAT:
            glUniform1f(glGetUniformLocation(program, name), v1);
            break;
        case GL_FLOAT_VEC2:
            glUniform2f(glGetUniformLocation(program, name), v1, v2);
            break;
        case GL_FLOAT_VEC3:
            glUniform3f(glGetUniformLocation(program, name), v1, v2, v3);
            break;
        case GL_FLOAT_VEC4:
            glUniform4f(glGetUniformLocation(program, name), v1, v2, v3, v4);
            break;
        case GL_INT:
            glUniform1i(glGetUniformLocation(program, name), v1);
            break;
        case GL_INT_VEC2:
            glUniform2i(glGetUniformLocation(program, name), v1, v2);
            break;
        case GL_INT_VEC3:
            glUniform3i(glGetUniformLocation(program, name), v1, v2, v3);
            break;
        case GL_INT_VEC4:
            glUniform4i(glGetUniformLocation(program, name), v1, v2, v3, v4);
            break;
        case GL_UNSIGNED_INT:
            glUniform1ui(glGetUniformLocation(program, name), v1);
            break;
        case GL_UNSIGNED_INT_VEC2:
            glUniform2ui(glGetUniformLocation(program, name), v1, v2);
            break;
        case GL_UNSIGNED_INT_VEC3:
            glUniform3ui(glGetUniformLocation(program, name), v1, v2, v3);
            break;
        case GL_UNSIGNED_INT_VEC4:
            glUniform4ui(glGetUniformLocation(program, name), v1, v2, v3, v4);
            break;
        case GL_DOUBLE:
            glUniform1d(glGetUniformLocation(program, name), v1);
            break;
        case GL_DOUBLE_VEC2:
            glUniform2d(glGetUniformLocation(program, name), v1, v2);
            break;
        case GL_DOUBLE_VEC3:
            glUniform3d(glGetUniformLocation(program, name), v1, v2, v3);
            break;
        case GL_DOUBLE_VEC4:
            glUniform4d(glGetUniformLocation(program, name), v1, v2, v3, v4);
            break;
        default:
            std::cout << "Uniform " << name << " has invalid type!" << std::endl;
            break;
    }
}

void Shader::setUniform(const char* name, const GLfloat* mat) const  {
    if (uniforms.find(name) == uniforms.end()) {
        std::cout << "Uniform " << name << " not defined!" << std::endl;
        return;
    }

    switch (uniforms.at(name)) {
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT4x3:
            glUniformMatrix4x3fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT4x2:
            glUniformMatrix4x2fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT3x4:
            glUniformMatrix3x4fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT3x2:
            glUniformMatrix3x2fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT2x4:   
            glUniformMatrix2x4fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        case GL_FLOAT_MAT2x3:
            glUniformMatrix2x3fv(glGetUniformLocation(program, name), 1, GL_FALSE, mat);
            break;
        default:
            std::cout << "Uniform " << name << " has invalid type!" << std::endl;
            break;
    }
}
