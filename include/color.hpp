#pragma once

// only support double for now

namespace renderer{
struct color
{
    double red, green, blue;
    color(const double& r, const double& g, const double& b) : red(r), green(g), blue(b) {}
};

color operator+ (const color& lhs, const color& rhs);

} // the end of the namespace renderer