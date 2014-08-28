Arduino-RC-Car
==============

This repository contains the code used to build an Arduino Robot controlled by a traditional PSX joystick.

Robot
-----

The robot was build using an Arduino Due with Wifi Shield (remember to short-circuit pins 3 and 7 or the shield won't be recognized by the Due) and a L298 module to control two different motors.
I used the Magician chassis to assemble the robot and fix all the stuffs on it, you can find it very easily online.


Controller
----------

I used a Raspberry Pi as a remote controller for the robot (but you can use whatever you want, even your laptop). Using a Joystick adapter I
connected a PSX controller to it.

Interaction
-----------

When a joystick button is pressed the computer processes the event and sends a command to the Arduino, the command is interpreted by the robot
that acts consequentially.
