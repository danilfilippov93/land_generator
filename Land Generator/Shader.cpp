//
// Created by aspcartman on 14.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <stdexcept>
#include "Shader.hpp"
#include "shaderUtils.hpp"

Shader::Shader(char const *vertex, char const *fragment)
{
	shaderID = LoadShaders(vertex, fragment);
	if (shaderID == 0)
		throw std::runtime_error("Could Not Load Shader");
}