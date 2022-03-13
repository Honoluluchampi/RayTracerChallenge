#include <canvas.hpp>
#include <utils.hpp>
#include <iostream>
#include <fstream>

// w,h : width and height of the canvas
// canvas should be initialized to black
renderer::canvas::canvas(const size_t w, const size_t h) : 
    width_m(w), height_m(h), pixels_m(w*h, color(0,0,0)) {}
// x,y : position of the pixel, clr : rgb value of the pixel
void renderer::canvas::writePixel(const size_t x, const size_t y, const color& clr)
{ pixels_m[pos2idx(x,y,width_m)] = clr; }
// x,y : position of the pixel
const renderer::color& renderer::canvas::readPixel(const size_t x, const size_t y) const
{ return pixels_m[pos2idx(x,y,width_m)]; }

void renderer::canvas::saveasPPM(const std::string& filename, const unsigned& maximumColorValue) const
{
    std::string imageDir = "image/";
    auto path = imageDir + filename + ".ppm";
    std::ofstream outputfile;
    outputfile.open(path, std::ios::out);
    // magic number for plain ppm file 
    outputfile << "P3" << std::endl;
    // size of the canvas
    outputfile << width_m << " " << height_m << std::endl; 
    outputfile << maximumColorValue << std::endl;
    // pixel valus (red -> green -> blue)
    unsigned count = 0;
    // prevent a ppm file's line from being too long
    unsigned maxPixelsPerLine = 6;
    for (size_t i = 0; i < width_m * height_m; i++) {
        outputfile << static_cast<unsigned>(pixels_m[i].red * 255) << " ";
        outputfile << static_cast<unsigned>(pixels_m[i].green * 255) << " ";
        outputfile << static_cast<unsigned>(pixels_m[i].blue * 255);
        if (++count < maxPixelsPerLine)
            outputfile << " ";
        else {
            count = 0;
            outputfile << std::endl;
        }
    }
    outputfile.close();
}