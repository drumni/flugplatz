#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

/*#ifdef _WIN32
#include "Include/freeglut.h"
#include "Include/glext.h"
#elif __linux__
#include "GL/glut.h"
#include "GL/glext.h"
#elif __APPLE__
#include "Include/freeglut.h"
#include "Include/glext.h"
#endif
*/

// Zeichnet einen Zylinder mit Durchmesser = Hoehe = 1 ausgehend von z=0 entlang der Z-Achse
void myCylinder();

// Zeichnet einen Zylinder variablen Abmessungen ausgehend von z=0 entlang der Z-Achse (startRadius bei z=0)
void myCylinder(float startRadius, float endRadius, float height);

// Zeichnet einen Kreiskegel bzw. oben offenen Kegelstump 
// ausgehend von z=0 entlang der Z-Achse (startRadius bei z=0)
void myCone(float startRadius, float endRadius, float height);

// Zeichnet einen Torus in der Ebene z=0
void myTorus(float innerRadius, float outerRadius);

// Zeichnet eine Einheitskugel
void mySphere();

// Zeichnet einen achsparallelen Würfel mit der Kantenlänge 1
void myCube();

// Zeichnet eine partielle Kreisscheibe
void myPartialDisk(float innerRadius, float outerRadius, float startAngle, float endAngle);

// Zeichnet den Szenenuntergrund
void myGround();

#endif