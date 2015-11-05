/*
		Title: Gears of Clock

		Author: Stuart Douglas

		Note: Parts of this class contains code from Iain Martin examples from 2015



/*


/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>
#include "ClockPart.h"
#include "Light.h"
#include "plane.h"
#include "cube.h"

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

GLuint drawmode;
GLuint program[2];
GLuint vao;
Cube cube;
GLuint selectedProgram;

// Movement/Animation values
struct Movement {
	GLfloat angle_x; 
	GLfloat angle_y; 
	GLfloat angle_z;
	GLfloat angle_inc_x;
	GLfloat angle_inc_y;
	GLfloat angle_inc_z;
};

struct Model {
	GLfloat		pos_x;
	GLfloat		pos_y;
	GLfloat		pos_z;
	GLfloat		scale;
	GLfloat		velocity;
	GLfloat		angle_x;
	GLfloat		angle_y;
	GLfloat		angle_z;
	glm::vec3	colour;
};



Model gear1;
Model gear2;
Model gear3;
Model gear4;
Model gear5;
Model gear6;

int selectedGear;

Plane plane;
GLuint planeVertices;

// Create instance of movement
Movement movement; 

// Model positioning values
GLfloat x, y, z;
GLfloat scale;

ClockPart gear;
ClockPart gearType2;


Light lightSource1;
GLuint lightSource1Vertices;




GLuint tetra1vertices;
GLuint gearType2vertices;


// Camera properties
struct Camera {
	GLfloat pos_x;
	GLfloat pos_y;
	GLfloat pos_z;
	GLfloat angle_x;
	GLfloat angle_y;
	GLfloat angle_z;
	GLfloat aspect_ratio;
	GLfloat radius;
};

// Create instance of camera struct
Camera camera;

struct LightProperties {
	GLfloat pos_x;
	GLfloat pos_y;
	GLfloat pos_z;
};

LightProperties light;

/* Uniforms*/

GLuint modelID, viewID, projectionID;
GLuint lightposID;
GLuint normalmatrixID;
GLuint emitmodeID;

GLuint lightProperties;

GLuint emitmode;

// setDefaultValues intializing variables with there default values; this is used at start and whenever the user stats a reset 
void setDefaultValues() {

	// Default camera properties
	camera.pos_x = 0;
	camera.pos_y = 0;
	camera.pos_z = 3;
	camera.angle_x = 0;
	camera.angle_y = 0.3;
	camera.angle_z = 0;
	camera.radius = 0;
	camera.aspect_ratio = 1024.f / 768.f;
	
	

	// Default coords for positioning
	x = y = z = 0;

	// Default light properties
	light.pos_x = 0; light.pos_y = 0;
	light.pos_z = -0.25f;

	// Default movement/animation values
	movement.angle_x = movement.angle_y = movement.angle_z = 0;
	movement.angle_inc_x = movement.angle_inc_z = 0;
	movement.angle_inc_y = -1;
	scale = 1.f;
	emitmode = 0;


	// Default positions values for gear models

	gear1.pos_x = 0;
	gear1.pos_y = 0;
	gear1.pos_z = 0;
	gear1.scale = 0;
	gear1.velocity = 0;
	gear1.angle_x = 0;
	gear1.angle_y = 0;
	gear1.angle_z = 0;
	gear1.colour = glm::vec3(0.2, 0.2, 0.2);

	gear2.pos_x = 0;
	gear2.pos_y = 0;
	gear2.pos_z = 0;
	gear2.scale = 0;
	gear2.velocity = 0;
	gear2.angle_x = 0;
	gear2.angle_y = 0;
	gear2.angle_z = 0;
	gear2.colour = glm::vec3(0.4, 0.4, 0.4);

	gear3.pos_x = 0;
	gear3.pos_y = 0;
	gear3.pos_z = 0;
	gear3.scale = 0;
	gear3.velocity = 0;
	gear3.angle_x = 0;
	gear3.angle_y = 0;
	gear3.angle_z = 0;
	gear3.colour = glm::vec3(0.2, 0.2, 0.2);

	gear4.pos_x = 0;
	gear4.pos_y = 0;
	gear4.pos_z = 0;
	gear4.scale = 0;
	gear4.velocity = 0;
	gear4.angle_x = 0;
	gear4.angle_y = 0;
	gear4.angle_z = 0;
	gear4.colour = glm::vec3(0.2, 0.2, 0.2);

	gear5.pos_x = 0;
	gear5.pos_y = 0;
	gear5.pos_z = 0;
	gear5.scale = 0;
	gear5.velocity = 0;
	gear5.angle_x = 0;
	gear5.angle_y = 0;
	gear5.angle_z = 0;
	gear5.colour = glm::vec3(0.2, 0.2, 0.2);

	gear6.pos_x = 0;
	gear6.pos_y = 0;
	gear6.pos_z = 0;
	gear6.scale = 0;
	gear6.velocity = 0;
	gear6.angle_x = 0;
	gear6.angle_y = 0;
	gear6.angle_z = 0;
	gear6.colour = glm::vec3(0.2, 0.2, 0.2);
}

