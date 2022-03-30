# Praxisorientierte Einführung in die Computergraphik

Mit der verwendung von OpenGL.
___

## Szene Elemente

### Helikopter

#### 3D-Model

> von Thoralf Teumer
* Heck und Hauptrotoren
* Kufen
  * Kufe 
* Rumpf
  * Nase & Wände
* Heck
* Cockpitscheibe (Transparent)

#### Spotlight

> von Robin Seerig und Thoralf Teumer

#### Steuerung

> von Robin Seerig, weitergeführt und animiert von Thoralf Teumer

    SHIFT: nach oben
    STRG: nach unten
    Pfeil-LINKS: drehung links
    Pfeil-RECHTS: drehung rechts
    Pfeil-Oben: neigung nach vorne (vorwärts fliegen)
    Pfeil-Unten: neigung nach hinten (rückwärts fliegen)

Die Neigung ist erst ab einer gewissen Höhe verfügbar! Sinkt man, setzt kurz über dem Boden eine Landeanimation ein.

![Helicopter](https://i.imgur.com/9nOb6Hf.png)

### Laterne

> von Robin Seerig

![Laterne](https://i.imgur.com/fEnkXzI.png)

### Flugzeug

> von Robin Seerig

Das Flugzeug ist innerhalb des Programmes Blender entstanden,
hier habe ich Beispiele aus dem Internet rausgesucht und dann
Formen dazu erstellt.

![Flugzeug](https://i.imgur.com/w7iYoVq.png)

### Windrad

> von Thoralf Teumer

Ein rotes Punktlicht auf dem mit Blender erstellten Windrad warnt vor Kollisionen.

![Windrad](https://i.imgur.com/By33yK1.png)

### Landschaft

> von Thoralf Teumer

Die Landschaft wurde ebenfalls mit Blender gestaltet.

![Landschaft](https://i.imgur.com/TwVL2jT.png)

### Direktionales Licht

> von Robin Seerig

Eine Implementierte Funktion für die Berechnung des RGB-Wertes
anhand einer Temperatur. Mit den Ziel einen Tagesrhytmus zu simulieren.

Die Temperatur der Szene steigt stätig.

### Kameraeinstellungen

Ein wechsel zwischen den Kameraperspektiven ist über die Tasten 1 bis 3 Möglich.

#### Standartperspektive

Die Standartperspektive aus Übung 12.

#### 3th Person

> von Thoralf Teumer

Die Verfolgeransicht. Die Kamera folgt dem Hubschrauber mit einstellbarem Abstand. (Mit geringstem Abstand am schönsten)

#### 1st Person

> von Robin Seerig

Cockpit perspektive aus dem Flugzeug herraus.