#include "heli.h"

#include "geometry.h"
#include "light.h"
#include "input.h"
#include <math.h>
#include <iostream>

void kufe()
{
	// Hauptstange
	glPushMatrix();
	glScalef(3, 0.1, 0.1);
	myCube();
	glPopMatrix();

	// Schr�ge vorn und hinten
	glPushMatrix();
	glTranslatef(1.5, 0, 0);
	glRotatef(225, 0, 0, 1);
	glTranslatef(-0.15, -0.1, 0);
	glScalef(0.3, 0.1, 0.1);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 0, 0);
	glRotatef(315, 0, 0, 1);
	glTranslatef(-0.15, 0, 0);
	glScalef(0.3, 0.1, 0.1);
	myCube();
	glPopMatrix();

	// Verbindung zum Hauptteil des Hubschraubers
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glRotatef(-45, 1, 0, 0);
	glScalef(0.1, 0.5, 0.1);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.65, 0, 0);
	glRotatef(-45, 1, 0, 0);
	glScalef(0.1, 0.5, 0.1);
	myCube();
	glPopMatrix();
}

void kufen()
{
	setColor(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslatef(0, 0, 0.7);
	kufe();
	glTranslatef(0, 0, -1.4);
	glRotatef(180, 0, 1, 0);
	kufe();
	glPopMatrix();
}

void nase()
{
	setColor(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(2, 0.75, 0);
	glScalef(0.4, 0.3, 0.4);
	mySphere();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.1, 0.55, 0);
	glRotatef(-10, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(0.2, 0.2, 0.2);
	myCylinder();
	glPopMatrix();

	setColor(0.7, 0.7, 0.3);
	glPushMatrix();
	glTranslatef(2.2, 0.75, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.3, 0.25, 0.3);
	myCone(1, 2, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6, 0.75, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.25, 0.3);
	myPartialDisk(0, 2, 0, 360);
	glPopMatrix();
}

void rumpf()
{
	nase();

	setColor(0.7, 0.7, 0.3);
	// Unterbau Rumpf
	glPushMatrix();
	glTranslatef(1.6, 0.75, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(4, 4, 8);
	glScalef(0.3, 0.25, 0.3);
	myCylinder();
	glPopMatrix();

	// W�nde Rumpf
	glPushMatrix();
	glTranslatef(0.1, 0.75, 0.5);
	glRotatef(-10, 1, 0, 0);
	glScalef(1.8, 1, 0.1);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.75, -0.5);
	glRotatef(180, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	glScalef(1.8, 1, 0.1);
	myCube();
	glPopMatrix();

	// Trennwand Cockpit-Rumpf nicht sichtbar, evtl. wichtig wenn scheibe transparent
	glPushMatrix();
	glTranslatef(0.95, 0.75, -0.425);
	glScalef(0.1, 1, 0.85);
	myCube();
	glPopMatrix();

	// Dach
	glPushMatrix();
	glTranslatef(1, 1.75, 0);
	glScalef(1.8, 0.5, 0.85);
	glRotatef(-90, 0, 1, 0);
	myCylinder();
	glPopMatrix();

	// Cockpit Scheibe
	setColor(0.6, 0.8, 1);
	glPushMatrix();
	glTranslatef(1.25, 1.4, 0);
	glScalef(0.75, 0.75, 0.7);
	mySphere();
	glPopMatrix();
}

void rotor()
{
	setColor(0.3, 0.3, 0.3);
	// Rotorenaufsatz
	glPushMatrix();
	glTranslatef(-0.3, 1.875, -0.25);
	glScalef(1, 0.25, 0.5);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, 2.5, 0);
	glRotatef(90, 1, 0, 0);
	myCone(0.15, 0.2, 0.5);
	glPopMatrix();

	static double alpha = 0;
	alpha += 0.1;

	setColor(0.1, 0.1, 0.1);
	// Hauptrotoren
	glPushMatrix();
	glTranslatef(-0.15, 2.35, 0);
	glRotatef(alpha, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -0.05);
	glRotatef(35, 1, 0, 0);
	glTranslatef(1.75, 0, 0);
	glScalef(3.5, 0.025, 0.1);
	myCube();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -0.05);
	glRotatef(35, 1, 0, 0);
	glTranslatef(1.75, 0, 0);
	glScalef(3.5, 0.025, 0.1);
	myCube();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -0.05);
	glRotatef(35, 1, 0, 0);
	glTranslatef(1.75, 0, 0);
	glScalef(3.5, 0.025, 0.1);
	myCube();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -0.05);
	glRotatef(35, 1, 0, 0);
	glTranslatef(1.75, 0, 0);
	glScalef(3.5, 0.025, 0.1);
	myCube();
	glPopMatrix();
	glPopMatrix();

	// Heckrotor
	glPushMatrix();
	glTranslatef(-4.2, 1.55, 0);
	setColor(0.3, 0.3, 0.3);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.25);
	glRotatef(180, 0, 1, 0);
	myCylinder();
	glPopMatrix();

	setColor(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glRotatef(alpha, 0, 0, 1);
	glTranslatef(0.375, -0.05, 0);
	glRotatef(35, 1, 0, 0);
	glScalef(0.75, 0.1, 0.025);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glRotatef(alpha, 0, 0, 1);
	glTranslatef(-0.375, -0.05, 0);
	glRotatef(-35, 1, 0, 0);
	glTranslatef(0, 0, 0.05);
	glScalef(0.75, 0.1, 0.025);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glRotatef(alpha + 90, 0, 0, 1);
	glTranslatef(-0.375, -0.05, 0);
	glRotatef(-35, 1, 0, 0);
	glTranslatef(0, 0, 0.05);
	glScalef(0.75, 0.1, 0.025);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glRotatef(alpha + 90, 0, 0, 1);
	glTranslatef(0.375, -0.05, 0);
	glRotatef(35, 1, 0, 0);
	glScalef(0.75, 0.1, 0.025);
	myCube();
	glPopMatrix();
	glPopMatrix();
}