// printControls prints the user controls to the debug console.
void printControls() {

	
	std::cout << "               Controls" << std::endl;
	std::cout << "_______________________________________" << std::endl;
	std::cout << "|     Keys   |         Function       |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|				Camera					|" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|    Q, E    | Speed up/down gears    |" << std::endl;
	std::cout << "|      R     | Reset Speed/position   |" << std::endl;
	std::cout << "|  Up arrow  |      Look Up           |" << std::endl;
	std::cout << "| Down arrow |      Look Down         |" << std::endl;
	std::cout << "| Left arrow |      Look Left         |" << std::endl;
	std::cout << "| Right arrow|      Look Right        |" << std::endl;
	std::cout << "|    - / _   |       Zoom Out         |" << std::endl;
	std::cout << "|    = / +   |       Zoom In          |" << std::endl;
	std::cout << "|      A     |       Pan Left         |" << std::endl;
	std::cout << "|      D     |       Pan Right        |" << std::endl;
	std::cout << "|      S     |       Pan Down         |" << std::endl;
	std::cout << "|      W     |       Pan Up           |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|	   Control individual model      	|" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|      M     |  Toggle between models |" << std::endl;
	std::cout << "|      I     |     Move up            |" << std::endl;
	std::cout << "|      K     |     Move Down          |" << std::endl;
	std::cout << "|      J     |     Move Left          |" << std::endl;
	std::cout << "|      L     |     Move Right         |" << std::endl;
	std::cout << "|      P     |     Move Back          |" << std::endl;
	std::cout << "|      O     |     Move Forward       |" << std::endl;
	std::cout << "|      U     |     Scale Up           |" << std::endl;
	std::cout << "|      Y     |     Scale Down         |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|	   Light Soure Controls           	|" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|      5     |     Move Down          |" << std::endl;
	std::cout << "|      6     |     Move Up            |" << std::endl;
	std::cout << "|      7     |     Move Left          |" << std::endl;
	std::cout << "|      8     |     Move Right         |" << std::endl;
	std::cout << "|      9     |     Scale Forward      |" << std::endl;
	std::cout << "|      0     |     Scale Back         |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|	      DRAW MODE                  	|" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|      N     |   Switch draw mode     |" << std::endl;
	std::cout << "_______________________________________" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Tip: hold down keys to increment faster" << std::endl;
	std::cout << std::endl;
	std::cout << "Tip: Scroll up to see more controlls" << std::endl;
	std::cout << std::endl;
	std::cout << "Currently selected model Gear: " << selectedGear << std::endl;
	std::cout << std::endl;
	std::cout << "Currently selected Program: " << selectedGear << std::endl;
	std::cout << "> Program 1:  Point light with Fog" << std::endl;
	std::cout << "> Program 0:  Directional light with Fog" << std::endl;
	std::cout << "> Program 2:  Directional light" << std::endl;
	std::cout << std::endl;
}

void updateConsole() {
	system("cls");
	printControls();
	std::cout << "Drawmode: ";
	if (drawmode == 1) {
		std::cout << "Lines";
	}
	else if (drawmode == 2) {
		std::cout << "Points";
	} else if (drawmode == 0) {
		std::cout << "Filled";
	}
	std::cout << std::endl;
}

