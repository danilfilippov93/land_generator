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
	static void GLFWCALL ResizeWindow(int x,int y);
	SimpleShader *shader;
	glm::mat4 mvp;
	std::vector<GameObject *> *gameObjectsArray;

private:
	// Initializations
	void InitGLFW();
	void InitGLEW();
	void InitWindow();
	void InitShaders();
	void InitGameObjectsArray();

	// Update
	void UpdateLoop();
	void UpdateModelViewMatrix();
	void DrawObject(GameObject *object);


};

#endif