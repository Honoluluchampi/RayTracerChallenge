#pragma once

#include <glm_inc.hpp>
#include <tuple.hpp>
#include <primitive.hpp>
#include <vector>
#include <optional>

namespace renderer {

struct intersect
{
    float t;
    const primitive& prmt;
    intersect(const float t_, const primitive& prmt_) : t(t_), prmt(prmt_) {}
};

struct ray
{
    tuple origin, direction;
    // intersectiong object list;
    std::vector<intersect> itscList;
    ray(const tuple& ori, const tuple& dir) : origin(ori), direction(dir) {}
    // returns r.origin + r.direction * t
    inline tuple proceed(const float& t)
    { return origin + direction * t; }
    // check weather this ray intersects with a given inst
    inline bool checkHit(const intersect& inst)
    { return (inst.t >= 0 && hittingItsc->t > inst.t); }
    // get hitting object and its t
    inline intersect hit() const
    { return hittingItsc.value(); }
    // calc intersecting points with a sphere
    void calcIntersect(const ray& r, const sphere& sph); 
private:
    // initialize as an invalid intersect
    std::optional<intersect> hittingItsc = std::nullopt;
};

} // namespace renderer