#include <primitive.hpp>

using namespace renderer;

const glm::mat4& primitive::getInverse()
{
    if(!inverseCached) {
        inverseTrfm = std::move(glm::inverse(transform));
        inverseCached = true;
    }
    return inverseTrfm;
}

// world point : worldp, object point : objectp
tuple sphere::normalAt(const tuple& worldp)
{   
    // calculating 3x3 submatrix's inverse is more efficient
    auto objectp = this->getInverse() * worldp;
    auto objectn = objectp - origin;
    auto worldn = glm::transpose(this->getInverse()) * objectn;
    worldn[3] = 0;
    return glm::normalize(worldn);
}
