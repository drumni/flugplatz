
/*void drawAxis(bool doubleWheel) {
	// eine Achse
	objects[AXIS].draw();

	// Aufruf f�r linkes Rad
	glPushMatrix();
	glTranslatef(-0.9f, 0.0, 0.0);    // Versatz nach Links (-x)
	objects[WHEEL_SCREWS].draw();
	if (doubleWheel)
		objects[WHEEL_DOUBLE].draw();
	else objects[WHEEL_SINGLE].draw();
	glPopMatrix();

	// Aufruf f�r rechts Rad
	glPushMatrix();
	glTranslatef(0.9, 0.0, 0.0);      // Versatz nach Rechts (+x)
	glRotatef(180.0, 0.0, 1.0, 0.0);  // 180� Drehung um Hochachse (Y)
	objects[WHEEL_SCREWS].draw();
	if (doubleWheel)
		objects[WHEEL_DOUBLE].draw();
	else
		objects[WHEEL_SINGLE].draw();
	glPopMatrix();
};

#pragma region VEHICLE
// Superklasse f�r die Fahrzeuge
class CVehicle {
protected:
	CVector _pos = CVector(0, 0, 0);	//  Position [m]
	float _rot = 0;						//  Rotation [�]
public:
	void setPos(CVector pos) { _pos = pos; }
	void setPos(float posX, float posZ) { _pos = CVector(posX, 0, posZ); }
	void setRot(float rot) { _rot = rot; }
	CVector getPos(void) { return _pos; }
	float getRot(void) { return _rot; }

	virtual void draw(void) { return; }
};

#pragma endregion

#pragma region TRUCK
// Klasse f�r den Truck
class CTruck : public CVehicle {

public:
	CTruck()	// constructor
	{
		_pos = CVector(0, 0, 0);
		_rot = 0;
	}

	void update()
	{
		// ...
	}

	void draw(void)
	{
		glPushMatrix();
		// Den Truck laut seinen Animationsparametern positionieren und ausrichten
		// pos[], rot
		glTranslatef(_pos.x(), 0.5, _pos.z());
		glRotatef(_rot, 0, 1, 0);

		// Vorderachse
		glPushMatrix();
		glTranslatef(0, 0, 6.2);
		drawAxis(false);
		glPopMatrix();

		// Hinterachse 1
		glPushMatrix();
		glTranslatef(0, 0, 0.7);
		drawAxis(true);
		glPopMatrix();

		// Hinterachse 2
		glPushMatrix();
		glTranslatef(0, 0, -0.4);
		drawAxis(true);
		glPopMatrix();

		// Chassis
		objects[TRUCK_TOP].draw();
		objects[TRUCK_CHROME].draw();

		// Fensterscheiben

		cg_globState globState;
		if (globState.blendMode) {
			// TODO U12.1: das OpenGL Blending aktivieren
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		//objects[TRUCK_GLASS].setMaterial(0,0,0.7,0.2,1,64,0);
		objects[TRUCK_GLASS].draw();

		// TODO U12:1 das Blending wieder deaktivieren
		glDisable(GL_BLEND);

		glPopMatrix();
	}
};
#pragma endregion // TRUCK

#pragma region TRAILER
// Klasse f�r die Verwaltung eines Trailers
class CTrailer : public CVehicle {
private:
	cg_object3D* _geometry;
	cg_image* _texture;

public:
	CTrailer(cg_object3D* geometry, cg_image* texture) {
		_geometry = geometry;
		_texture = texture;
	}

	// Trailer zeichnen
	void draw(void) {
		glPushMatrix();
		// pos[], rot
		glTranslatef(_pos.x(), 0.5, _pos.z());
		glRotatef(_rot, 0, 1, 0);

		{ // Fahrwerk und Rahmen
		// Achse 1
			glPushMatrix();
			glTranslatef(0, 0, -9.0);
			drawAxis(true);
			glPopMatrix();

			// Achse 2
			glPushMatrix();
			glTranslatef(0, 0, -10.2);
			drawAxis(true);
			glPopMatrix();

			// Rahmen + Aufbau
			objects[TRAILER_CHASSIS].draw();
		} // Fahrwerk und Rahmen

		{ // Container
			glPushMatrix();
			glTranslatef(0, 0.01, 0);

			// TODO U12.2: Den Container transparent zeichnen:
			// Blending aktivieren, siehe Aufgaben 1
			cg_globState globState;
			if (globState.blendMode) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			//objects[TRAILER_CARGO].setMaterial(1,1,1,1,1,0,0);

			// TODO U12.3: die Texturierung aktivieren und die Textur _texture binden,
			// vorher den gew�nschten Texturmodus einstellen, siehe �bung 11
			if (globState.textureMode) {
				glEnable(GL_TEXTURE_2D);

				_texture->setEnvMode(GL_DECAL);
				_texture->bind();
			}

			// TODO U12:4: das CARGO-Objekt mittel Backface Culling korrekt darstellen

			// Der Quader ist ein konvexes Objekt. Damit lassen sich Fehler in der
			// transparenten Darstellung mittels BackFace Culling adressieren.
			// Prinzip: zuerst die R�ckseiten zeichnen, damit werden nur die weiter
			// entfernten Fl�chen gerastert, danach die Vorderseiten.

			// wir merken uns den aktuellen Zustand des Cullings
			GLboolean cullingIsEnabled = false;
			glGetBooleanv(GL_CULL_FACE, &cullingIsEnabled);

			// Culling aktivieren f�r Vorderseiten
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			// die R�ckseiten zeichnen
			_geometry->draw();

			// Culling umschalten auf R�ckseiten
			glCullFace(GL_BACK);

			// die Vorderseiten zeichnen
			_geometry->draw();

			// das Backface-Cullung wieder deaktivieren, falls es aus war
			if (!cullingIsEnabled)
				glDisable(GL_CULL_FACE);

			// TODO U12.3: die Texturierung deaktivieren
			glDisable(GL_TEXTURE_2D);

			// TODO U12:2 das Blending wieder deaktivieren
			glDisable(GL_BLEND);
			glPopMatrix();
		} // Container

		glPopMatrix();
	};
}; // CTrailer
#pragma endregion // TRAILER
*/
///////////////////////////////////////////////////////////////////////////////////////////////
// es folgt das Zeichnen der Fahrzeuge (hier ohne Animation) //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// globale Instanzen
// CTruck truck;

