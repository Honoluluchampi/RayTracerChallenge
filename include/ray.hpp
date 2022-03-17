#pragma once

#include <glm_inc.hpp>
#include <tuple.hpp>
#include <primitive.hpp>
#include <vector>

namespace renderer {

struct ray
{
    tuple origin, direction;
    ray(const tuple& ori, const tuple& dir) : origin(ori), direction(dir) {}
    // returns r.origin + r.direction * t
    tuple proceed(const float& t)
    { return origin + direction * t; }
};

// intersecting points count and its list
struct intersectInfo
{
    unsigned count;
    std::vector<float> tList;
};

// calc intersecting points with a sphere
intersectInfo intersect(const ray& r, const sphere& sph); 

} // namespace renderer