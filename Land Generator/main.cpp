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
			glm::vec4 color;
			if (z <= -0.5)
			{
				z = -0.5;
				color = glm::vec4(0, 0, 1, 1);
				color *= glm::vec4(2);
			} else if (z < -0.4)
			{
				color = glm::vec4(0.96, 0.83, 0.16, 1);
			} else if (z < 0.7)
			{
				color = glm::vec4(0.74, 0.84, 0.05, 1);
			} else
			{
				color = glm::vec4(1, 1, 1, 1);
			}
			float colorMult = (z + 1) / 2.f;
			color *= glm::vec4(colorMult);

			Cube *object = new Cube();
			object->position = glm::vec3(2 * float(x), 2 * float(y), 10 * (z + 1));
			object->color = color;

			display->AddGameObject(object);
		}


	display->Run();

	return 0;
}

