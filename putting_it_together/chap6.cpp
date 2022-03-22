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
    // sph.setTransform(glm::scale(glm::vec3(1, 0.5, 1)));
    // blue green sphere
    sph.setMaterial(material(color(0.2, 0.8, 0.3)));
    // light
    auto light = pointLight(pointFactory(-10, 10, -10));
    canvas cvs(CANVAS_PIXELS, CANVAS_PIXELS);

    for (size_t y = 0; y < CANVAS_PIXELS; y++) {
        // top = +half, bottom = -half
        auto worldY = WALL_SIZE / 2 - PIXEL_SIZE * y;
        for (size_t x = 0; x < CANVAS_PIXELS; x++) {
            auto worldX = -WALL_SIZE / 2 + PIXEL_SIZE * x;
            auto position = pointFactory(worldX, worldY, WALL_Z);
            
            // ray from the light to the pixel
            ray r(RAY_ORIGIN, glm::normalize(position - RAY_ORIGIN));
            r.calcIntersect(sph);

            // calc the lighting
            if(r.hit()) {
                auto hittingPoint = r.proceed(r.hit().value().t);
                auto normal = r.hit().value().pPrmt->normalAt(hittingPoint);
                auto eye = -r.direction;
                auto clr = lighting(r.hit().value().pPrmt->getMaterial(), light, hittingPoint, eye, normal);
                cvs.writePixel(x, y, clr);
            }
        }
    }
    cvs.saveasPNG("shaded_sphere");
}

int main() { drawCircle(); }