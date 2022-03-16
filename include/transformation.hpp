#pragma once
#include <eigen_inc.hpp>
#include <functional>

// all functions should be executed from left to right
// is it guaranteed by compiler...?

namespace renderer{
using Eigen::Matrix4d;
using Eigen::Vector4d;

enum class direction {x, y, z};

// for construct
Matrix4d translation_ctor(const double& x, const double& y, const double& z);
Matrix4d scaling_ctor(const double& x, const double& y, const double& z);
Matrix4d reflection_ctor(direction dir);
Matrix4d rotationX_ctor(const double& rad);
Matrix4d rotationY_ctor(const double& rad);
Matrix4d rotationZ_ctor(const double& rad);

// aP2b : a in proportion to b
Matrix4d shearing_ctor(const double& xP2y, const double& xP2z, const double& yP2x, const double& yP2z, const double& zP2x, const double& zP2y);
} // the end of the namespace renderere