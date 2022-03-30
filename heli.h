#pragma once

#include "wavefront.h"
#ifdef _WIN32
#include "Include/glew.h"
#include "Include/freeglut.h"
#elif __linux__
#include "GL/glew.h"
#include "GL/glut.h"
#elif __APPLE__
#include "Include/glew.h"
#include "Include/freeglut.h"
#endif


class heli
{
public:
	void calc();
	void draw();
	void animate();

	// TODO
	GLfloat pos[3] = {0.0f, 0.0f, 0.0f};

	GLfloat rotation = 0.0f;
	GLfloat angle = 0.0f;
	GLfloat enginePower = 0.0f;

	GLfloat rotationSpeed = 60.0f;	
	GLfloat angleSpeed = 120.0f;
	GLfloat engineAcc = 10.0f;
};

