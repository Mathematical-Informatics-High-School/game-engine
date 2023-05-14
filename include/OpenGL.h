#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


// BOILERPLATE configuration of the window
void windowConfig();


/* @brief Initializes OpenGL and returns a window object. 
 * @example
 * How to use:
 *  ```
 *        GLFWwindow* window = Init(800, 600, "OpenGL");
 * ```
 * @param width  the width of the window.
 * @param height the height of the window.
 * @param title  the title of the window.
 * 
 * 
 */ 
GLFWwindow* Init(const unsigned int width, const unsigned int height, const char* title);

// Prints an error number from glGetError()
void printError();

const std::string read(const std::string& path);

// mouse shit
const GLint HEIGHT = 600;
const GLint WIDTH  = 900;

// bool firstMouse = true;
// double xoffset = 0;
// double yoffset = 0;
// double lastX = WIDTH / 2;
// double lastY = HEIGHT / 2;
// float alpha = 0.4f;

// void mouse_callback(GLFWwindow* window, double xpos, double ypos);