#pragma once

#include <color.hpp>
#include <tuple.hpp>

namespace renderer{

// point light
struct pointLight
{
    tuple position_m;
    color intensity_m;
    
    pointLight(const tuple& pos, const color& itst = color(1,1,1)) : position_m(pos), intensity_m(itst) {}
    pointLight(tuple&& pos, color&& itst = color(1,1,1)) : position_m(std::move(pos)), intensity_m(std::move(itst)) {}
};

struct material
{
    color color_m;
    // for each kind of reflection of Phong algorithm
    float ambient_m; // 0 ~ 1
    float diffuse_m; // 0 ~ 1
    float specular_m; // 0 ~ 1
    float shininess_m; // 10 ~ 200
    material(const color& col = color(1,1,1), float amb = 0.1, float dif = 0.9, float scl = 0.9, float shns = 100) 
        : color_m(col), ambient_m(amb), diffuse_m(dif), specular_m(scl), shininess_m(shns) {}
};

inline bool operator== (const material& lhs, const material& rhs) 
{ return (lhs.color_m==rhs.color_m) && (lhs.ambient_m==rhs.ambient_m) && (lhs.diffuse_m==rhs.diffuse_m) && 
    (lhs.specular_m==rhs.specular_m) && (lhs.shininess_m==rhs.shininess_m); }

color lighting(const material& mtrl, const pointLight& light, const tuple& point, const tuple& eyev, const tuple& normalv);
} // namespace renderer