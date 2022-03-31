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

	GLfloat pos[3] = {0.0f, 0.0f, 0.0f};

	GLfloat rotation = 0.0f;
	GLfloat angle = 0.0f;
	GLfloat power = 0.0f;

	GLfloat rotation_acc = 15000.0f;	
	GLfloat tilt_acc = 6000.0f;
	GLfloat rotor_acc = 5.0f;
};

