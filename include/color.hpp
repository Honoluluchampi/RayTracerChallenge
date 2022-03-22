#pragma once
#include <utils.hpp>

// only support float for now

namespace renderer{
struct color
{
    float red, green, blue;
    color(const float& r, const float& g, const float& b) : red(r), green(g), blue(b) {}
    inline const color& censore() {red=std::min(red,1.0f); green=std::min(green,1.0f); blue=std::min(blue,1.0f); return *this;}
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