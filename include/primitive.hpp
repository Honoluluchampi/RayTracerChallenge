#pragma once

#include <tuple.hpp>

namespace renderer {

struct sphere 
{
    tuple origin;
    float radius;
    sphere(const tuple& ori, const float& radi) : origin(ori), radius(radi) {}
};

}// namespace renderer