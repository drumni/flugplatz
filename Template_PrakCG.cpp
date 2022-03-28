#define _CRT_SECURE_NO_WARNINGS

#pragma region INCLUDES
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <cstdlib>

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

#include "laterne.h"
#include "heli.h"
#include "help.h"
#include "window.h"
#include "input.h"
#include "light.h"
#include "wavefront.h"
#include "image.h"
#include "vector.h"
#include "geometry.h"
#include <iostream>
#pragma endregion

void setCamera(); // Kamera platzieren, siehe Maus-Callbacks
void drawScene(); // Zeichnet die Szene im Weltkoordinatensystem

void loadObjects();
void initTextures();

/////////////////////////////////////////////////////////////////////////////////
//	Kamerafunktion
/////////////////////////////////////////////////////////////////////////////////


void setCamera(GLfloat pos[3], double xp, double yp, double zp, double radiusAdjustable)
{
	cg_mouse mouse;
	//cg_key key;
	// Ansichtstransformationen setzen,
	// SetCamera() zum Beginn der Zeichenfunktion aufrufen
	double x, y, z, The, Phi;
	static double radius = 10;
	// Maus abfragen
	if (cg_mouse::buttonState(GLUT_LEFT_BUTTON))
	{
		cg_globState::cameraHelper[0] += mouse.moveX() * 16 / 6;
		cg_globState::cameraHelper[1] += mouse.moveY() * 9 / 6;
	}

	if (cg_mouse::buttonState(GLUT_MIDDLE_BUTTON))
	{
		radius += 0.1 * mouse.moveY();
		if (radius < 1.0) radius = 1.0;
	}

	Phi = 0.2 * cg_globState::cameraHelper[0] / cg_globState::screenSize[0] * M_PI + M_PI * 0.5;
	The = 0.2 * cg_globState::cameraHelper[1] / cg_globState::screenSize[1] * M_PI;

	if (radiusAdjustable) {
		x = radius * cos(Phi) * cos(The);
		y = radius * sin(The);
		z = radius * sin(Phi) * cos(The);
	}
	else {
		x = radius * cos(Phi) * cos(The) + xp;
		y = radius * sin(The) + yp;
		z = radius * sin(Phi) * cos(The) + zp;
	}

	cg_globState::cameraPos[0] = x;
	cg_globState::cameraPos[1] = z;
	int Oben = (The <= 0.5 * M_PI || The > 1.5 * M_PI) * 2 - 1;

	// globale, mausgesteuerte Sicht
	gluLookAt(x, y, z, 0 + pos[0], 0 + pos[1], 0 + pos[2], 0, Oben, 0);
}

/////////////////////////////////////////////////////////////////////////////////
//	main : Anfang des OpenGL Programmes
/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	init(argc, argv);

	// Programm startet im Beleuchtungsmodus
	cg_globState::lightMode = true;

	// hier Objekte laden, erstellen etc.
	loadObjects();

	// Texturen laden und vorbereiten
	initTextures();

	// Die Hauptschleife starten
	glutMainLoop();
	return 0;
}

