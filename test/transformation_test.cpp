#include <gtest/gtest.h>
#include <renderer.hpp>

using namespace renderer;

TEST(Transformation, Translation) {
    auto transform = translation_ctor(5, -3, 2);
    auto invTransform = transform.inverse();
    auto point = pointFactory(-3, 4, 5);
    auto vector = vectorFactory(-3, 4, 5);
    EXPECT_EQ(transform * point, pointFactory(2, 1, 7));
    EXPECT_EQ(invTransform * point, pointFactory(-8, 7, 3));
    EXPECT_EQ(transform * vector, vector);
}

TEST(Transformation, Scaling) {
    auto transform = scaling_ctor(2, 3, 4);
    auto invTransform = transform.inverse();
    auto point = pointFactory(-4, 6, 9);
    point[2] = 9;
    transform(3,2) = 0;
    auto vector = vectorFactory(-4, 6, 8);
    EXPECT_EQ(transform*point, pointFactory(-8, 18, 36));
    EXPECT_EQ(transform*vector, vectorFactory(-8, 18, 32));
    EXPECT_EQ(invTransform*vector, vectorFactory(-2, 2, 2));
    EXPECT_EQ(reflection_ctor(direction::x)*point, pointFactory(4, 6, 9));
}

TEST(Transformation, Rotation) {
    auto rotX = rotationX_ctor(M_PI_2);
    auto rotY = rotationY_ctor(M_PI / 4.0f);
    auto rotZ = rotationZ_ctor(M_PI / 4.0f);
    auto point1 = pointFactory(0, 1, 0);
    auto point2 = pointFactory(0, 0, 1);
    EXPECT_TRUE((rotX * point1).isApprox(pointFactory(0, 0, 1)));
    EXPECT_TRUE((rotY * point2).isApprox(pointFactory(sqrt(2)/2.0f, 0, sqrt(2)/2.0f)));
    EXPECT_TRUE((rotZ * point1).isApprox(pointFactory(-sqrt(2)/2.0f, sqrt(2)/2.0f, 0)));
}

TEST(Transformation, Shearing) {
    auto shear1 = shearing_ctor(1, 0, 0, 0, 0, 0);
    auto shear2 = shearing_ctor(0, 1, 0, 0, 0, 0);
    auto shear3 = shearing_ctor(0, 0, 1, 0, 0, 0);
    auto shear4 = shearing_ctor(0, 0, 0, 1, 0, 0);
    auto shear5 = shearing_ctor(0, 0, 0, 0, 1, 0);
    auto shear6 = shearing_ctor(0, 0, 0, 0, 0, 1);
    auto point = pointFactory(2, 3, 4);
    EXPECT_TRUE((shear1 * point).isApprox(pointFactory(5, 3, 4)));        
    EXPECT_TRUE((shear2 * point).isApprox(pointFactory(6, 3, 4)));    
    EXPECT_TRUE((shear3 * point).isApprox(pointFactory(2, 5, 4)));    
    EXPECT_TRUE((shear4 * point).isApprox(pointFactory(2, 7, 4)));    
    EXPECT_TRUE((shear5 * point).isApprox(pointFactory(2, 3, 6)));    
    EXPECT_TRUE((shear6 * point).isApprox(pointFactory(2, 3, 7)));    
}