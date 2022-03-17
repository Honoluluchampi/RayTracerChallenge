#pragma once

// all functions should be executed from left to right
// is it guaranteed by compiler...?

#ifndef RENDERER_INCLUDE_EIGEN

    #include <glm_inc.hpp>
    #include <vector>
    #include <utility>
    #include <functional>
    
    namespace renderer {
        // syntax sugar
        // write rad first
        inline auto rotateX(const float rad, glm::mat4 mat = glm::mat4(1)) 
        { return glm::rotate(mat, rad, glm::vec3(1, 0, 0)); }
        inline auto rotateY(const float rad, glm::mat4 mat = glm::mat4(1)) 
        { return glm::rotate(mat, rad, glm::vec3(0, 1, 0)); }
        inline auto rotateZ(const float rad, glm::mat4 mat = glm::mat4(1)) 
        { return glm::rotate(mat, rad, glm::vec3(0, 0, 1)); }
        
        // pipeline
        // ex : auto mat = translate(1, 3, 5) | scale(2, 3, 2) | rotateX(M_PI2f32);
        // translate -> scale -> rotate;

        std::function<glm::mat4(glm::mat4&)> translate(const float x, const float y, const float z)
        { return [=](glm::mat4& mat){ return glm::translate(mat, glm::vec3(x, y, z)); }; };

        std::function<glm::mat4(glm::mat4&)> scale(const float x, const float y, const float z)
        { return [=](glm::mat4& mat){ return glm::scale(mat, glm::vec3(x, y, z)); }; }     

        std::function<glm::mat4(glm::mat4&)> rotate(const float rad, const float x, const float y, const float z)
        { return [=](glm::mat4& mat){ return glm::rotate(mat, rad, glm::vec3(x, y, z)); }; }

        // aP2b : a in proportion to b
        std::function<glm::mat4(glm::mat4&)> shearX(const float xP2y, const float xP2z)
        { return [=](glm::mat4& mat){ return glm::shearX3D(mat, xP2y, xP2z); }; }
        std::function<glm::mat4(glm::mat4&)> shearY(const float yP2x, const float yP2z)
        { return [=](glm::mat4& mat){ return glm::shearY3D(mat, yP2x, yP2z); }; }
        std::function<glm::mat4(glm::mat4&)> shearZ(const float zP2x, const float zP2y)
        { return [=](glm::mat4& mat){ return glm::shearZ3D(mat, zP2x, zP2y); }; }

        // perfect forward is prefered ...
        auto operator| (glm::mat4& mat, const std::function<glm::mat4(glm::mat4&)>& func)
        { return func(mat); }
        auto operator| (glm::mat4&& mat, const std::function<glm::mat4(glm::mat4&)>& func)
        { return func(mat); }
    } // namespace renderer

#else

    #include <eigen_inc.hpp>

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
    
#endif