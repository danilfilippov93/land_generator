#include <iostream>
#include <stdexcept>
#include "Display.hpp"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Triangle.hpp"

using namespace glm;
using namespace std;

Display::Display()
{
	this->InitGLFW();
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

void Display::InitWindow()
{
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    glfwEnable( GLFW_STICKY_KEYS );
}

void Display::OpenWindow(){
	this->InitWindow();

	if( !glfwOpenWindow( 600, 400, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		throw runtime_error("Failed in open window");
	}
	glfwSetWindowTitle( "My Land" );

	this->InitGLEW();
	this->UpdateLoop();
}

void Display::UpdateLoop()
{
	triangle = new Triangle();

	do{
        this->Draw();
    } 
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
    glfwGetWindowParam( GLFW_OPENED ) );
}



void Display::Draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	triangle->Draw();
    glfwSwapBuffers();
}

