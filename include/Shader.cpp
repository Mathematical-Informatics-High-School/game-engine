#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"



Shader::Shader() {
    shaderID = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(shaderID);
}

void Shader::addShader(const std::string& source, GLenum type) {
    shaders.push_back(glCreateShader(type)); 

    const std::string raw = read(source);
    const char* src = raw.c_str();

    glShaderSource(shaders.back(), 1, &src, NULL);
    glCompileShader(shaders.back());
}

void Shader::build() const{
    for (GLuint shader : shaders) {
        glAttachShader(shaderID, shader);
    }
    glLinkProgram(shaderID);
}


void Shader::bind() const {
    glUseProgram(shaderID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::defineUniform(std::string name, int size, GLenum type) {
    uniforms[name] = std::make_pair(size, type);
}

void Shader::setUniform(std::string name, float v1, float v2, float v3, float v4) {
    if (uniforms.find(name) == uniforms.end()) {
        std::cerr << "Error: Uniform " << name << " not found" << std::endl;
        return;
    }

    GLint uniform = glGetUniformLocation(shaderID, name.c_str());

    if (uniforms[name].second == GL_FLOAT) {
        switch (uniforms[name].first)
        {
        case 1: glUniform1f(uniform, v1);             break;

        case 2: glUniform2f(uniform, v1, v2);         break;

        case 3: glUniform3f(uniform, v1, v2, v3);     break;

        case 4: glUniform4f(uniform, v1, v2, v3, v4); break;

        default:
            break;
        }
    } else if (uniforms[name].second == GL_INT) {
        switch (uniforms[name].first)
        {
        case 1: glUniform1i(uniform, (int)v1);             break;

        case 2: glUniform2i(uniform, (int)v1, (int)v2);         break;

        case 3: glUniform3i(uniform, (int)v1, (int)v2, (int)v3);     break;

        case 4: glUniform4i(uniform, (int)v1, (int)v2, (int)v3, (int)v4); break;

        default:
            break;
        }
    } else {
        std::cerr << "Error: Uniform " << name << " has an unsupported type" << std::endl;
    }
}

void Shader::setUniformVec(std::string name, glm::vec4 vec) {
    if (uniforms.find(name) == uniforms.end()) {
        std::cerr << "Error: Uniform " << name << " not found" << std::endl;
        return;
    }

    GLint uniform = glGetUniformLocation(shaderID, name.c_str());

    switch (uniforms[name].first)
    {
    case 1: glUniform1f(uniform, vec.x);                    break;

    case 2: glUniform2f(uniform, vec.x, vec.y);              break;

    case 3: glUniform3f(uniform, vec.x, vec.y, vec.z);       break;

    case 4: glUniform4f(uniform, vec.x, vec.y, vec.z, vec.w); break;

    default:
        break;
    }
}

void Shader::setUniformMat(std::string name, glm::mat4 mat) {
    if (uniforms.find(name) == uniforms.end()) {
        std::cerr << "Error: Uniform " << name << " not found" << std::endl;
        return;
    }

    glUniformMatrix4fv(
        glGetUniformLocation(shaderID, name.c_str()), 
        1,
        GL_FALSE, 
        glm::value_ptr(mat)
    );
}

