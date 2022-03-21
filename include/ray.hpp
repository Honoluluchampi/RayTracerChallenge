#pragma once

#include <glm_inc.hpp>
#include <tuple.hpp>
#include <primitive.hpp>
#include <vector>
#include <optional>
#include <limits>
#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace renderer {

struct primitive;
struct sphere;

struct intersect
{
    float t;
    // pointer for a primitive
    // boost::intrusive_ptr<primitive> pPrmt;
    primitive* pPrmt; // should be safer...
    intersect(const float t_, primitive& prmt_) : t(t_), pPrmt(&prmt_) {}
    intersect(const float t_, primitive&& prmt_) : t(t_), pPrmt(&prmt_) {}
};

struct ray
{
    tuple origin, direction;
    // intersectiong object list;
    std::vector<intersect> itscList;

    ray() {}
    ray(const tuple& ori, const tuple& dir) : origin(ori), direction(dir) {}
    ray(const ray& r) = default;

    // returns r.origin + r.direction * t
    inline tuple proceed(const float& t)
    { return origin + direction * t; }
    // check weather this ray hits a given inst
    bool checkHit(const intersect& inst);
    // adding intersection
    bool addItsc(const intersect& itsc);

    // getter
    // get hitting object and its t
    inline const std::optional<intersect>& hit() const
    { return hittingItsc; }
    inline size_t itscCount()
    { return itscList.size(); }

    // calc intersecting points with a sphere
    void calcIntersect(sphere& sph); 

    // transform
    ray transform(const glm::mat4& mat)
    { return {mat * this->origin, mat * this->direction}; } 
private:
    // initialized as an invalid intersect
    std::optional<intersect> hittingItsc = std::nullopt;
};

} // namespace renderer