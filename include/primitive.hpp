#pragma once

#include <tuple.hpp>

namespace renderer {

static unsigned PRIMITIVE_ID = 0;

struct primitive
{
    // primitive type
    enum class pType {
        SPHERE
    };
    unsigned id = PRIMITIVE_ID++;
    pType type;
    primitive(pType t) : type(t) {}
    ~primitive() {}
};

struct sphere : public primitive
{
    tuple origin;
    float radius;
    sphere(const tuple& ori, const float& radi) : 
        primitive(pType::SPHERE), origin(ori), radius(radi) {}
};

}// namespace renderer