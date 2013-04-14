#include <iostream>
#include "Display.hpp"

// Include GLM
#include <glm/gtc/matrix_transform.hpp>

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
		throw runtime_error("Failed to initialize GLFW");
	}
}

void Display::InitGameObjectsArray()
{
	gameObjectsArray = new std::vector<GameObject*>(0);
}

void Display::AddGameObjects(GameObject *gameObject)
{
	if (gameObject == NULL)
		throw runtime_error("GameObject == NULL");

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
}

void Display::InitShaders()
{
	shader = new SimpleShader();
}

void Display::InitModelViewProjectionMatrix()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	mat4 View = lookAt(
			vec3(0, 0, 10), // Camera is at (4,3,3), in World Space
			vec3(0, 0, 0), // and looks at the origin
			vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	mat4 Model = mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

void Display::OpenWindow()
{
	InitWindow();

	if (!glfwOpenWindow(600, 400, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		throw runtime_error("Failed in open window");
	}
	glfwSetWindowTitle("My Land");

	InitGLEW();
	InitShaders();
	InitModelViewProjectionMatrix();

}

void Display::Run()
{
	UpdateLoop();
}

void Display::UpdateLoop()
{
	do
	{
		Draw();
	}
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
			glfwGetWindowParam(GLFW_OPENED));
}

void Display::Draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	std::vector<GameObject*>::iterator itr;
	for(itr = gameObjectsArray->begin(); itr != gameObjectsArray->end(); ++itr)
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

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, object->vertexBuffer);
	assert(glIsBuffer(object->vertexBuffer) == GL_TRUE);

	// Get a handle for our buffers
	GLint vertexPosition_modelspaceID = glGetAttribLocation(shader->shaderID, "vertexPosition_modelspace");

	glVertexAttribPointer(
			GLuint(vertexPosition_modelspaceID),
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void *) 0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 object
	glDisableVertexAttribArray(0);
}