#include "Tetra.h"

/*

		Gears.h

		Author: Stuart Douglas

		Note: this class following the scheme of Sphere.cpp by Iain Martin

*/

Tetra::Tetra()
{
}


Tetra::~Tetra()
{
}

// Draw the Gear based on defined vertices and index buffesr
void Tetra::drawTetra(GLuint drawmode)
{

	// Draw the vertices
	glBindBuffer(GL_ARRAY_BUFFER, sphereBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Bind the Gear normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, sphereNormals);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Bind the colours
	glBindBuffer(GL_ARRAY_BUFFER, sphereColours);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Enable this line to show model in wireframe
	if (drawmode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (drawmode == 2)
	{
		glPointSize(3.f);
		glDrawArrays(GL_POINTS, 0, tetravertices);
	}
	else
	{
		/* Bind the indexed vertex buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		/* Draw the north pole regions as a triangle  */
		glDrawElements(GL_TRIANGLE_FAN, numlongs + 2, GL_UNSIGNED_INT, (GLvoid*)(0));

		/* Calculate offsets into the indexed array. Note that we multiply offsets by 4
		because it is a memory offset the indices are type GLuint which is 4-bytes */
		GLuint lat_offset_jump = (numlongs * 2) + 2;
		GLuint lat_offset_start = numlongs + 2;
		GLuint lat_offset_current = lat_offset_start * 4;

		/* Draw the triangle strips of latitudes */
		for (int i = 0; i < numlats - 2; i++)
		{
			glDrawElements(GL_TRIANGLE_STRIP, numlongs * 2 + 2, GL_UNSIGNED_INT, (GLvoid*)(lat_offset_current));
			lat_offset_current += (lat_offset_jump * 4);
		}
		/* Draw the south pole as a triangle fan */
		glDrawElements(GL_TRIANGLE_FAN, numlongs + 2, GL_UNSIGNED_INT, (GLvoid*)(lat_offset_current));
	}
}

GLuint Tetra::makeTetraVBO(GLuint numlat, GLuint numlong, glm::vec3 colour)
{
	GLuint i, j;

	numlats = numlat * 3;
	numlongs = numlong * 3;

	GLuint numvertices = 2 + ((numlats - 1) * numlongs);
	GLfloat* pVertices = new GLfloat[numvertices * 3];
	GLfloat* pColours = new GLfloat[numvertices * 4];
	GLfloat* pNormals = new GLfloat[numvertices * 4];
	makeUnitTetra(pVertices, numlats);



	// Calculate the colours and normals 
	for (i = 0; i < numvertices; i++)
	{
		pColours[i * 4] = colour.x;
		pColours[i * 4 + 1] = colour.y;
		pColours[i * 4 + 2] = colour.z;
		pColours[i * 4 + 3] = 1.f;

		pNormals[i * 4] = 0;
		pNormals[i * 4 + 1] = 0;
		pNormals[i * 4 + 2] = 0.01;
		pNormals[i * 4 + 3] = 1;
	}


	/* Generate the vertex buffer object */
	glGenBuffers(1, &sphereBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, sphereBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 3, pVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Store the normals in a buffer object */
	glGenBuffers(1, &sphereNormals);
	glBindBuffer(GL_ARRAY_BUFFER, sphereNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 3, pNormals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Store the colours in a buffer object */
	glGenBuffers(1, &sphereColours);
	glBindBuffer(GL_ARRAY_BUFFER, sphereColours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 4, pColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Calculate the number of indices in our index array and allocate memory for it */
	GLuint numindices = ((numlongs * 2) + 2) * (numlats - 1) + ((numlongs + 2) * 2);
	GLuint* pindices = new GLuint[numindices];

	// fill "indices" to define triangle strips
	GLuint index = 0;		// Current index

	// Define indices for the first triangle fan for one pole
	for (i = 0; i < (numlats * 3) + 1; i++)
	{
		pindices[index++] = i;
	}
	pindices[index++] = 1;	// Join last triangle in the triangle fan

	GLuint start = 1;		// Start index for each latitude row
	
	pindices[index] = (numvertices * 3)- 2;	// Tie up last triangle in fan

	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numindices * sizeof(GLuint), pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete pindices;
	delete pColours;
	delete pVertices;
	delete pNormals;
	tetravertices = numvertices;
	return numvertices;
}


/* Define the vertex positions for a sphere. The array of vertices must have previosuly
been created.
*/

void Tetra::makeUnitTetra(GLfloat *pVertices, GLuint numlats)
{

	GLfloat rad = 3.141592f / 90.f;
	GLuint vnum = 0;
	GLfloat x, y, z, radian;

	//Define north pole
	pVertices[0] = 0; pVertices[1] = 0; pVertices[2] = 0;

	vnum++;

	GLfloat latstep = 360.f / numlats;

	bool tooth = false;
	int count = 0;

	int topcount = 0;
	int leftcount = 0;
	int rightcount = 0;
	int bottomcount = 0;
	int missingcount = 0;

	for (GLfloat lat = 360.f - latstep; lat > -360.f; lat -= latstep)
	{
		radian = lat * rad;
		x = cos(radian);
		y = sin(radian);
		if (tooth) {
			if (count <= 3) {
				y = sin(radian + -2);
				x = cos(radian + -2);
				count++;
			}
			else {
				count = 0;

				tooth = false;
			}
			
		}
		else {
			tooth = true;
		}
		z = 0;

		// Define the vertex
		pVertices[vnum * 3] = x; pVertices[vnum * 3 + 1] = y; pVertices[vnum * 3 + 2] = z;
		vnum++;
		pVertices[vnum * 3] = x; pVertices[vnum * 3 + 1] = y; pVertices[vnum * 3 + 2] = 0.5f;
		vnum++;
	}
}


