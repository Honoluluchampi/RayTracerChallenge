#include <ray.hpp>

using namespace renderer;

// intersect with sphere
void ray::calcIntersect(const ray& r, const sphere& sph)
{
    // https://risalc.info/src/sphere-line-intersection.html 
    const tuple& x0 = r.origin, m = r.direction, a = sph.origin;
    float rad = sph.radius;    
    // discreminant
    auto dot = glm::dot(m, x0-a);
    float d = std::pow(dot, 2) - (glm::length2(x0 - a) - rad*rad);
    // even if d == 0 , return 2 point for now
    if(d >= 0) {
        intersect inst(-dot - std::sqrt(d), sph);
        itscList.push_back(inst);
        itscList.emplace_back(-dot + std::sqrt(d), sph);
    }
}

