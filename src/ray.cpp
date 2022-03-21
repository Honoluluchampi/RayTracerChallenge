#include <ray.hpp>
#include <memory>
#include <type_traits>

using namespace renderer;

bool ray::checkHit(const intersect& inst)
{ 
    // first object, or nearer object
    if(inst.t >= 0 && (!hittingItsc || hittingItsc.value().t > inst.t)) {
        // update the hitting itsc
        hittingItsc = inst;
        return true;
    }
    else return false;    
}

bool ray::add(const intersect& itsc)
{ 
    // check for hitting (and chage if its necessary) 
    itscList.push_back(itsc); 
    return checkHit(itsc);
}

// intersect with sphere
void ray::calcIntersect(sphere& sph)
{
    // https://risalc.info/src/sphere-line-intersection.html 
    const tuple& x0 = origin, m = direction, a = sph.origin;
    float rad = sph.radius;    
    // discreminant
    auto dot = glm::dot(m, x0-a);
    float d = std::pow(dot, 2) - (glm::length2(x0 - a) - rad*rad);
    // even if d == 0 , return 2 point for now
    if(d >= 0) {
        // check hitting
        // dangerous for parallelization?
        intersect a(-dot - std::sqrt(d), sph);
        this->add(a);
        intersect b(-dot + std::sqrt(d), sph);
        this->add(b);
    }
}

