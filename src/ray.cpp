#include <ray.hpp>
#include <memory>
#include <type_traits>
#include <utils.hpp>

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

bool ray::addItsc(const intersect& itsc)
{ 
    // check for hitting (and chage if its necessary) 
    itscList.push_back(itsc); 
    return checkHit(itsc);
}

// intersect with sphere
void ray::calcIntersect(sphere& sph)
{
    // get the inverse of the sph transform, and make new object-space ray 
    auto r = this->transform(glm::inverse(sph.transform));

    // discreminant
    auto sphere_to_ray = r.origin - sph.origin;
    float a = glm::dot(r.direction, r.direction), b = 2.0f * glm::dot(r.direction, sphere_to_ray),
        c = glm::dot(sphere_to_ray, sphere_to_ray) - sph.radius * sph.radius;
    float d = b * b - 4.0f * a * c;
    // even if d == 0 , return 2 point for now
    if(d >= 0) {
        // check hitting
        // could be dangerous in parallelization?
        intersect itscA((-b - std::sqrt(d)) / (2.0f * a), sph);
        this->addItsc(itscA);
        intersect itscB((-b + std::sqrt(d)) / (2.0f * a), sph);
        this->addItsc(itscB);
    }
}

