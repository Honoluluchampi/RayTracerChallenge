#pragma once

#include <tuple.hpp>
#include <ray.hpp>
#include <functional>
#include <glm_inc.hpp>

namespace renderer {

static unsigned PRIMITIVE_ID = 0;

struct primitive
{
    // primitive type
    enum class pType {
        SPHERE
    };
    unsigned id = PRIMITIVE_ID++;
    pType type;
    primitive(pType t) : type(t), refCount(0) {}
    ~primitive() {}

    // transform func
    std::function<glm::mat4(glm::mat4&)> transform;
    
private:
    // for intrusive pointer
    int refCount;
    void add_ref() { ++refCount; }
    void release() { if(--refCount == 0) delete this; }
    friend void intrusive_ptr_add_ref(primitive* prmt);
    friend void intrusive_ptr_release(primitive* prmt);
};

inline void intrusive_ptr_add_ref(primitive* prmt) { prmt->add_ref(); }
inline void intrusive_ptr_release(primitive* prmt) { prmt->release(); }

struct sphere : public primitive
{
    tuple origin;
    float radius;
    glm::mat4 transform = glm::mat4(1); 
    sphere(const tuple& ori = pointFactory(0, 0, 0), const float& radi = 1) : 
        primitive(pType::SPHERE), origin(ori), radius(radi) {}
    
    // for object space transform
    inline void setTransform(const glm::mat4& mat) { transform = mat; }
    inline void setTransform(glm::mat4&& mat) { transform = std::move(mat); }
};

}// namespace renderer