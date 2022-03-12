#include <color.hpp>

using namespace renderer;

color renderer::operator+ (const color& lhs, const color& rhs)
{ return color(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue); }
color renderer::operator- (const color& lhs, const color& rhs)
{ return color(lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue - rhs.blue); }
color renderer::operator* (const color& clr, const double& dbl)
{ return color (clr.red * dbl, clr.green * dbl, clr.blue * dbl); }
color renderer::operator* (const double& dbl, const color& clr)
{ return color (clr.red * dbl, clr.green * dbl, clr.blue * dbl); }
color renderer::operator* (const color& lhs, const color& rhs)
{ return color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue); }

color& renderer::operator+= (color& lhs, const color& rhs)
{ lhs.red += rhs.red; lhs.green += rhs.green; lhs.blue += rhs.blue; return lhs; }
color& renderer::operator-= (color& lhs, const color& rhs)
{ lhs.red -= rhs.red; lhs.green -= rhs.green; lhs.blue -= rhs.blue; return lhs; }
color& renderer::operator*= (color& clr, const double& dbl)
{ clr.red *= dbl; clr.green *= dbl; clr.blue *= dbl; return clr; }
color& renderer::operator*= (color& lhs, const color& rhs)
{ lhs.red *= rhs.red; lhs.green *= rhs.green; lhs.blue *= rhs.blue; return lhs; }

// for comparision
bool renderer::operator== (const color& lhs, const color& rhs)
{ return nearlyEqual<double>(lhs.red, rhs.red) && nearlyEqual<double>(lhs.green, rhs.green) && nearlyEqual<double>(lhs.blue, rhs.blue); }
bool renderer::operator!= (const color& lhs, const color& rhs)
{ return !(lhs == rhs); }