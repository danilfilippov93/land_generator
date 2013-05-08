#ifndef Triangle_H
#define Triangle_H

#include "GL.hpp"

class Cube
{
public:
	Cube();
	void InitTriangle();

	GLuint vertexBuffer;

	glm::vec3 position;
	glm::vec4 color;
};

#endif