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
	bool isInsideHelipad();

	void calc();
	void draw();
	void animate();
	
	GLfloat pos[3] = {0.0f, 0.0f, 0.0f};

	GLfloat rotation = 0.0f;
	GLfloat rotation_acc = 0.85f;	

	GLfloat angle = 0.0f;
	GLfloat tilt_acc = 0.5f;
	GLfloat max_angle = 30.0f;
	GLfloat tilt_tthreshold = 1;

	GLfloat power = 0.0f;
	GLfloat rotor_acc = 0.002f;
	GLfloat max_power = 1;
	
	GLfloat helipad[4] = {
	27, 62,
	37, 72
	};

	GLfloat helipad_h = 19.6;

};

