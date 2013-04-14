#ifndef Triangle_H
#define Triangle_H

#include "GL.hpp"

class GameObject
{
public:
	GameObject();
	void InitTriangle();

	GLuint vertexBuffer;

	glm::vec3 position;
};

#endif