// TODO U12.3: hier eine Textur w�hlen, Index 0 = container.bmp, index 1 = opengl.bmp
// CTrailer trailer1(&objects[TRAILER_CARGO], &textures[0]);
// CTrailer trailer2(&objects[TRAILER_CARGO], &textures[0]);


	// Truck und Trailer positionieren
	/*truck.setPos(-5, 5);
	truck.setRot(90);
	trailer1.setPos(-2, 0);
	trailer1.setRot(25);
	trailer2.setPos(2, -1);
	trailer2.setRot(-25);

	// TODO U12.2: Berechnen der Entfernungen
	// 1. Kamera-Truck
	// 2. Kamera-Trailer1
	// 3. Kamera-Trailer2
	// dann Zeichnen der Fahrzeuge von "hinten" nach "vorn"

	// die Kameraposition
	CVector camPos = CVector(cg_globState::cameraPos[0], 0, cg_globState::cameraPos[1]);

	// die Vektoren Kamera-->Objekt
	CVector vec_to_truck;
	CVector vec_to_trailer1;
	CVector vec_to_trailer2;

	// TODO U12.2 Schritt2 - Distanzvektoren bestrimmen
	vec_to_truck = truck.getPos() - camPos;
	vec_to_trailer1 = trailer1.getPos() - camPos;
	vec_to_trailer2 = trailer2.getPos() - camPos;

	// wir sortieren nun die Objekt-Indizes absteigend nach der Entfernung
	const int numObjects = 3;

	// initial sind die Indizes der Objekte truck=0, trailer1=1 und trailer2=2
	int objectIndexes[numObjects] = { 0,1,2 };

	// die Entfernungen zwischen Kamera und den Objekten
	float distances[numObjects];
	distances[0] = vec_to_truck.len();
	distances[1] = vec_to_trailer1.len();
	distances[2] = vec_to_trailer2.len();

	// Indizes nach absteigenden Entfernungen sortieren, Algorthmus bubblesort
	bool switched = false;
	do
	{
		switched = false;
		for (int i = 1; i < numObjects; i++)
		{
			if (distances[objectIndexes[i - 1]] < distances[objectIndexes[i]])
			{
				int tempi = objectIndexes[i];
				objectIndexes[i] = objectIndexes[i - 1];
				objectIndexes[i - 1] = tempi;
				switched = true;
			}
		}
	} while (switched);

	// TODO U12.2 Schritt3 - Zeichnen in der richtigen Reihenfolge
	// zun�chst das unsortierte Zeichnen entfernen
	truck.draw();
	trailer1.draw();
	trailer2.draw();

	// TODO U12.3: stattdessen sortiert zeichnen
	for (int i = 0; i < numObjects; i++) {
		switch (objectIndexes[i]) {
		case 0: // den Truck zeichnen
			truck.draw();
			break;
		case 1: // den Trailer1 zeichnen
			trailer1.draw();
			break;
		case 2: // den Trailer 2 zeichnen
			trailer2.draw();
			break;
		}
	}*/

	// Texturierung und Blending global deaktivieren