// Intitilization
void init(GLWrapper *glw) {
	
	setDefaultValues();
	selectedProgram = 1;
	
	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);


	
	// Create Tetra vertices
	tetra1vertices = gear.makeClockPartVBO(32, 32, gear1.colour);
	gearType2vertices = gearType2.makeClockPartVBO(32, 32, gear2.colour);

	// Create the plane
	plane.makePlaneVBO();
	cube.makeCubeVBO();

	try
	{
		//Load in the vertex and fragment shader
		program[0] = glw->LoadShader("shader.vert", "shader.frag");
		program[1] = glw->LoadShader("mist.vert", "mist.frag");
		program[2] = glw->LoadShader("shader.vert", "directionalLight.frag");
	}
	catch (std::exception &e) // If we capture an error; file load failure
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

	/* Define uniforms to send to vertex shader */
	for (int i = 0; i < (sizeof(program) / sizeof(*program)); i++) {
		modelID = glGetUniformLocation(program[i], "model");
		emitmodeID = glGetUniformLocation(program[i], "emitmode");
		lightProperties = glGetUniformLocation(program[i], "LightProperties");
		viewID = glGetUniformLocation(program[i], "view");
		projectionID = glGetUniformLocation(program[i], "projection");
		lightposID = glGetUniformLocation(program[i], "lightpos");
		normalmatrixID = glGetUniformLocation(program[i], "normalmatrix");
	}
	

}

