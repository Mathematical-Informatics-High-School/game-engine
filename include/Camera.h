#pragma once

#include "OpenGL.h"
#include "Shader.h"
#include <vector>

class Camera 
{
public:
     Camera(unsigned int width, unsigned int height);
    ~Camera();

    void update();
    void processInput(GLFWwindow* window, float offsetX, float offsetY);
    void setSpeed(float speed);
    void setSensitivity(float sensitivity);
    void setFOV(float fov);
    void addShader(Shader* shader);
    glm::vec3 getPosition();

private:
    std::vector<Shader*> shaders;

    glm::vec3 position;
    glm::vec3 front;

    float speed;

    unsigned int width;
    unsigned int height;

    float deltaTime;
    float lastFrame;
    float currentFrame;

    float fov;
    float sensitivity;
    bool firstMouse;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
};