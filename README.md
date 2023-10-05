# Practical Introduction to Computer Graphics

Using OpenGL.
___

## Scene Elements

### Helicopter

#### 3D Model

* Tail and main rotors
* Skids
  * Skid
* Fuselage
  * Nose & walls
* Tail
* Cockpit window (Transparent)

#### Spotlight

#### Controls

    SHIFT: Ascend
    CTRL: Descend
    Left Arrow: Turn left
    Right Arrow: Turn right
    Up Arrow: Tilt forward (move forward)
    Down Arrow: Tilt backward (move backward)

Tilting is only available at a certain height!
When descending, a landing animation is triggered just above the ground.

![Helicopter](https://i.imgur.com/unv1pUk.png)

### Lantern

#### 3D Model

* Pole
* Lamp
  * Emitting light source
* Cover
  * Top and shade
* Anchor
* Glass pane (Transparent)

![Lantern](https://i.imgur.com/BHEJZBg.png)

### Airplane

The airplane was created within the Blender program.
I found examples on the internet and then added shapes to them.

![Airplane](https://i.imgur.com/XgPUO1v.png)

### Wind Turbine

A red point light on the wind turbine created in Blender serves as a collision warning.

Blinking of the light

![Wind Turbine](https://i.imgur.com/vtgt7rm.png)

### Landscape

The landscape was also created with Blender.

![Landscape](https://i.imgur.com/Fa0jS34.png)

#### Helipad Landing Function

![Helipad](https://i.imgur.com/49YvShW.png)

### Directional Light

An implemented function for calculating the RGB value based on temperature. The goal is to simulate a daily rhythm.

The temperature of the scene continually increases.

### Camera Settings

Switching between camera perspectives is possible using keys 1 to 3.

#### Default Perspective (Key `1`)

The default perspective from Exercise 12.

#### 3rd Person (Key `2`)

The chase view. The camera follows the helicopter with adjustable distance. (Closest distance looks the best)

#### 1st Person (Key `3`)

Cockpit perspective from inside the helicopter.
