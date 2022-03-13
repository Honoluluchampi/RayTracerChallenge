#pragma once
#include <cstdlib>
#include <vector>
#include <color.hpp>
#include <string>

// |-----> x
// |
// |  canvas
//\/
// y

namespace renderer
{
constexpr unsigned MAXIMUM_COLOR_VALUE = 255;

struct canvas
{
    size_t width_m, height_m;
    canvas(const size_t w, const size_t h);
    void writePixel(const size_t x, const size_t y, const color& clr);
    const color& readPixel(const size_t x, const size_t y) const;
    void saveasPPM(const std::string& filename, const unsigned& maximumColorValue = MAXIMUM_COLOR_VALUE) const;
    void saveasPNG(const std::string& filename);
private:
    std::vector<color> pixels_m;
};
} // the end of the namespace renderer