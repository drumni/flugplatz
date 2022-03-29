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
	setColor(1, 0.85, 0.5);
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
	glPushMatrix();
		glPushMatrix();
		cg_light lamp(id);
		lamp.setPosition(x, y + h, z, 1);

		lamp.setAttentuation( .5f, .0f, .0f );
		lamp.setDiffuse(.39f, .25f, .1f, 0.0f);
		//lamp.setDiffuse(.0f, .0f, .01f, 0.0f);
		lamp.setSpotlight(0.0f, -1.0f, 0.0f, 70.0f, 1.0f);
		lamp.setAmbient(.2f, .1f, .1f, 1.f);
		//lamp.setSpecular(.9f, .3f, .3f, 1.f);	
		//lamp.setSpotlight(1, 1, 1, 20, 2);
		lamp.enable();	lamp.draw();
		//lamp.markLightPosition();
		lamp.disable();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x, y, z);
		mast(h);
		lampe(h);
		deckel(h);
		anker();
		glPopMatrix();
	glPopMatrix();
}