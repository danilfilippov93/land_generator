//
// Created by aspcartman on 14.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Shader.hpp"
#include "shaderUtils.hpp"
#include <iostream>

#ifndef __APPLE__
#include <stdexcept>
#endif
using namespace std;

Shader::Shader(char const *vertex, char const *fragment)
{
	shaderID = LoadShaders(vertex, fragment);
	if (shaderID == 0)
		throw runtime_error("Could Not Load Shader");
}