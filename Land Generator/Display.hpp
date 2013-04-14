#ifndef Display_H
#define Display_H

#include <glm/glm.hpp>
#include "SimpleShader.hpp"

class Triangle;

class Display
{
public:
	Display();
	void OpenWindow();
	Triangle *triangle;

protected:
	void Draw();

	SimpleShader *shader;
	glm::mat4 mvp;

private:
	// Initializations
	void InitGLFW();
	void InitGLEW();
	void InitWindow();
	void InitShaders();
	void InitModelViewProjectionMatrix();

	// Update
	void UpdateLoop();

};

#endif