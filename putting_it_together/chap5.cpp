#include <renderer.hpp>

using namespace renderer;

const color c(1, 1, 0);
const auto RAY_ORIGIN = pointFactory(0, 0, -5);
constexpr float WALL_Z = 10.0f;
constexpr float WALL_SIZE = 7.0f;
constexpr size_t CANVAS_PIXELS = 1000;
constexpr float PIXEL_SIZE = WALL_SIZE / CANVAS_PIXELS;


void drawCircle()
{
    // at the origin , radius = 1.0
    sphere sph{};
    canvas cvs(CANVAS_PIXELS, CANVAS_PIXELS);

    for (size_t y = 0; y < CANVAS_PIXELS; y++) {
        // top = +half, bottom = -half
        auto worldY = WALL_SIZE / 2 - PIXEL_SIZE * y;
        for (size_t x = 0; x < CANVAS_PIXELS; x++) {
            auto worldX = -WALL_SIZE / 2 + PIXEL_SIZE * x;
            auto position = pointFactory(worldX, worldY, WALL_Z);

            ray r(RAY_ORIGIN, glm::normalize(position - RAY_ORIGIN));
            r.calcIntersect(sph);
            if(r.hit()) cvs.writePixel(x, y, c);
        }
    }
    cvs.saveasPNG("unshaded sphere");
}

int main() { drawCircle(); }