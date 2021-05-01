# Not a Banksy

## Interdisciplinary course of Design and Robotics
9° edition, 2021

---
Laura Bonitta, school of Design

Samuele Camnasio, school of Engineering

Maria Castellvi, school of Design

Pavel Popov, school of Engineering

Hongwei Xu, school of Engineering

---

### Supervising professors:

Andrea Bonarini, DEIB department, Politecnico di Milano

Maximiliano Romero , Design department, IUAV, Venice University

---

### Supervising tutor:

Rohan Vangal



Code for the Robotics and design course, the final code for the working robot is in the 'firmware' folder, in the other folder can be found a series of sketches used to test the working of the single components, in particular:

-'basementTest': test the rotation of the basement, from 0 to 180 degrees and then back

-'combineStuff': code used to test more components together, now tries the sneeze sound combined with the head movement and the pump

-'headTest': test the movement of the head, put the head down and up

-'slidingDown': put down the picture of the sliding mechanism, can be used in case the mechanism gets stuck 

-'slidingTest': test the sliding mechanism by going up and back down 

-'slidingUp': put up the picture of the sliding mechanism

-'sneezeTest': test the correct working of the relay and the pump

-'speakerTest': test the correct working of the speakers and the DFPlayer by playing an MP3 file on the SD card

-'switchTest': test the correct working of the switch, making the robot act in different ways given the state read from the switch(HIGH or LOW).

All these testing codes are activated by the sonar sensor in the back of the robot (from a distance less than 10 cm)
