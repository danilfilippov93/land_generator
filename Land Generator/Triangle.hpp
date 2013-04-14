#ifndef Triangle_H
#define Triangle_H

#include "GL.hpp"
class Triangle {
    public:
    Triangle();
	void InitTriangle();

    GLuint vertexBuffer;

	glm::vec3 position;
	glm::vec3 rotation;
};

#endif