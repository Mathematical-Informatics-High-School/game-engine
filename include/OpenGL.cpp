#include "OpenGL.h"


Window createWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }


    // CONFIG
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // No Backwards Compatibility
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    Window window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

    return window;
}


void destroyWindow(Window window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

std::string read(const char* path) {
    std::fstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}