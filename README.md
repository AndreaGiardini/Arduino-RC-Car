Arduino-RC-Car
==============

This repository contains the code used to build an Arduino Robot controlled by a traditional PSX joystick.

Robot
-----

The robot was build using an Arduino Due with Wifi Shield (remember to short-circuit pins 3 and 7 or the shield won't be recognized by the Due) and a L298 module to control two different motors.
I used the Magician chassis to assemble the robot, you can find it very easily online.


Controller
----------

I used a Raspberry Pi as a remote controller for the robot (but you can use whatever you want, even your laptop). Using a Joystick adapter I connected a PSX controller to it [this one](http://www.dx.com/p/ps2-game-controller-to-pc-usb-converter-789)

Interaction
-----------

When a joystick button is pressed the computer processes the event and sends a command to the Arduino, the command is interpreted by the robot that acts consequentially.


Make it work
------------

- Create a wifi access point with WPA/WPA2 auth on channel one (I used hostapd with a dhcp/dns server - If the channel il != from 1 Arduino might not find the wifi network)
- Compile RemoteControl.c with `gcc RemoteControl.c` and start the executable
- Open the Arduino sketch and edit Wifi name/password
- Upload the sketch to Arduino
- After a while you should se a "GOT CONNECTION" message on your screen, the arduino is now connected to the joystick

TODO
----

* Clean the C code (maybe write it also in python?)
* TCP -> UDP - Right now I'm using TCP which is not good for this kind of application. UDP it's definately better in this case but it seems to heve a bugged Arduino library (starts dropping packets after a while)
* Automate hostapd and dhcpd installation