// display loop
void display() {
	// Define the background colour;  note: black/white may hide points, best 0.2,0.2,0.2 for debugging
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

	// Clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);
	// Enable the Depth 
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);



	// Assign the current shader application
	glUseProgram(program[selectedProgram]);


	// Intialize the default model transformations as a fallback
	glm::mat4 model = glm::mat4(1.0f);
	

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(30.0f, camera.aspect_ratio, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(camera.angle_x, camera.angle_y, camera.pos_z), // Camera is at (0,0,4), in World Space
		glm::vec3(camera.pos_x,camera.pos_y, camera.angle_z), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//// Send our transformations to the currently bound shader,
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &Projection[0][0]);

	

	// Define the light position and transform by the view matrix

	/*
				Light
	*/
	// Define the position in space
	glm::vec4 lightpos = View * glm::vec4(light.pos_x, light.pos_y, light.pos_z, 1.0);
	// Define the normal matrix
	glm::mat3 normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));

	// Send the light MVP to the vertex shader
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &Projection[0][0]); 
	glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);	 // send the normal matrix
	glUniform4fv(lightposID, 1, glm::value_ptr(lightpos)); // send the light position to the vertex shader


		/*
				Gears of the Clock
		*/

		// Gear 1
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-x + 0.16 + gear1.pos_x, 0.14 + gear1.pos_y, 0.2 + gear1.pos_z)); // Position in space
		model = glm::scale(model, glm::vec3(scale / 5.f + gear1.scale, scale / 5.f + gear1.scale, scale / 5.f + gear1.scale)); // Scale of model
		model = glm::rotate(model, -movement.angle_x, glm::vec3(1, 0, 0)); // x axis rotation
		model = glm::rotate(model, gear1.angle_z, glm::vec3(0, 1, 0));
		model = glm::rotate(model, -(movement.angle_y * 0.7f + gear1.velocity), glm::vec3(0, 0, 1)); // z axis rotation
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Gear 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + -0.08 + gear2.pos_x, -0.142 + gear2.pos_y, 0.2 + gear2.pos_z));
		model = glm::scale(model, glm::vec3(scale / 5.f + gear2.scale, scale / 5.f + gear2.scale, scale / 5.f + gear2.scale));
		model = glm::rotate(model, -movement.angle_x, glm::vec3(1, 0, 0)); // x axis rotation
		model = glm::rotate(model, gear1.angle_z, glm::vec3(0, 1, 0));
		model = glm::rotate(model, (movement.angle_y * 0.7f + gear2.velocity), glm::vec3(0, 0, 1)); // z axis rotation
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);


		// Gear 3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + 0.41 + gear3.pos_x, 0.23 + gear3.pos_y, 0 + gear3.pos_z));
		model = glm::scale(model, glm::vec3(scale / 4.f + gear3.scale, scale / 4.f + gear3.scale, scale / 4.f + gear3.scale));
		model = glm::rotate(model, gear3.angle_z, glm::vec3(1, 0, 0)); // x axis rotation
		model = glm::rotate(model, -90.f, glm::vec3(0, 1, 0)); // y axis rotation
		model = glm::rotate(model, -(movement.angle_y * 0.7f + gear3.velocity), glm::vec3(0, 0, 1)); // z axis rotation
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Gear 4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + 0.41 + gear4.pos_x, -0.12 + gear4.pos_y, -0.285 + gear4.pos_z));
		model = glm::scale(model, glm::vec3(scale / 4.f + gear4.scale, scale / 4.f + gear4.scale, scale / 4.f + gear4.scale));
		model = glm::rotate(model, gear4.angle_z, glm::vec3(1, 0, 0));
		model = glm::rotate(model, -90.f, glm::vec3(0, 1, 0));
		model = glm::rotate(model, (movement.angle_y * 0.7f + gear4.velocity), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Gear 5
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + -0.4 + gear5.pos_x, -0.33 + gear5.pos_y, 0.2 + gear5.pos_z));
		model = glm::scale(model, glm::vec3(scale / 5.f + gear5.scale, scale / 5.f + gear5.scale, scale / 5.f + gear5.scale));
		model = glm::rotate(model, -movement.angle_x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, gear5.angle_z, glm::vec3(0, 1, 0));
		model = glm::rotate(model, -(movement.angle_y * 0.7f + gear5.velocity), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Gear 6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + -0.56 + gear6.pos_x, -0.02 + gear6.pos_y, 0.2 + gear6.pos_z));
		model = glm::scale(model, glm::vec3(scale / 5.f + gear6.scale, scale / 5.f + gear6.scale, scale / 5.f + gear6.scale));
		model = glm::rotate(model, -movement.angle_x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, gear6.angle_z, glm::vec3(0, 1, 0));
		model = glm::rotate(model, (movement.angle_y * 0.7f + gear6.velocity), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gearType2.drawClockPart(drawmode);



		/*
				Background Gears
		*/

		// Background Gear 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + -0.4, -0.33, -10.2));
		model = glm::scale(model, glm::vec3(scale * 1.1f, scale * 1.1f, scale * 1.f));
		model = glm::rotate(model, -(movement.angle_y * 0.1f), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Background Gear 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + -2.1, -1.3, -10.2));
		model = glm::scale(model, glm::vec3(scale * 1.1f, scale * 1.1f, scale * 1.f));
		model = glm::rotate(model, (movement.angle_y * 0.1f), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Background Gear 3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + 1.1, -1.5, -10.2));
		model = glm::scale(model, glm::vec3(scale * 1.1f, scale * 1.1f, scale * 1.f));
		model = glm::rotate(model, (movement.angle_y * 0.1f), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Background Gear 4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-x + 2.8, -0.53, -10.2));
		model = glm::scale(model, glm::vec3(scale * 1.1f, scale * 1.1f, scale * 1.f));
		model = glm::rotate(model, -(movement.angle_y * 0.1f), glm::vec3(0, 0, 1));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		gear.drawClockPart(drawmode);

		// Ground plane
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y-5, z-40));
		model = glm::scale(model, glm::vec3(scale * 600.f, scale * 6.f, scale * 600.f));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		plane.drawPlane();

		// Cube 1
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x - 1.3, y + 0.1, z));
		model = glm::scale(model, glm::vec3(scale * 0.5, scale * 0.5, scale * 0.5));
		model = glm::rotate(model, movement.angle_y, glm::vec3(0, 0, 1));
		model = glm::rotate(model, movement.angle_y, glm::vec3(1, 0, 0));

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		cube.drawCube();

		// Cube 2

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x + 1.3f, y + 0.1, z));
		model = glm::scale(model, glm::vec3(scale * 0.5, scale * 0.5, scale * 0.5));
		model = glm::rotate(model, movement.angle_y, glm::vec3(0, 0, 1));
		model = glm::rotate(model, movement.angle_y, glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

		normalmatrix = glm::transpose(glm::inverse(glm::mat3(View * model)));
		glUniformMatrix3fv(normalmatrixID, 1, GL_FALSE, &normalmatrix[0][0]);
		cube.drawCube();

	

		
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	// modify movement/animation values
	movement.angle_x += movement.angle_inc_x;
	movement.angle_y += movement.angle_inc_y;
	movement.angle_z += movement.angle_inc_z;
}


// When error occurs
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

