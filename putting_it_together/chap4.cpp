// draw points on the number position of the clock

#include <renderer.hpp>
using namespace renderer;

constexpr unsigned POINT_NUM = 12;
constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGHT = 600;
constexpr unsigned RADIUS = 50.0f;

std::vector<tuple> calcPointsPos()
{
    std::vector<tuple> pointsList;
    // standard point
    auto stdPoint = pointFactory(RADIUS, 0, 0);
    pointsList.push_back(stdPoint);
    
    auto rotateMat = glm::mat4(1);
    for(unsigned i = 1; i < POINT_NUM; i++) {
        float rad = 2.0f * M_PI * i / POINT_NUM;
        auto oneShotRot = rotateMat | rotate(rad, 0, 0, 1);
        auto newPoint = oneShotRot * stdPoint;
        pointsList.push_back(newPoint);
    }
    return pointsList;
}

auto& posFix(tuple& point) 
{
    point[0] += WIDTH / 2;
    point[1] -= HEIGHT / 2;
    return point;
}

void drawCanvas() 
{
    canvas cvs(WIDTH, HEIGHT);
    color clr(1, 1, 1);
    auto pointList = calcPointsPos();
    for (auto& point : pointList) {
        cvs.writePixel(point[0] + WIDTH / 2, point[1] + HEIGHT / 2, clr);
    }
    cvs.saveasPNG("chap4");;
}

int main() { drawCanvas(); }