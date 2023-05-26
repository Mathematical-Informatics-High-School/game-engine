#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


typedef GLFWwindow* Window;

/*!
    * \brief Initializes the OpenGL context and also creates a pointer to the window. The type of the pointer it returns has been set to Window(not Window*).
    * \param width The width of the window.
    * \param height The height of the window.
    * \param title The title of the window.
    * \note Since this also initializes the OpenGL context, you don't need to initialize it again, so be careful where you call this function.
*/
Window createWindow(int width, int height, const char* title);


/*!
    * \brief Destroys the window and terminates the OpenGL context.
    * \param window The window to destroy.
    * \note Be careful when multithreading!
*/
void destroyWindow(Window window);


/*!
    * \brief Reads a file and returns a pointer to the contents of the file.
    * \param path The path to the file.
*/
std::string readFile(const char* path);
