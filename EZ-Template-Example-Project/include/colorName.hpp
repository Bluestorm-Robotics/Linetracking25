#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include <iostream>


/* List of colors needed to be defined
(define as constants so they are protected memory)
colorRed
colorGreen
colorBlack
colorWhite

*/
/*
inline const int colorRed < 345 > 30;
inline const int colorGreen;
inline const int colorBlack;
inline const int colorWhite;
*/


class ColorRange {
    public:
        ColorRange(int min, int max) : min_(min), max_(max) {}

        // Method to check if a value is within the range
        bool contains(int value) const {
            return value >= min_ && value <= max_;
        }

        // Overload the equality operator to compare with an integer
        bool operator==(int value) const {
            return contains(value);
        }

    private:
        int min_;
        int max_;
};

// Define color ranges

inline const ColorRange colorRed(0, 30);   // Example range for red
inline const ColorRange colorGreen(60, 200); // Example range for green
//inline const ColorRange colorBlack(0, 10);   // Example range for black
//inline const ColorRange colorWhite(240, 255); // Example range for white
inline const int colorBlack = 1800; //bro what somehow the sensor reads a dif range between days