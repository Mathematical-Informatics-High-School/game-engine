#include "OpenGL.h"
#include "Utils.h"
#include <bits/stdc++.h>

glm::mat4 model(1.0f);


float cords[] = {
     // draw a rect
    -0.5f, -0.5f, 
    0.5f, -0.5f, 
    0.5f,  0.5f, 

    0.5f,  0.5f, 
    -0.5f,  0.5f,
    -0.5f, -0.5f,

};


// Camera camera;

int main() {
    GLFWwindow* window = Init(WIDTH, HEIGHT, "Nostalgia 3D");

    // GLuint vao, vbo;
    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);

    // glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cords), cords, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(0);

    // Shader shader;
    // shader.addShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    // shader.addShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    // shader.build();
    // shader.bind();

    Mesh mesh = Mesh(GL_TRIANGLES, 2, 0, 0, 0);
    mesh.setAttribData(Mesh::Attrib::CORDS, cords, sizeof(cords));
    mesh.setShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    mesh.setShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    mesh.build();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        mesh.draw();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    
    glfwTerminate();
    return EXIT_SUCCESS;
}



