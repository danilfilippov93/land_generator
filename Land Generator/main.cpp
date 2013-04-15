//
//  main.cpp
//  Land Generator
//
//  Created by ASPCartman on 14.04.13.
//  Copyright (c) 2013 ASPCartman. All rights reserved.
//

#include "Display.hpp"
#include  "PerlinNoise.h"

#define LIMIT 100

int main(int argc, const char *argv[])
{
	Display *display = new Display();
	display->OpenWindow();

	PerlinNoise noise;

	for (int x = 0; x < LIMIT; ++x)
		for (int y = 0; y < LIMIT; ++y)
		{
			float z = float(noise.Noise(double(x), double(y)));

			GameObject *object = new GameObject();
			object->position = glm::vec3(2*float(x),2*float(y),z);

			display->AddGameObjects(object);
		}

	display->Run();

	return 0;
}

