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

class Sphere
{
public:
	Sphere();
	~Sphere();


	GLuint sphereBufferObject, sphereNormals, sphereColours;
	GLuint elementbuffer;
	GLuint drawmode;
	GLuint numlats;
	GLuint numlongs;
	GLuint numspherevertices;

	/* Function prototypes */
	/* Note that a better design would be to make a sphere class. I've suggested that as one of the
	extras to do in the lab for this week. */
	void makeUnitSphere(GLfloat *pVertices, GLuint numlats, GLuint numlongs);
	GLuint makeSphereVBO(GLuint numlats, GLuint numlongs);
	void drawSphere(GLuint drawmode);

};

