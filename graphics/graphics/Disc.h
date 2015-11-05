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

class Disc
{
public:
	Disc();
	~Disc();

	GLuint discPositionBufferObject, discColourObject, discNormalsBufferObject;

	void drawDisc();
	GLuint makeDiscVBO();
};

