#pragma once

#include <tuple.hpp>
#include <ray.hpp>

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
    sphere(const tuple& ori, const float& radi) : 
        primitive(pType::SPHERE), origin(ori), radius(radi) {}
};

}// namespace renderer