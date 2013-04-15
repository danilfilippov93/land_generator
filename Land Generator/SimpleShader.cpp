//
// Created by aspcartman on 14.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "SimpleShader.hpp"

SimpleShader::SimpleShader() : Shader("shader.vertexshader", "shader.fragmentshader")
{
	// Get a handle for our "MVP" uniform
	modelViewProjectionUniformID = glGetUniformLocation(shaderID, "MVP");
	// Get a handle for our buffers
	vertexPostitionModelspaceAttributeID = glGetAttribLocation(shaderID, "vertexPosition_modelspace");

	objectColorUniformID = glGetUniformLocation(shaderID, "oColor");
}