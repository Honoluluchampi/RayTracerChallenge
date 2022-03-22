#pragma once

#include <tuple.hpp>
#include <ray.hpp>
#include <shading_components.hpp>
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
    virtual ~primitive() {}

    // material getter setter
    const material& getMaterial() { return material_m; }
    void setMaterial(const material& mtrl) { material_m = mtrl; }
    void setMaterial(material&& mtrl) { material_m = std::move(mtrl); }

    // get surface normal
    virtual tuple normalAt(const tuple& point)=0;

    // getter for transform matrix
    inline const glm::mat4& getTransform()
    { return transform; }
    const glm::mat4& getInverse();
    inline void setTransform(const glm::mat4& mat) { transform = mat; inverseCached = false; }
    inline void setTransform(glm::mat4&& mat) { transform = std::move(mat); inverseCached = false; }
    
private:
    // transform func
    // for object space transform
    glm::mat4 transform = glm::mat4(1);
    // inverse transform 
    glm::mat4 inverseTrfm = glm::mat4(1);

    material material_m;
    // inverse trfm mat caching
    bool inverseCached = true;

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
    
    sphere(const tuple& ori = pointFactory(0, 0, 0), const float& radi = 1) : 
        primitive(pType::SPHERE), origin(ori), radius(radi) {}
    ~sphere() {}

    // get surface normal
    tuple normalAt(const tuple& point) override;
};

}// namespace renderer