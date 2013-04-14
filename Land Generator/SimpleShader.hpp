//
// Created by aspcartman on 14.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __SimpleShader_H_
#define __SimpleShader_H_

#include "Shader.hpp"


class SimpleShader : public Shader
{
	public:
	SimpleShader();

	GLint modelViewProjectionUniformID;
	GLint vertexPostitionModelspaceAttributeID;
};


#endif //__SimpleShader_H_
