#include "heli.h"
#include "geometry.h"
#include "light.h"

void mast(GLfloat h)
{
	setColor(0.2, 0.2, 0.2);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2f, 0.2f, h);
	myCylinder();
	glPopMatrix();
};

void lampe(GLfloat h)
{

	glPushMatrix();
	glTranslatef(0, h, 0);
	setColor(1, 0.3, 0.1);
	glScalef(0.3, 0.25, 0.3);
	mySphere();
	glPopMatrix();
};

void deckel(GLfloat h)
{
	setColor(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0, h + 0.5f, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.25, 0.3);
	myCone(1, 2.5f, 2);
	glPopMatrix();
};

void anker() {
	setColor(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.25, 0.3);
	myCone(0.5f, 0.7f, 0.4);
	glPopMatrix();
};

void laterne(int id, GLfloat x, GLfloat y, GLfloat z, GLfloat h)
{
	cg_light lamp(id);
	lamp.setPosition(x, y + 5, z, 1);

	lamp.setDiffuse(.5f, .4f, .4f, 1.f);
	lamp.enable();	lamp.draw();

	glPushMatrix();
	glTranslatef(x, y, z);
	mast(h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, z);
	lampe(h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, z);
	deckel(h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, z);
	anker();
	glPopMatrix();
}