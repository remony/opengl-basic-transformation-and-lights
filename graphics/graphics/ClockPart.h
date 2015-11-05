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
#include <stdlib.h> 
#include <time.h>

class ClockPart
{
public:
	ClockPart();
	~ClockPart();


	GLuint partBufferObject, partNormals, partColours;
	GLuint elementbuffer;
	GLuint drawmode;
	GLuint numlats;
	GLuint numlongs;
	GLuint partvertices;

	void makeUnitClockPart(GLfloat *pVertices, GLuint numlats);
	GLuint makeClockPartVBO(GLuint numlats, GLuint numlongs, glm::vec3 colour);
	void drawClockPart(GLuint drawmode);

};

