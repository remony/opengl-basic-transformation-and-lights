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

class Plane
{
public:
	Plane();
	~Plane();

	GLuint planePositionBufferObject, planeColourObject, planeNormalsBufferObject;

	void drawPlane();
	GLuint makePlaneVBO();
};