void displayFunc()
{
	// Hilfe-Instanzen
	cg_help help;
	cg_globState globState;
	cg_key key;

	// Tastatur abfragen
	// Achtung: einmaliges Bet�tigen funktioniert so nur mit glutIgnoreKeyRepeat(true) (siehe main())
	if (key.keyState(27))
	{
		exit(0); // Escape -> Programm beenden
	}
	else if (1 == key.keyState('f') || 1 == key.keyState('F'))
	{
		help.toggleFps(); // Framecounter on/off
	}
	else if (1 == key.keyState('h') || 1 == key.keyState('H') || 1 == key.specialKeyState(GLUT_KEY_F1))
	{
		help.toggle(); // Hilfetext on/off
	}
	else if (1 == key.keyState('k') || 1 == key.keyState('K'))
	{
		help.toggleKoordsystem(); // Koordinatensystem on/off
	}
	else if (1 == key.keyState('w') || 1 == key.keyState('W'))
	{
		globState.drawMode = (globState.drawMode == GL_FILL) ? GL_LINE : GL_FILL; // Wireframe on/off
	}
	else if (1 == key.keyState('l') || 1 == key.keyState('L'))
	{
		globState.lightMode = !globState.lightMode; // Beleuchtung on/off
	}
	else if (1 == key.keyState('i') || 1 == key.keyState('I'))
	{
		globState.cameraHelper[0] = 0; // Initialisierung der Kamera
		globState.cameraHelper[1] = 0;
	}

	// Szene zeichnen: CLEAR, SETCAMERA, DRAW_SCENE

	// Back-Buffer neu initialisieren
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// // Kamera setzen (spherische Mausnavigation)
	// setCamera();

	// Koordinatensystem zeichnen
	help.drawKoordsystem(-8, 10, -8, 10, -8, 10);

	// Zeichenmodus einstellen (Wireframe on/off)
	glPolygonMode(GL_FRONT_AND_BACK, globState.drawMode);

	// Backface Culling on/off, Standardwert ist Entfernen der R�ckseiten
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	if (globState.cullMode)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Farbmodus oder Beleuchtungsmodus ?
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	if (globState.lightMode == GL_TRUE) // Beleuchtung aktivieren
	{
		//float m_amb[4] = {0.2, 0.2, 0.2, 1.0};
		//float m_diff[4] = { 0.2, 0.2, 0.6, 1.0 };
		//float m_spec[4] = { 0.8, 0.8, 0.8, 1.0 };
		//float m_shine = 32.0;
		//float m_emiss[4] = { 0.0, 0.0, 0.0, 1.0 };

		//setMaterial(GL_FRONT_AND_BACK, m_amb, m_diff, m_spec, m_shine, m_emiss);
		setLights();

		glEnable(GL_LIGHTING);
	}
	else // Zeichnen im Farbmodus
	{
		glDisable(GL_LIGHTING);
		glColor4f(0.2, 0.2, 0.6, 1.0);
	}

	glEnable(GL_NORMALIZE);

	// die Szene zeichnen
	drawScene();

	// den Hilfetext �ber die Szene zeichnen, wenn gefordert
	help.draw();

	// Wireframe deaktivieren
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glFlush();		   // Daten an Server (fuer die Darstellung) schicken
	glutSwapBuffers(); // Buffers wechseln
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �BUNG 12 - Blending ////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	Texturdefinition
#define NUM_TEXTURES 2

const char* texture_files[NUM_TEXTURES] = {
	"./textures/planetexture.bmp", "./textures/grass2.bmp" };

cg_image textures[NUM_TEXTURES]; // die GL Texturobjekte

// die Texturen laden und vorbereiten
void initTextures()
{

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		bool success = false;
		success = textures[i].load(texture_files[i], true);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		if (!success)
			printf("Can not load texture %s!\n", texture_files[i]);
	}
}

#define num_objects 9				  // wir haben 2 Wavefront Objekte
const char* objects_dir = "./Scene/"; // ... im Verzeichnis ./Scene
const char* objects_paths[num_objects] = {"ground_street.obj", "Berge.obj", "H.obj",  "Landeplatz.obj", "plane.obj", "boden50x50.obj", "glass.obj", "Windrad.obj", "Fluegel.obj"};

cg_object3D objects[num_objects];
// Objektbezeichner f�r den Zugriff auf die Wavefront Objekte
enum
{
	//GROUND_OBJ1,
	GROUND_OBJ2,
	BERGE,
	H,
	LANDEPLATZ,
	PLANE,
	BODEN,
	GLASS,
	WINDRAD,
	FLUEGEL
};

