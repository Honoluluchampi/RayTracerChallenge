#pragma once
#include <cstdlib>
#include <vector>
#include <color.hpp>

// |-----> x
// |
// |  canvas
//\/
// y

namespace renderer
{
struct canvas
{
    size_t width, height;
    canvas(const size_t w, const size_t h);
    void writePixel(const size_t x, const size_t y, const color& clr);
    const color& readPixel(const size_t x, const size_t y) const;
private:
    std::vector<color> pixels;
};
} // the end of the namespace renderer