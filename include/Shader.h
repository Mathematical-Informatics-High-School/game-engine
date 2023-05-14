#pragma once

#include "OpenGL.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>


class Shader {
private:
    // The ID of the shader program
    GLuint shaderID;
    // A list of all the shader(OpenGL adresses) that make up this program
    std::vector<GLuint> shaders;
    // A map of all the uniforms in the shader
    std::map<std::string, std::pair<int, GLenum> > uniforms;

public:
    Shader();
    ~Shader();

    /*
        @brief Adds a shader to the program
        @param source File path to the shader source code
        @param type The type of shader
    */
    void addShader(const std::string& source, GLenum type);

    // Links all the shaders together
    void build() const;

    // Binds(selects) the shader program
    void bind()   const;
    // Unbinds(unselects) the shader program
    void unbind() const;

    /*
        @brief Defines a uniform in the shader, so that it can be set later
        @param name The name of the uniform
        @param count The number of components in the uniform
        @param type The type of the uniform
    */
    void defineUniform(std::string name, int count, GLenum type);
    /*
        @brief Sets a value to a uniform
        @param name The name of the uniform
        @param vx Values of the uniform
    */
    void setUniform(std::string name, float v1 = 0.0f, float v2 = 0.0f, float v3 = 0.0f, float v4 = 0.0f);

    /*
        @brief Sets a value to a vector uniform
        @param name The name of the uniform
        @param vx Values of the uniform
    */
    void setUniformVec(std::string name, glm::vec4 vec);

    /*
        @brief Sets a value to a matrix uniform
        @param name The name of the uniform
        @param matrix The matrix to set
    */
    void setUniformMat(std::string name, glm::mat4 matrix);

};