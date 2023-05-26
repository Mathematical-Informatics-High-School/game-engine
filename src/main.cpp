#include "OpenGL.h"
#include "Shader.h"

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


    Shader shader;
    shader.addShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    shader.addShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    shader.link();
    shader.select();
    shader.defineUniform("color", GL_FLOAT_VEC3);
    shader.setUniform("color", 1.0f, 0.0f, 0.0f);



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