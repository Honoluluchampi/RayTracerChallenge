#pragma once
#include <glm_inc.hpp>
#include <functional>

// all functions should be executed from left to right
// is it guaranteed by compiler...?

namespace renderer{
using glm::mat4x4;
using glm::vec4;

enum class direction {x, y, z};

// for construct
mat4x4 translation_ctor(const double& x, const double& y, const double& z);
mat4x4 scaling_ctor(const double& x, const double& y, const double& z);
mat4x4 reflection_ctor(direction dir);
mat4x4 rotationX_ctor(const double& rad);
mat4x4 rotationY_ctor(const double& rad);
mat4x4 rotationZ_ctor(const double& rad);

// aP2b : a in proportion to b
mat4x4 shearing_ctor(const double& xP2y, const double& xP2z, const double& yP2x, const double& yP2z, const double& zP2x, const double& zP2y);
} // the end of the namespace renderere