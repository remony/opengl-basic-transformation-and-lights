#include "inputHandler.h"


inputHandler::inputHandler()
{
}


inputHandler::~inputHandler()
{
}

/*
Scaling
Methods handling scaling
*/

float scaleUp(float scale, float amount) {
	return scale += amount;
}

float scaleDown(float scale, float amount) {
	return scale -= amount;
}

/*
Rotation
Methods handling rotation
*/

float rotateLeft(float rotate, float amount) {
	return rotate += amount;
}

float rotateRight(float rotate, float amount) {
	return rotate -= amount;
}

float rotateUp(float rotate, float amount) {
	return rotate += amount;
}

float rotateDown(float rotate, float amount) {
	return rotate -= amount;
}


