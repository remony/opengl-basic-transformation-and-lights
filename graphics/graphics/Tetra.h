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

class Tetra
{
public:
	Tetra();
	~Tetra();


	GLuint sphereBufferObject, sphereNormals, sphereColours;
	GLuint elementbuffer;
	GLuint drawmode;
	GLuint numlats;
	GLuint numlongs;
	GLuint tetravertices;

	void makeUnitTetra(GLfloat *pVertices, GLuint numlats);
	GLuint makeTetraVBO(GLuint numlats, GLuint numlongs, glm::vec3 colour);
	void drawTetra(GLuint drawmode);

};

