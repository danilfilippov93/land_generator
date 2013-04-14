#ifndef Display_H
#define Display_H

#include <glm/glm.hpp>
#include "SimpleShader.hpp"
#include <vector>
#include "GameObject.hpp"

class Display
{
public:
	Display();
	void OpenWindow();
	void AddGameObjects(GameObject *gameObject);
	void Run();

protected:
	void Draw();

	SimpleShader *shader;
	glm::mat4 mvp;
	std::vector<GameObject*> *gameObjectsArray;

private:
	// Initializations
	void InitGLFW();
	void InitGLEW();
	void InitWindow();
	void InitShaders();
	void InitModelViewProjectionMatrix();
	void InitGameObjectsArray();

	// Update
	void UpdateLoop();
	void DrawObject(GameObject *object);


};

#endif