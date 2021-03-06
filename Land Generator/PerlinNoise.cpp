//
// Created by aspcartman on 15.04.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <math.h>
#include "PerlinNoise.hpp"
#include <stdlib.h>

double Noise(int x, int y)
{
	static int randomInteger = 0;
	if (randomInteger == 0)
	{
		randomInteger = random() % 50 + 10;
	}

	int n = x + y * randomInteger;
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double SmoothNoise(int x, int y)
{
	double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16.f;
	double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8.f;
	double center = Noise(x, y) / 4.f;
	return corners + sides + center;
}

double Cosine_Interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1.f - cos(ft)) * .5;
	return a * (1.f - f) + b * f;
}

double InterpolatedNoise(double x, double y)
{
	int integer_X = int(x);
	double fractional_X = x - integer_X;

	int integer_Y = int(y);
	double fractional_Y = y - integer_Y;

	double v1 = SmoothNoise(integer_X, integer_Y);
	double v2 = SmoothNoise(integer_X + 1, integer_Y);
	double v3 = SmoothNoise(integer_X, integer_Y + 1);
	double v4 = SmoothNoise(integer_X + 1, integer_Y + 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);

	return Cosine_Interpolate(i1, i2, fractional_Y);
}


#define NUMBER_OF_OCTAVES 2

double PerlinNoise_2D(double x, double y)
{
	double total = 0;

	for (int i = 0; i < NUMBER_OF_OCTAVES; ++i)
	{
		int frequency = 2 * i;
		double amplitude = 3.141592654;
		total += InterpolatedNoise(x * frequency, y * frequency) * amplitude;
	}

	return total;
}

double PerlinNoise::Noise(double x, double y)
{
	return PerlinNoise_2D(x, y);
}
