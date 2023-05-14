#include "Camera.h"


Camera::Camera(unsigned int width, unsigned int height) {
    position = glm::vec3(0.0f, 1.0f, 3.0f);
    front = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 2.5f;
    sensitivity = 4.4f;
    fov = 45.0f;
    this->width = width;
    this->height = height;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

Camera::~Camera() {}

void Camera::update() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    for (auto shader : shaders) {
        shader->bind();
        shader->setUniformMat("view",       glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f)));
        shader->setUniformMat("projection", glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 10.0f));
    }

}

void Camera::processInput(GLFWwindow* window, float offsetX, float offsetY) { 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += speed * front * deltaTime;
    } else 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= speed * front * deltaTime;
    } else
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
    } else
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
    }
        


    offsetX = offsetX * sensitivity * deltaTime;
    offsetY = offsetY * sensitivity * deltaTime;


    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }


    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

}

void Camera::setSpeed(float speed) {
    this->speed = speed;
}

void Camera::setSensitivity(float sensitivity) {
    this->sensitivity = sensitivity;
}

void Camera::setFOV(float fov) {
    this->fov = fov;
}

void Camera::addShader(Shader* shader) {
    shaders.push_back(shader);
}

glm::vec3 Camera::getPosition() {
    return position; 
}