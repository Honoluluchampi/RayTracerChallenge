#include <canvas.hpp>
#include <utils.hpp>
// https://www.nongnu.org/pngpp/doc/0.2.9/ (document of png++)
#include <png++/png.hpp>
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
        outputfile << static_cast<unsigned>(pixels_m[i].red * maximumColorValue) << " ";
        outputfile << static_cast<unsigned>(pixels_m[i].green * maximumColorValue) << " ";
        outputfile << static_cast<unsigned>(pixels_m[i].blue * maximumColorValue);
        if (++count < maxPixelsPerLine)
            outputfile << " ";
        else {
            count = 0;
            outputfile << std::endl;
        }
    }
    outputfile.close();
}

void renderer::canvas::saveasPNG(const std::string& filename)
{
    auto path = "image/" + filename + ".png";
    png::image<png::rgb_pixel> image(width_m, height_m);
    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for(png::uint_32 x = 0; x < image.get_width(); ++x) {
            const auto& pixel = pixels_m[pos2idx(x,y,width_m)];
            image[y][x] = png::rgb_pixel(pixel.red * MAXIMUM_COLOR_VALUE, pixel.green * MAXIMUM_COLOR_VALUE, pixel.blue * MAXIMUM_COLOR_VALUE);
        }
    }
    image.write(path);
}