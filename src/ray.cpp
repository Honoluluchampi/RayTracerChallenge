#include <ray.hpp>

using namespace renderer;

intersectInfo renderer::intersect(const ray& r, const sphere& sph)
{
    intersectInfo info;
    // https://risalc.info/src/sphere-line-intersection.html 
    tuple x0 = r.origin, m = r.direction, a = sph.origin;
    float rad = sph.radius;    
    // discreminant
    auto dot = glm::dot(m, x0-a);
    float d = std::pow(dot, 2) - (glm::length2(x0 - a) - rad*rad);
    // even if d == 0 , return 2 point for now
    if(d >= 0) {
        info.count = 2;
        info.tList.push_back(-dot + std::sqrt(d));
        info.tList.push_back(-dot - std::sqrt(d));
    }
    else info.count = 0;
    return info;
}