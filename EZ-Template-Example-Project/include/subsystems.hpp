#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::adi::AnalogIn leftLine('A');
inline pros::adi::AnalogIn rightLine('C');
inline pros::Optical leftColor(19);
inline pros::Optical rightColor(9);
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');