/*
Name: InputHandler
Description: This method handles all of repeated input handling methods. To encourage reusability
*/
static void inputHandler(int key) {
	// Movement of objects

	// Speed up
	if (key == GLFW_KEY_E) movement.angle_inc_y -= 0.5f;
	// speed down
	if (key == GLFW_KEY_Q) movement.angle_inc_y += 0.5f;

	/* 
		Light movement
	*/

	if (key == GLFW_KEY_8) {
		light.pos_x += 0.1f;
	}

	if (key == GLFW_KEY_7) {
		light.pos_x -= 0.1f;
	}

	if (key == GLFW_KEY_6) {
		light.pos_y += 0.1f;
	}

	if (key == GLFW_KEY_5) {
		light.pos_y -= 0.1f;
	}

	if (key == GLFW_KEY_9) {
		light.pos_z -= 0.1f;
	}

	if (key == GLFW_KEY_0) {
		light.pos_z += 0.1f;
	}

	/*
			Camera Movement

			We are also moving the light with the camera,
			however this can be moved to another key bind
			a future situation.
			*/

	// Zoom: This will move the camera closer or further away
	if (key == GLFW_KEY_EQUAL) {
		// limit the zoom
		if (camera.pos_z > 0.5) camera.pos_z -= 0.1f; // Zoom In
	}
	if (key == GLFW_KEY_MINUS) {
		// limit zoom out
		if (camera.pos_z < 8) camera.pos_z += 0.1f; // Zoom Out
	}
	
	// Move camera right
	if (key == GLFW_KEY_RIGHT) {
		//camera.pos_x += 0.1f;
		camera.pos_x += 0.1f;
		
	}
	// Move camera left
	if (key == GLFW_KEY_LEFT) {
		camera.pos_x -= 0.1f;
		
	}

	// Move camera up
	if (key == GLFW_KEY_UP) {
		camera.pos_y += 0.1f;
		
	}
	// Move camera down
	if (key == GLFW_KEY_DOWN) {
		camera.pos_y -= 0.1f;
		
	}

	if (key == GLFW_KEY_W) {
		camera.angle_y -= 0.1f;
	}
	if (key == GLFW_KEY_S) {
		camera.angle_y += 0.1f;
	}

	if (key == GLFW_KEY_A) {
		camera.angle_x -= 0.1f;
	}
	
	if (key == GLFW_KEY_D) {
		
		camera.angle_x += 0.1;
		
	}

	// Reset speed and camera position
	if (key == GLFW_KEY_R) {
		setDefaultValues();
	}


	if (key == GLFW_KEY_M) {
		selectedGear++;
		if (selectedGear > 5) selectedGear = 0;
	}

	// Indivedual model controls
	if (key == GLFW_KEY_I) { // move y
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_y += 0.01f;
			break;
		case 1: // gear 2
			gear2.pos_y += 0.01f;
			break;
		case 2: // gear 3
			gear3.pos_y += 0.01f;
			break;
		case 3: // gear 4
			gear4.pos_y += 0.01f;
			break;
		case 4: // gear 5
			gear5.pos_y += 0.01f;
			break;
		}
	}
	if (key == GLFW_KEY_K) { // move y
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_y -= 0.01;
			break;
		case 1: // gear 2
			gear2.pos_y -= 0.01;
			break;
		case 2: // gear 3
			gear3.pos_y -= 0.01;
			break;
		case 3: // gear 4
			gear4.pos_y -= 0.01;
			break;
		case 4: // gear 5
			gear5.pos_y += 0.01;
			break;
		}
	}
	if (key == GLFW_KEY_L) { // move x
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_x += 0.01;
			break;
		case 1: // gear 2
			gear2.pos_x += 0.01;
			break;
		case 2: // gear 3
			gear3.pos_x += 0.01;
			break;
		case 3: // gear 4
			gear4.pos_x += 0.01;
			break;
		case 4: // gear 5
			gear5.pos_x += 0.01;
			break;
		}
	}
	if (key == GLFW_KEY_J) { // move x
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_x -= 0.01;
			break;
		case 1: // gear 2
			gear2.pos_x -= 0.01;
			break;
		case 2: // gear 3
			gear3.pos_x -= 0.01;
			break;
		case 3: // gear 4
			gear4.pos_x -= 0.01;
			break;
		case 4: // gear 5
			gear5.pos_x -= 0.01;
			break;
		}
	}
	if (key == GLFW_KEY_O) { // move z
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_z += 0.01;
			break;
		case 1: // gear 2
			gear2.pos_z += 0.01;
			break;
		case 2: // gear 3
			gear3.pos_z += 0.01;
			break;
		case 3: // gear 4
			gear4.pos_z += 0.01;
			break;
		case 4: // gear 5
			gear5.pos_z += 0.01;
			break;
		}
	}
	if (key == GLFW_KEY_P) { // move z
		switch (selectedGear){
		case 0: // gear 1
			gear1.pos_z -= 0.01;
			break;
		case 1: // gear 2
			gear2.pos_z -= 0.01;
			break;
		case 2: // gear 3
			gear3.pos_z -= 0.01;
			break;
		case 3: // gear 4
			gear4.pos_z -= 0.01;
			break;
		case 4: // gear 5
			gear5.pos_z -= 0.01;
			break;
		}
	}

	if (key == GLFW_KEY_U) { // scale up
		switch (selectedGear){
		case 0: // gear 1
			gear1.scale += 0.01;
			break;
		case 1: // gear 2
			gear2.scale += 0.01;
			break;
		case 2: // gear 3
			gear3.scale += 0.01;
			break;
		case 3: // gear 4
			gear4.scale += 0.01;
			break;
		case 4: // gear 5
			gear5.scale += 0.01;
			break;
		}
	}
	if (key == GLFW_KEY_Y) { // move z
		switch (selectedGear){
		case 0: // gear 1
			gear1.scale -= 0.01;
			break;
		case 1: // gear 2
			gear2.scale -= 0.01;
			break;
		case 2: // gear 3
			gear3.scale -= 0.01;
			break;
		case 3: // gear 4
			gear4.scale -= 0.01;
			break;
		case 4: // gear 5
			gear5.scale -= 0.01;
			break;
		}
	}

	if (key == GLFW_KEY_Z) {
		switch (selectedGear){
			case 0: // gear 1
				gear1.angle_z -= 1;
				break;
			case 1: // gear 2
				gear2.angle_z -= 1;
				break;
			case 2: // gear 3
				gear3.angle_z -= 1;
				break;
			case 3: // gear 4
				gear4.angle_z -= 1;
				break;
			case 4: // gear 5
				gear5.angle_z -= 1;
				break;
		}
	}
	if (key == GLFW_KEY_X) {
		switch (selectedGear){
		case 0: // gear 1
			gear1.angle_z += 1;
			break;
		case 1: // gear 2
			gear2.angle_z += 1;
			break;
		case 2: // gear 3
			gear3.angle_z += 1;
			break;
		case 3: // gear 4
			gear4.angle_z += 1;
			break;
		case 4: // gear 5
			gear5.angle_z += 1;
			break;
		}
	}

	if (key == GLFW_KEY_1) {
		selectedProgram++;
		if (selectedProgram > (sizeof(program) / sizeof(*program))) selectedProgram = 0;
	}

}

