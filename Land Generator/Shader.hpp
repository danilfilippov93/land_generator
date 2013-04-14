//
// Created by aspcartman on 14.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Shader_H_
#define __Shader_H_

#include "GL.hpp"

class Shader
{
public:
	Shader(char const *vertex, char const *fragment);
	GLint shaderID;
};

#endif //__Shader_H_
