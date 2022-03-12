#pragma once
#include <utils.hpp>

// only support double for now

namespace renderer{
struct color
{
    double red, green, blue;
    color(const double& r, const double& g, const double& b) : red(r), green(g), blue(b) {}
};

color operator+ (const color& lhs, const color& rhs);
color operator- (const color& lhs, const color& rhs);
color operator* (const color& clr, const double& dbl);
color operator* (const double& dbl, const color& clr);
color operator* (const color& lhs, const color& rhs);

color& operator+= (color& lhs, const color& rhs);
color& operator-= (color& lhs, const color& rhs);
color& operator*= (color& clr, const double& dbl);
color& operator*= (color& lhs, const color& rhs);

// for comparision
bool operator== (const color& lhs, const color& rhs);
bool operator!= (const color& lhs, const color& rhs);
} // the end of the namespace renderer