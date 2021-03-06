#ifndef Display_H
#define Display_H

#include <glm/glm.hpp>
#include "SimpleShader.hpp"
#include <vector>
#include "Cube.hpp"

class Display
{
public:
	Display();
	void OpenWindow();
	void AddGameObject(Cube *gameObject);
	void Run();

protected:
	void Draw();
	static void GLFWCALL ResizeWindow(int x, int y);
	SimpleShader *shader;
	glm::mat4 mvp;
	std::vector<Cube *> *gameObjectsArray;

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
	void DrawObject(Cube *object);


};

#endif