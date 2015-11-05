#pragma once

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* GLM core */
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Cube
{
public:
	Cube();
	~Cube();

	GLuint cubePositionBufferObject, cubeColourObject, cubeNormalsBufferObject;

	void createCube();
	void drawCube();
	GLuint makeCubeVBO();

};

