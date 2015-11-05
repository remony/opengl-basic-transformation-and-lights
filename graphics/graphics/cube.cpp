#include "cube.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* GLM core */
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>



Cube::Cube()
{
}

Cube::~Cube()
{
}


GLuint Cube::makeCubeVBO() {
	/* Define vertices for a cube in 12 triangles */
	
	
	
	GLfloat vertexPositions[] =
	{
		-0.25f, 0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, 0.25f,

		-0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, 0.25f,

		0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, -0.25f,
	};
	

	GLuint numvertices = sizeof(vertexPositions);


	/* Manually specified colours for our cube */
	float vertexColours[] = {
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,

		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,
		0.5f, 0.5f, 1.5f, 0.5f,


	};

	/* Manually specified normals for our cube */
	GLfloat normals[] =
	{
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,


	};


	/* Create the vertex buffer for the cube */
	glGenBuffers(1, &cubePositionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, cubePositionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the colours buffer for the cube */
	glGenBuffers(1, &cubeColourObject);
	glBindBuffer(GL_ARRAY_BUFFER, cubeColourObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours), vertexColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &cubeNormalsBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, cubeNormalsBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return numvertices;
}

void Cube::drawCube() {

	/* Bind cube vertices. Note that this is in attribute index 0 */
	glBindBuffer(GL_ARRAY_BUFFER, cubePositionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/* Bind cube colours. Note that this is in attribute index 1 */
	glBindBuffer(GL_ARRAY_BUFFER, cubeColourObject);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Bind cube normals. Note that this is in attribute index 2 */
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, cubePositionBufferObject);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	/* Draw our cube*/
	glDrawArrays(GL_TRIANGLES, 0, 300);

}


