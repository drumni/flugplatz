#define _CRT_SECURE_NO_WARNINGS

#pragma region INCLUDES
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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
	cg_key key;
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
		x = xp;
		y = yp;
		z = zp;
	}
	
	cg_globState::cameraPos[0] = x;
	cg_globState::cameraPos[1] = z;
	int Oben = (The <= 0.5 * M_PI || The > 1.5 * M_PI) * 2 - 1;

	// globale, mausgesteuerte Sicht
	gluLookAt(x, y, z, 0+ pos[0], 0+ pos[1], 0+ pos[2], 0, Oben, 0);
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
		float m_amb[4] = { 0.2, 0.2, 0.2, 1.0 };
		float m_diff[4] = { 0.2, 0.2, 0.6, 1.0 };
		float m_spec[4] = { 0.8, 0.8, 0.8, 1.0 };
		float m_shine = 32.0;
		float m_emiss[4] = { 0.0, 0.0, 0.0, 1.0 };

		setMaterial(GL_FRONT_AND_BACK, m_amb, m_diff, m_spec, m_shine, m_emiss);

		//setLights();

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
#define NUM_TEXTURES 1

const char* texture_files[NUM_TEXTURES] = {
	"./textures/plane.jpg" };

cg_image textures[NUM_TEXTURES]; // die GL Texturobjekte

// die Texturen laden und vorbereiten
void initTextures()
{

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		bool success = false;
		success = textures[i].load(texture_files[i], false);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		if (!success)
			printf("Can not load texture %s!\n", texture_files[i]);
	}
}

#define num_objects 3				  // wir haben 2 Wavefront Objekte
const char* objects_dir = "./Scene/"; // ... im Verzeichnis ./Scene
const char* objects_paths[num_objects] = { /*"ground_concrete.obj",*/ "ground_street.obj", "platform.obj", "plane.obj"};

cg_object3D objects[num_objects];
// Objektbezeichner f�r den Zugriff auf die Wavefront Objekte
enum
{
	//GROUND_OBJ1,
	GROUND_OBJ2,
	LANDSCAPE,
	PLANE
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

	//objects[GROUND_OBJ1].setMaterial(0.4, 0.4, 0.4, 1.0, 0.0, 128.0, 0.0);
	objects[GROUND_OBJ2].setMaterial(0.2, 0.2, 0.2, 1.0, 0.0, 128.0f, 0.0);
	objects[LANDSCAPE].setMaterial(0.17, 0.17, 0.15, 1.0, 0.0, 0.0, 0.0);
	objects[LANDSCAPE].setPosition(65, -0.001, -30);
	objects[PLANE].setMaterial(0.4, 0.4, 0.2, 1.0, 0.0, 20.0f, 0.0);
	objects[PLANE].setPosition(30, 0, 0);
}

void drawScene()
{
	static heli helicopter;
	cg_globState globState;
	cg_key key;
	cg_help help;
	GLfloat camerapos[] = { 0, 0, 0 };
	static int camerastate = 1;

	

	// Zeichnet die Szene 1x im Weltkoordinatensystem

	// Kamera setzen (spherische Mausnavigation)
	if (camerastate != 1 && 1 == key.keyState('1')) {
		camerastate = 1;
	}
	else if (camerastate != 2 && 1 == key.keyState('2')) {
		camerastate = 2;
	}

	switch (camerastate){
	//Fester Standpunkt
	case 1:
		setCamera(camerapos, 0, 0, 0, 1);
		break;
	//Hinter dem Hubschrauber
	case 2:
		double xpc = 20.0 * -cos(helicopter.rotation * M_PI / 180) + helicopter.pos[0];
		double zpc = 20.0 * sin(helicopter.rotation * M_PI / 180) + helicopter.pos[2];
		setCamera(helicopter.pos, xpc, helicopter.pos[1] + 5.0, zpc, 0);
		break;
	//default:
		//std::cout << "Fehler bei Camerastatewahl";
	}


	if (1 == key.keyState('t') || 1 == key.keyState('T'))
	{
		globState.textureMode = !globState.textureMode; // Texturierung on/off
	}
	else if (1 == key.keyState('b') || 1 == key.keyState('B'))
	{
		globState.blendMode = !globState.blendMode; // Blending on/off
	}

	// Stra�e bei Y=0 zeichnen
	//objects[GROUND_OBJ1].draw();
	objects[GROUND_OBJ2].draw();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	objects[LANDSCAPE].draw();
	glPopMatrix();
	
	static cg_image* _texture;
	_texture = &textures[0];
	
	if (globState.textureMode) {
		glEnable(GL_TEXTURE_2D);

		_texture->setEnvMode(GL_DECAL);
		_texture->bind();
	}

	objects[PLANE].draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	helicopter.animate(0.0f, 1.0f, 0.0f);

	if (2 == key.specialKeyState(GLUT_KEY_LEFT))
	{
		helicopter.rotation += helicopter.rotationSpeed * help.getFps();
	}

	if (2 == key.specialKeyState(GLUT_KEY_RIGHT))
	{
		helicopter.rotation -= helicopter.rotationSpeed * help.getFps();
	}

	if (2 == key.specialKeyState(GLUT_KEY_UP))
	{
		helicopter.angle += helicopter.angleSpeed * help.getFps();
	}

	if (2 == key.specialKeyState(GLUT_KEY_DOWN))
	{
		helicopter.angle -= helicopter.angleSpeed * help.getFps();
	}

	if (2 == key.specialKeyState(GLUT_KEY_SHIFT_L)) {
		helicopter.enginePower += helicopter.engineAcc * help.getFps();
	}
	if (2 == key.specialKeyState(GLUT_KEY_CTRL_L)) {
		helicopter.enginePower -= helicopter.engineAcc * help.getFps();
	}

	int counter = 1;
	for (size_t i = 0; i < 2; i++)
	{
		laterne(counter, -(30.0f * i) + 10, 0.0f, 6.5f, 4.7f);
		counter++;
		laterne(counter, -(30.0f * i) + 10, 0.0f, -9.5f, 4.7f);
		counter++;
	}
}
