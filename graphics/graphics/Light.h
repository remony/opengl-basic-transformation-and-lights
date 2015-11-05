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




class Light
{
public:
	Light();
	~Light();

	GLuint lightBufferObject, lightNormals, lightColours;
	GLuint elementbuffer;
	GLuint drawmode;
	GLuint numlats;
	GLuint numlongs;
	GLuint numlightvertices;

	void makeUnitLight(GLfloat *pVertices, GLuint numlats, GLuint numlongs);
	GLuint makeLightVBO(GLuint numlats, GLuint numlongs);
	void drawLight(GLuint drawmode);



};

