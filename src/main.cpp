#include "OpenGL.h"
#include "Shader.h"
#include "Mesh.h"

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


struct Vertex
{
    glm::vec2 position;
};

Vertex vertices[] = {
    glm::vec2(-0.5f, -0.5f),
    glm::vec2( 0.5f, -0.5f),
    glm::vec2(-0.5f,  0.5f),
    glm::vec2( 0.5f,  0.5f),
};

GLuint indices[] = {
    0, 1, 2,
    1, 2, 3
};





int main() {
    Window window = createWindow(800, 600, "OpenGL");

    Mesh mesh = Mesh(sizeof(Vertex));

    mesh.addAttribute(2, GL_FLOAT);

    mesh.setVertices(vertices, sizeof(vertices));
    mesh.setIndices(indices, sizeof(indices));

    mesh.Program.addShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    mesh.Program.addShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    
    mesh.build();
    
    mesh.Program.defineUniform("color", GL_FLOAT_VEC3);
    mesh.Program.setUniform("color", 1.0f, 1.0f, 1.0f);

    printErorr();



    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh.draw();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    destroyWindow(window);
    return EXIT_SUCCESS;
}