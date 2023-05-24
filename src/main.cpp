#include "OpenGL.h"

#include <bits/stdc++.h>

// SQUARE
float cords[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,

    -0.5f,  0.5f,
    -0.5f, -0.5f,
     0.5f,  0.5f,
};



int main() {
    Window window = createWindow(800, 600, "OpenGL");

    

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(cords), 
        cords, 
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        2 * sizeof(float), 
        (void*)0
    );
    glEnableVertexAttribArray(0);


    std::string vertexShaderSource = read("shaders/vertex.glsl");
    std::string fragmentShaderSource = read("shaders/fragment.glsl");



    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSourceC = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
    glCompileShader(vertexShader);

    // GLint success;
    // GLchar infoLog[512];
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    // if (!success) {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cerr << "Failed to compile vertex shader: " << infoLog << std::endl;
    // }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourceC = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
    glCompileShader(fragmentShader);


    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);


    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);




    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);





    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    destroyWindow(window);
    return EXIT_SUCCESS;
}