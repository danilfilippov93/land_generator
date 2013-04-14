// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>

#include "Triangle.h"
#import "shader.hpp"

Triangle::Triangle()
{
	vertexBuffer=0;
	InitTriangle();
}

void Triangle::InitTriangle()
{
	static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'this->vertexBuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	assert(glIsBuffer(vertexBuffer) == GL_TRUE);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "shader.vertexshader", "shader.fragmentshader" );
}

void Triangle::Draw()
{
	glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	assert(glIsBuffer(vertexBuffer) == GL_TRUE);

	// Get a handle for our buffers
	GLint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");

	glVertexAttribPointer(
	   vertexPosition_modelspaceID,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	 
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	 
	glDisableVertexAttribArray(0);
}
