//#include <iostream>
#include "Display.hpp"

// Include GLM
#include <glm/gtc/matrix_transform.hpp>
#include "controls.hpp"

#ifndef __APPLE__
#include <stdexcept>
#endif

#define WIDTH 600
#define HEIGHT 400

using namespace glm;
using namespace std;

Display::Display()
{
	InitGLFW();
	InitGameObjectsArray();
}

void Display::InitGLFW()
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
}

void Display::InitGameObjectsArray()
{
	gameObjectsArray = new vector<GameObject *>(0);
}

void Display::AddGameObjects(GameObject *gameObject)
{
	if (gameObject == NULL)
		throw std::runtime_error("GameObject == NULL");

	gameObjectsArray->push_back(gameObject);
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

	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetMousePos(int(WIDTH/ 2), int(HEIGHT/ 2));
}

void Display::InitShaders()
{
	shader = new SimpleShader();
}

void Display::UpdateModelViewMatrix()
{
	computeMatricesFromInputs();
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 Projection = getProjectionMatrix();
	// Camera matrix
	mat4 View = getViewMatrix();
	// Model matrix : an identity matrix (model will be at the origin)
	mat4 Model = mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

void GLFWCALL Display::ResizeWindow(int x, int y)
{
	glfwSetWindowSize(x, y);
	glViewport(0, 0, x, y);

}

void Display::OpenWindow()
{
	InitWindow();

	if (!glfwOpenWindow(WIDTH, HEIGHT, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		throw runtime_error("Failed in open window");
	}
	glfwSetWindowTitle("My Land");
	glfwSetWindowSizeCallback(ResizeWindow);

	InitGLEW();
	InitShaders();
	UpdateModelViewMatrix();
}


void Display::Run()
{
	UpdateLoop();
}

void Display::UpdateLoop()
{
	do
	{
		UpdateModelViewMatrix();
		Draw();
	}
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
			glfwGetWindowParam(GLFW_OPENED));
}

void Display::Draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::vector<GameObject *>::iterator itr;
	for (itr = gameObjectsArray->begin(); itr != gameObjectsArray->end(); ++itr)
	{
		DrawObject(*itr);
	}

	glfwSwapBuffers();
}

void Display::DrawObject(GameObject *object)
{
	glUseProgram(shader->shaderID);

	mat4 mvpForObject = translate(mvp, object->position);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(shader->modelViewProjectionUniformID, 1, GL_FALSE, &mvpForObject[0][0]);

	glUniform4f(shader->objectColorUniformID, object->position.z / 10.f, 0, 0, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertexBuffer);
	assert(glIsBuffer(object->vertexBuffer) == GL_TRUE);

	// Get a handle for our buffers
	GLint vertexPosition_modelspaceID = shader->vertexPostitionModelspaceAttributeID;

	glVertexAttribPointer(
			GLuint(vertexPosition_modelspaceID),
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void *) 0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 object
	glDisableVertexAttribArray(0);
}