void loadObjects()
{

	// alle Objekte Laden, wenn der Pfad verf�gbar ist (Pfad != "")
	for (int i = 0; i < num_objects; i++)
		if (strlen(objects_paths[i]) > 0)
		{
			char file[255] = "";
#ifndef _MSC_VER
			strcat(file, ".");
#endif // _MSC_VER
			strcat(file, objects_dir);
			strcat(file, objects_paths[i]); // file enth�lt nun den vollst�ndigen Dateinamen

			// Hier das Objekt laden
			// --> Aufruf von loadobject(file, false) f�r objects[i]
			objects[i].load(file, true);
		}
	// nun setzen wir die Materialeigenschaften f�r die Objekte

	objects[GROUND_OBJ2].setMaterial(0.2, 0.2, 0.2, 1.0, 0.0, 128.0f, 0.0);
	objects[BERGE].setMaterial(0.15, 0.15, 0.15, 1.0, 0.0, 0.0, 0.0);
	objects[BERGE].setPosition(65, -0.001, -30);
	objects[H].setMaterial(0.7, 0.7, 0.1, 1.0, 0.0, 0.0, 0.0);
	objects[H].setPosition(65, -0.001, -30);
	objects[LANDEPLATZ].setMaterial(0.3, 0.3, 0.3, 1.0, 0.0, 0.0, 0.0);
	objects[LANDEPLATZ].setPosition(65, -0.001, -30);
	objects[PLANE].setMaterial(0.2, 0.2, 0.1, 1.0, 0.0, 0.0f, 0.0);
	objects[PLANE].setPosition(30, 0, 0);
	objects[BODEN].setMaterial(1, 1, 1, 1.0, 0, 128, 0);
	objects[GLASS].setMaterial(0.3, 0.3, 1, 0.8, 0, 128, 0.1);
	objects[WINDRAD].setMaterial(0.9, 0.9, 0.9, 1, 0, 128, 0);
	objects[WINDRAD].setPosition(-60, 0, -60);
	objects[FLUEGEL].setMaterial(0.9, 0.9, 0.9, 1, 0, 128, 0);
	objects[FLUEGEL].setPosition(-60, 0, -60);
}

void drawUmgebung(int useLinearFiltering, int useMipmapFiltering) {
	// Stra�e bei Y=0 zeichnen
	//objects[GROUND_OBJ1].draw();

	glPushMatrix();
	glTranslatef(0, 0.01, 0);
	objects[GROUND_OBJ2].draw();
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	objects[BERGE].draw();
	objects[H].draw();
	objects[LANDEPLATZ].draw();
	glPopMatrix();
	objects[WINDRAD].draw();
	objects[FLUEGEL].draw();


	int currentTexture = 1;
	glEnable(GL_TEXTURE_2D);

	// der MAG-Filter kann GL_NEAREST (std) oder GL_LINEAR sein
	textures[currentTexture].setMagFilter(GL_LINEAR);
	//textures[currentTexture].setMagFilter(GL_NEAREST);
	// der MIN-Filter ist sinnvoll entweder GL_LINEAR (std) oder GL_LINEAR_MIPMAP_LINEAR sein
	//textures[currentTexture].setMinFilter(GL_LINEAR);
	textures[currentTexture].setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
	textures[currentTexture].setEnvMode(GL_MODULATE);
	textures[currentTexture].setWrapMode(GL_REPEAT);
	textures[currentTexture].bind();
	objects[BODEN].draw();
	glPopMatrix();
	

	//licht geht noch nicht// soll auf dem Windrad stehen 
	static cg_light point(7);
	point.setPosition(-60.0f, 23.802f, -62.7296f, 1.0f);
	point.setAmbient(0.1f, 0.1f, 0.1f, 1.0f);
	point.setDiffuse(0.9f, 0.0f, 0.0f, 1.0f);
	point.setSpecular(0.9f, 0.9f, 0.0f, 1.0f);
	point.enable();
	point.draw();

	glDisable(GL_TEXTURE_2D);
}


void setColorByTemp(int temp, GLfloat(*color)[4]) {
	if (temp <= 66) {
		(*color)[2] = temp - 10;
		(*color)[2] = 138.5177312231 * expl((*color)[2]) - 305.0447927307;
		if ((*color)[2] < 0) (*color)[2] = 0;
		if ((*color)[2] > 255) (*color)[2] = 255;

		(*color)[0] = 255;

		(*color)[1] = temp;
		(*color)[1] = 99.4708025861 * expl((*color)[1]) - 161.1195681661;
		if ((*color)[1] < 0) (*color)[1] = 0;
		if ((*color)[1] > 255) (*color)[1] = 255;
		if (temp <= 19) (*color)[2] = 0;
	}
	else {

		(*color)[0] = temp - 60;
		(*color)[1] = temp - 60;

		(*color)[0] = 329.698727446 * powl((*color)[0], -0.1332047592);
		(*color)[1] = 288.1221695283 * powl((*color)[1], -0.0755148492);

		if ((*color)[0] < 0) (*color)[0] = 0;
		if ((*color)[0] > 255) (*color)[0] = 255;

		if ((*color)[1] < 0) (*color)[1] = 0;
		if ((*color)[1] > 255) (*color)[1] = 255;

		(*color)[2] = 255;
	}

	(*color)[0] = (*color)[0] / 255;
	(*color)[1] = (*color)[1] / 255;
	(*color)[2] = (*color)[2] / 255;
	(*color)[3] = 1.0f;
}

