#pragma once
#include <utils.hpp>

// only support float for now

namespace renderer{
struct color
{
    float red, green, blue;
    color(const float& r, const float& g, const float& b) : red(r), green(g), blue(b) {}
};

color operator+ (const color& lhs, const color& rhs);
color operator- (const color& lhs, const color& rhs);
color operator* (const color& clr, const float& dbl);
color operator* (const float& dbl, const color& clr);
color operator* (const color& lhs, const color& rhs);

color& operator+= (color& lhs, const color& rhs);
color& operator-= (color& lhs, const color& rhs);
color& operator*= (color& clr, const float& dbl);
color& operator*= (color& lhs, const color& rhs);

// for comparision
bool operator== (const color& lhs, const color& rhs);
bool operator!= (const color& lhs, const color& rhs);
} // the end of the namespace renderer