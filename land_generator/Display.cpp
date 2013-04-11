#include <iostream>
#include <stdexcept>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

class Display {
    public:
    Display();
    private:
    // Initializations
    void InitGLFW();
    void InitGLEW();
};

Display::Display()
{
    this->InitGLFW();
    this->InitGLEW();
}

void Display::InitGLFW()
{
    if( !glfwInit() )
    {
        throw runtime_error("Failed to initialize GLFW");
    }
}

void Display::InitGLEW()
{
    if (glewInit() != GLEW_OK)
    {
        throw runtime_error("Faild to initialize GLEW");
    }
}