void drawScene()
{
	static heli helicopter;
	static cg_image* _texture;

	cg_key key;
	cg_help help;
	cg_globState globState;
	GLfloat camerapos[] = { 0, 0, 0 };
	GLfloat directionalLightDiffuse[4] = { 1.0f, 1.0f,  1.0f, 0.3f };

	cg_light directionalLight(0);
	GLfloat global_light_power = 0.25f;
	static GLfloat global_temp = 100.0f; // Kelvin
	global_temp += (10000 / help.getFps());
	if (global_temp > 100000)
		global_temp = 0;

	setColorByTemp(global_temp, &directionalLightDiffuse);
	directionalLight.setPosition(1, 10, 10, 0);
	directionalLight.setDiffuse(directionalLightDiffuse[0] * global_light_power, directionalLightDiffuse[1] * global_light_power, directionalLightDiffuse[2] * global_light_power, directionalLightDiffuse[3]);
	directionalLight.setSpotlight(.0f, 1.f, 1.f, 180.0f, 0.0f);
	directionalLight.setAttentuation(0.f, 0.f, 0.f);
	directionalLight.enable();
	directionalLight.draw();

	glEnable(GL_NORMALIZE);

	// Kamera setzen (spherische Mausnavigation)
	static int camerastate = 1;
	if (camerastate != 1 && 1 == key.keyState('1')) {
		camerastate = 1;
	}
	else if (camerastate != 2 && 1 == key.keyState('2')) {
		camerastate = 2;
	}

	switch (camerastate) {
	case 1:
		//Fester Standpunkt
		setCamera(camerapos, 0, 0, 0, 1);
		break;
	case 2:
		//Hinter dem Hubschrauber
		double xpc = 20.0 * -cos(helicopter.rotation * M_PI / 180) + helicopter.pos[0];
		double zpc = 20.0 * sin(helicopter.rotation * M_PI / 180) + helicopter.pos[2];
		setCamera(helicopter.pos, xpc, helicopter.pos[1] + 5.0, zpc, 0);
		break;
	}

	if (1 == key.keyState('t') || 1 == key.keyState('T'))
		globState.textureMode = !globState.textureMode; // Texturierung on/off
	else if (1 == key.keyState('b') || 1 == key.keyState('B'))
		globState.blendMode = !globState.blendMode; // Blending on/off

	// Rendering 


	drawUmgebung(1, 0);


	_texture = &textures[0];
	if (globState.textureMode) {
		glEnable(GL_TEXTURE_2D);

		_texture->setEnvMode(GL_DECAL);
		_texture->bind();
	}
	if (globState.blendMode) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	objects[PLANE].draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	helicopter.animate();

	helicopter.draw();
	glPushMatrix();

	glTranslatef(helicopter.pos[0], helicopter.pos[1], helicopter.pos[2]);
	glRotatef(helicopter.rotation, 0, 1, 0);
	glRotatef(-helicopter.angle, 0, 0, 1);
	glTranslatef(1.25, 1.4, 0.0);
	objects[GLASS].draw();
	glPopMatrix();

	helicopter.calc();
	int counter = 1;
	for (size_t i = 0; i < 2; i++)
	{
		laterne(counter, -(30.0f * i) + 10, 0.0f, 6.5f, 4.7f);
		counter++;
		laterne(counter, -(30.0f * i) + 10, 0.0f, -9.5f, 4.7f);
		counter++;
	}
}
