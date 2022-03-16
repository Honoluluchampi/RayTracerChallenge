#include <transformation.hpp>
#include <cmath>
#include <iostream>
#include <utils.hpp>

using namespace renderer;
using Eigen::Matrix4d;
using std::sin; using std::cos;


Matrix4d renderer::translation_ctor(const double& x, const double& y, const double& z)
{
    Matrix4d mat;
    mat << 1, 0, 0, x,
           0, 1, 0, y,
           0, 0, 1, z,
           0, 0, 0, 1;
    return mat;
}

Matrix4d renderer::scaling_ctor(const double& x, const double& y, const double& z)
{
    Matrix4d mat;
    mat << x, 0, 0, 0,
           0, y, 0, 0,
           0, 0, z, 0,
           0, 0, 0, 1;
    return mat;
}

Matrix4d renderer::reflection_ctor(direction dir)
{
    switch(dir) {
        case direction::x : return scaling_ctor(-1, 1, 1);
        case direction::y : return scaling_ctor(1, -1, 1);
        case direction::z : return scaling_ctor(1, 1, -1);
        default : throw std::runtime_error("invalid argument : reflection");
    }
}

Matrix4d renderer::rotationX_ctor(const double& rad) 
{
    Matrix4d mat;
    mat << 1, 0, 0, 0,
           0, cos(rad), -sin(rad), 0,
           0, sin(rad), cos(rad), 0,
           0, 0, 0, 1;
    return mat;
}

Matrix4d renderer::rotationY_ctor(const double& rad) 
{
    Matrix4d mat;
    mat << cos(rad), 0, sin(rad), 0,
           0, 1, 0, 0,
           -sin(rad), 0, cos(rad), 0,
           0, 0, 0, 1;
    return mat;
}

Matrix4d renderer::rotationZ_ctor(const double& rad) 
{
    Matrix4d mat;
    mat << cos(rad), -sin(rad), 0, 0,
           sin(rad), cos(rad), 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1;
    return mat;
}

Matrix4d renderer::shearing_ctor(const double& xP2y, const double& xP2z, const double& yP2x, const double& yP2z, const double& zP2x, const double& zP2y)
{
    Matrix4d mat;
    mat << 1, xP2y, xP2z, 0,
           yP2x, 1, yP2z, 0,
           zP2x, zP2y, 1, 0,
           0, 0, 0, 1;
    return mat;
}