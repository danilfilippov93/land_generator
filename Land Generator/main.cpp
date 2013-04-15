//
//  main.cpp
//  Land Generator
//
//  Created by ASPCartman on 14.04.13.
//  Copyright (c) 2013 ASPCartman. All rights reserved.
//

#include "Display.hpp"
#include "PerlinNoise.hpp"

#define LIMIT 100

int main(int argc, const char *argv[])
{
	Display *display = new Display();
	display->OpenWindow();

	PerlinNoise noise;

	for (int x = 0; x < LIMIT; ++x)
		for (int y = 0; y < LIMIT; ++y)
		{
			float z = float(noise.Noise(double(x) / 10.f, double(y) / 10.f));

			GameObject *object = new GameObject();
			object->position = glm::vec3(2 * float(x), 2 * float(y), 10 * z);

			display->AddGameObjects(object);
		}

	display->Run();

	return 0;
}

