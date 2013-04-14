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
#include "shaderUtils.hpp"

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

void Display::InitShaders()
{
	shader = new SimpleShader();
}

void Display::InitModelViewProjectionMatrix()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
			glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
			glm::vec3(0,0,0), // and looks at the origin
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
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
	this->InitShaders();
	this->InitModelViewProjectionMatrix();
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

	glUseProgram(shader->shaderID);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(shader->modelViewProjectionUniformID, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangle->vertexBuffer);
	assert(glIsBuffer(triangle->vertexBuffer) == GL_TRUE);

	// Get a handle for our buffers
	GLint vertexPosition_modelspaceID = glGetAttribLocation(shader->shaderID, "vertexPosition_modelspace");

	glVertexAttribPointer(
			GLuint(vertexPosition_modelspaceID),
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

	glfwSwapBuffers();
}