void heck()
{
	setColor(0.7, 0.7, 0.3);
	//�bergang unten
	glPushMatrix();
	glScalef(0.5, 0.5, 0.6);
	mySphere();
	glPopMatrix();

	//�bergang oben
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(0.75, 0.25, 0.425);
	mySphere();
	glPopMatrix();

	// Verbindungsst�ck
	glPushMatrix();
	glTranslatef(-0.2, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.6, 0.8, 1);
	myCylinder();
	glPopMatrix();

	//�bergangsw�nde
	glPushMatrix();
	glTranslatef(-0.25, 0, 0.5);
	glRotatef(-10, 1, 0, 0);
	glTranslatef(0.25, 0, 0.1);
	glRotatef(-37, 0, 1, 0);
	glTranslatef(-0.25, 0, -0.1);
	glScalef(0.5, 1, 0.1);
	myCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0, -0.6);
	glRotatef(10, 1, 0, 0);
	glTranslatef(0.25, 0, 0);
	glRotatef(37, 0, 1, 0);
	glTranslatef(-0.25, 0, 0);
	glScalef(0.5, 1, 0.1);
	myCube();
	glPopMatrix();

	// heck
	setColor(0.7, 0.7, 0.3);
	glPushMatrix();
	glTranslatef(0, 0.8, 0);
	glScalef(3, 0.4, 0.28);
	glRotatef(-90, 0, 1, 0);
	myCylinder();
	glPopMatrix();

	// setColor(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(-3.1, 0.9, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.2, 0.5, 0.15);
	mySphere();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.2, 0.575, -0.05);
	glRotatef(45, 0, 0, 1);
	glScalef(0.4, 0.85, 0.1);
	glRotatef(-25, 0, 0, 1);
	myCube();
	glPopMatrix();
}

void heli::animate(GLfloat x, GLfloat y, GLfloat z)
{
	if (angle < -45) {
		angle = -45;
	}
	if (angle > 45) {
		angle = 45;
	}

	double pi = 2 * acos(0.0);
	pos[0] += 0.001 * angle * cos(rotation * pi / 180);
	pos[2] += 0.001 * angle * -sin(rotation * pi / 180);

	std::cout << "; rotation: " << rotation;

	// static GLfloat alpha = 0.00f;
	// alpha += 0.01f;
	// heli::rotation = heli::rotation + alpha;
		
	//Heli zeichnen
		glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glRotatef(rotation, 0, 1, 0);
			glRotatef(-angle, 0, 0, 1);
			// Kufen zeichnen
			glPushMatrix();
				setColor(0, 0.75, 0.75);
				kufen();
			glPopMatrix();

			glPushMatrix();
				rumpf();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.8, 0.75, 0);
				heck();
			glPopMatrix();

			glPushMatrix();
				rotor();
			glPopMatrix();
		glPopMatrix();
}