#pragma once

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
	void animate(GLfloat x, GLfloat y, GLfloat z);
	
	// TODO
	GLfloat pos[3] = {0.0f, 0.0f, 0.0f};

	GLfloat rotation = 0.0f;
	GLfloat rotationSpeed = 0.5f;

	GLfloat angle = 0.0f;
	GLfloat angleSpeed = 0.2f;
};

