#include "geometry.h"
#include "light.h"

#define SLICES 20			// für Zylindermantel, Boden und Deckel
#define STACKS 20			// für Zylindermantel
#define LOOPS 1				// für "Boden" und "Deckel"

// Zeichnet einen Zylinder mit Durchmesser = Hoehe = 1 ausgehend von z=0 entlang der Z-Achse
void myCylinder() {

	// Zeichnet einen Einheitszylinder ins WKS
	// d = 1, h = 1, Unterteilung: RINGS, SLICES
	// Lage: Basiskreis in X-Y-Ebene, Höhe entlang der +Z Achse

	GLUquadricObj *q = gluNewQuadric();

	glPushMatrix();

		// Mantelfläche
		gluCylinder(q, 0.5, 0.5, 1, SLICES, STACKS);

		// Deckel
		glTranslatef(0, 0, 1);
		gluDisk(q, 0, 0.5, SLICES, LOOPS);

		// Boden
		glTranslatef(0, 0, -1);
		glRotatef(180, 0, 1, 0);
		gluDisk(q, 0, 0.5, SLICES, LOOPS);

	glPopMatrix();

	gluDeleteQuadric(q);

};

// Zeichnet einen Zylinder variablen Abmessungen ausgehend von z=0 entlang der Z-Achse (startRadius bei z=0)
void myCylinder(float startRadius, float endRadius, float height) {

	// Zeichnet einen Zylinder mit variablen Abmessungen ins WKS
	// Unterteilung: RINGS, SLICES
	// Lage: Basiskreis in X-Y-Ebene, Höhe entlang der +Z Achse

	GLUquadricObj *q = gluNewQuadric();

		glPushMatrix();

			// Mantelfläche
			gluCylinder(q, startRadius, endRadius, height, SLICES, STACKS);

			// Deckel
			glTranslatef(0, 0, height);
			gluDisk(q, 0, endRadius, SLICES, LOOPS);

			// Boden
			glTranslatef(0, 0, -height);
			glRotatef(180, 0, 1, 0);
			gluDisk(q, 0, startRadius, SLICES, LOOPS);

		glPopMatrix();

	gluDeleteQuadric(q);
};


// Zeichnet einen Kreiskegel bzw. oben offenen Kegelstump 
// ausgehend von z=0 entlang der Z-Achse (startRadius bei z=0)
void myCone(float startRadius, float endRadius, float height) {
	GLUquadricObj *q = gluNewQuadric();

	glPushMatrix();
		// Mantelfläche
		gluCylinder(q, startRadius, endRadius, height, SLICES, STACKS);

		// Boden
		glRotatef(180, 0, 1, 0);
		gluDisk(q, 0, startRadius, SLICES, LOOPS);
	glPopMatrix();

	gluDeleteQuadric(q);
}

// Zeichnet einen Torus in der Ebene z=0
void myTorus(float innerRadius, float outerRadius) {
	glutSolidTorus(innerRadius, outerRadius, SLICES, STACKS);
}


// Zeichnet eine Einheitskugel
void mySphere() {
	glutSolidSphere(1, SLICES, STACKS);
}

// Zeichnet eine partielle Kreisscheibe
void myPartialDisk(float innerRadius, float outerRadius, float startAngle, float endAngle) {
	GLUquadricObj *q = gluNewQuadric();
		gluPartialDisk(q, innerRadius, outerRadius, SLICES, LOOPS, startAngle, endAngle);
	gluDeleteQuadric(q);
}

// Zeichnet den Szenenuntergrund
void myGround()
{
	GLUquadricObj *q = gluNewQuadric();
	glPushMatrix();
		glRotatef(90, -1, 0, 0);
		gluDisk(q, 0, 20, SLICES, LOOPS);
	glPopMatrix();
	gluDeleteQuadric(q);
}

// Zeichnet einen achsparallelen Würfel mit der Kantenlänge 1
void myCube() {

	// TODO: Aufgabe 3
	// Würfel zeichnen

	// die Attribute auf den Stack sichern (siehe Übungsblatt)
	glPushMatrix();
		// einen geeigneten Ursprung wählen
		glTranslatef(0, 0.5, 0.5);
		
		// Solid-Cube zeichnen
		glutSolidCube(1.0);

		// Umrandung zeichnen
		glPushAttrib(GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
			setColor(0.1, 0.1, 0.1);
			glDepthFunc(GL_LEQUAL);
			glutWireCube(1.005);
		glPopAttrib();
	glPopMatrix();

};