// key_callback is called when a keyboard event is captured
static void key_callback(GLFWwindow* window, int key, int s, int action, int mods)
{
	// If the escape key is pressed, clost the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// If the callback has action pressed
	if (action == GLFW_PRESS) {

		updateConsole();
		inputHandler(key);
		/* Cycle between drawing vertices, mesh and filled polygons */
	}
	// If the callback has action repeated; if the user holds the button
	else if (action == GLFW_REPEAT) {
		inputHandler(key);
	}

	// Toggle between draw mode states;   0 = filled;   1 = lines;  2 = Points;
	if (key == 'N' && action != GLFW_PRESS)
	{
		drawmode++;
		if (drawmode > 2) drawmode = 0;
	}
}

// reshape changes the view to fix the window
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	camera.aspect_ratio = float(w) / float(h);
}


// printControls prints the user controls to the debug console.




int main(int argc, char* argv[]) {
	
	GLWrapper *glw = new GLWrapper(
		1024,				// Window width
		768,				// Window height 
		"Gears of Clock (View console for instructions and state information)"	// Window title
	);
	glw->setErrorCallback(error_callback);

	// If unable to load functions close the application
	if (!ogl_LoadFunctions())
	{
		fprintf(stderr, "ogl_LoadFunctions() failed. Exiting\n");
		return 0;
	}

	// Print controls and info to the console
	updateConsole();

	// set the renderer
	glw->setRenderer(display);
	glw->setKeyCallback(key_callback); // Set callback for keyboard shortcuts
	glw->setReshapeCallback(reshape); // Set callback for handling window resizing
	
	//Initialize the glw wrapper
	init(glw);

	//Start the event loop
	glw->eventLoop();

	delete(glw); // detele the windows instance

	return 0;
}


