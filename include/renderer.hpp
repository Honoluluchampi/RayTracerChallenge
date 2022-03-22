#pragma once

// eigen or glm
#ifdef RENDERER_INCLUDE_EIGEN
    #include <eigen_inc.hpp>
#else
    #include <glm/glm.hpp>
#endif

#include <canvas.hpp>
#include <color.hpp>
#include <tuple.hpp>
#include <transformation.hpp>
#include <ray.hpp>
#include <primitive.hpp>
#include <shading_components.hpp>