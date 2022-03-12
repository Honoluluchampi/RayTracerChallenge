#include <canvas.hpp>
#include <utils.hpp>

// canvas should be initialized to black
renderer::canvas::canvas(const size_t w, const size_t h) : 
    width(w), height(h), pixels(w*h, color(0,0,0)) {}

void renderer::canvas::writePixel(const size_t x, const size_t y, const color& clr)
{ pixels[pos2idx(x,y,width)] = clr; }

const renderer::color& renderer::canvas::readPixel(const size_t x, const size_t y) const
{ return pixels[pos2idx(x,y,width)]; }