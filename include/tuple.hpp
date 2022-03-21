#pragma once

#ifndef RENDERER_INCLUDE_EIGEN


    #include <glm_inc.hpp>
    #include <math.h>
    #include <iostream>
    #include <utils.hpp>

    namespace renderer
    {
        using tuple = glm::vec4;
        
        inline tuple pointFactory(const float& x, const float& y, const float& z)
        { return tuple(x, y, z, 1); }
        inline tuple vectorFactory(const float& x, const float& y, const float& z)
        { return tuple(x, y, z, 0); }
        inline tuple cross(const tuple& a, const tuple& b)
        { 
            if (a[3] != 0 || b[3] != 0) throw std::runtime_error("argument is not a vector."); 
            // can be parallelized?
            return tuple(a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0], 0);
        }
        inline bool operator== (const tuple& lhs, const tuple& rhs)
        { return nearlyEqual(lhs[0], rhs[0]), nearlyEqual(lhs[1], rhs[1]), nearlyEqual(lhs[2], rhs[2]), nearlyEqual(lhs[3], rhs[3]); }
    } // namespace renderer

#else

    #include <eigen_inc.hpp>

    namespace renderer
    {
        using namespace Eigen;
        using tuple = Vector4d;
        inline tuple pointFactory(const double& x, const double& y, const double& z)
        { return tuple(x,y,z,1); }
        inline tuple vectorFactory(const double&x, const double& y, const double& z)
        { return tuple(x,y,z,0); }
        inline tuple cross(const tuple& a, const tuple& b)
        { 
            if (a[3] != 0 || b[3] != 0) throw std::runtime_error("argument is not a vector."); 
            // can be parallelized?
            return tuple(a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0], 0);
        }
    } // the end of the namesapce renderer

#endif