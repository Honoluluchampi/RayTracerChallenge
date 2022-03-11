#pragma once
#include <utils.hpp>

// only support double for now

namespace renderer{
struct color
{
    double red, green, blue;
    color(const double& r, const double& g, const double& b) : red(r), green(g), blue(b) {}
};

color operator+ (const color& lhs, const color& rhs)
{ return color(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue); }
color operator- (const color& lhs, const color& rhs)
{ return color(lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue - rhs.blue); }
color operator* (const color& clr, const double& dbl)
{ return color (clr.red * dbl, clr.green * dbl, clr.blue * dbl); }
color operator* (const double& dbl, const color& clr)
{ return color (clr.red * dbl, clr.green * dbl, clr.blue * dbl); }
color operator* (const color& lhs, const color& rhs)
{ return color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue); }

color& operator+= (color& lhs, const color& rhs)
{ lhs.red += rhs.red; lhs.green += rhs.green; lhs.blue += rhs.blue; return lhs; }
color& operator-= (color& lhs, const color& rhs)
{ lhs.red -= rhs.red; lhs.green -= rhs.green; lhs.blue -= rhs.blue; return lhs; }
color& operator*= (color& clr, const double& dbl)
{ clr.red *= dbl; clr.green *= dbl; clr.blue *= dbl; return clr; }
color& operator*= (color& lhs, const color& rhs)
{ lhs.red *= rhs.red; lhs.green *= rhs.green; lhs.blue *= rhs.blue; return lhs; }

// for comparision
bool operator== (const color& lhs, const color& rhs)
{ return nearlyEqual<double>(lhs.red, rhs.red) && nearlyEqual<double>(lhs.green, rhs.green) && nearlyEqual<double>(lhs.blue, rhs.blue); }
bool operator!= (const color& lhs, const color& rhs)
{ return !(lhs == rhs); }
} // the end of the namespace renderer