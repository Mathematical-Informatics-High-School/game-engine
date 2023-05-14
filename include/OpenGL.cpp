#include "OpenGL.h"


void windowConfig() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
 
}


GLFWwindow* Init(const unsigned int width, const unsigned int height, const char* title) {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Unexpected error occurred. Initialization failed!\n");
        return nullptr;
    }

    windowConfig();

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        printf("Unexpected error occurred. Window creation failed!\n");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Unexpected error occurred. GLEW initialization failed!\n");
        return nullptr;
    }

    return window;
}

void printError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "Error: " << err << std::endl;
    }
}


const std::string read(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{   
    xoffset += alpha * (xpos - lastX) + (1.0f - alpha) * xoffset;
    lastX = xpos;
    yoffset += alpha * (lastY - ypos) + (1.0f - alpha) * yoffset;
    lastY = ypos;
}