//
//  main.cpp
//  Land Generator
//
//  Created by ASPCartman on 14.04.13.
//  Copyright (c) 2013 ASPCartman. All rights reserved.
//

#include "Display.hpp"

int main(int argc, const char *argv[])
{
	Display *display = new Display();
	display->OpenWindow();

	GameObject *object1 = new GameObject();
	object1->position = glm::vec3(2, 0, 0);
	display->AddGameObjects(object1);

	GameObject *object = new GameObject();
	display->AddGameObjects(object);

	display->Run();

	return 0;
}

