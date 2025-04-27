#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

//Linetracking sensors (23mm spacing)
inline pros::adi::AnalogIn leftLine('A');
inline pros::adi::AnalogIn midLine('B');
inline pros::adi::AnalogIn rightLine('C');

//Outer linetracking sensors
inline pros::adi::AnalogIn leftOuterLine('D');
inline pros::adi::AnalogIn rightOuterLine('E');


//Color sensors  (58mm spacing)
inline pros::Optical leftColor(19);
inline pros::Optical rightColor(21);

//Ultrasonic sensors //Centered in the front of the robot
inline pros::Distance ultrasonic(18);
inline pros::Distance sideUltrasonic(17);

//Other
inline pros::adi::DigitalIn resetBut('F');

inline pros::adi::Motor servo('G');


//Examples:
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');