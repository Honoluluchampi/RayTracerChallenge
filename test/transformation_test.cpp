#include <gtest/gtest.h>
#include <renderer.hpp>

using namespace renderer;

TEST(Transformation, Translation) {
    glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(5, -3, 2));
    auto invTransform = glm::inverse(transform);
    auto point = pointFactory(-3, 4, 5);
    auto vector = vectorFactory(-3, 4, 5);
    EXPECT_EQ(transform * point, pointFactory(2, 1, 7));
    EXPECT_EQ(invTransform * point, pointFactory(-8, 7, 3));
    EXPECT_EQ(transform * vector, vector);
}

TEST(Transformation, Scaling) {
    glm::mat4 transform = glm::scale(glm::mat4(1), glm::vec3(2, 3, 4));
    auto invTransform = glm::inverse(transform);
    auto point = pointFactory(-4, 6, 9);
    auto vector = vectorFactory(-4, 6, 8);
    EXPECT_EQ(transform*point, pointFactory(-8, 18, 36));
    EXPECT_EQ(transform*vector, vectorFactory(-8, 18, 32));
    EXPECT_EQ(invTransform*vector, vectorFactory(-2, 2, 2));
    EXPECT_EQ(glm::reflect(point, glm::vec4(1, 0, 0, 0)), pointFactory(4, 6, 9));
}

TEST(Transformation, Rotation) {
    glm::mat4 rotX = glm::rotate(glm::mat4(1), M_PI_2f32, glm::vec3(1, 0, 0));
    auto rotY = glm::rotate(glm::mat4(1), M_PI_2f32, glm::vec3(0, 0, 1));
    auto rotZ = glm::rotate(glm::mat4(1), M_PI_2f32, glm::vec3(0, 1, 1));
    auto point1 = pointFactory(0, 1,0);
    auto point2 = pointFactory(0, 0, 1);
    EXPECT_TRUE(rotX * point1 == pointFactory(0, 0, 1));
    EXPECT_TRUE(rotY * point2 == pointFactory(sqrt(2)/2.0f, 0, sqrt(2)/2.0f));
    EXPECT_TRUE(rotZ * point1 == pointFactory(-sqrt(2)/2.0f, sqrt(2)/2.0f, 0));
}

TEST(Transformation, Shearing) {
    auto shear1 = glm::shearX3D(glm::mat4(1), 1.0f, 0.0f);
    auto shear2 = glm::shearX3D(glm::mat4(1), 0.0f, 1.0f);
    auto shear3 = glm::shearY3D(glm::mat4(1), 1.0f, 0.0f);
    auto shear4 = glm::shearY3D(glm::mat4(1), 0.0f, 1.0f);
    auto shear5 = glm::shearZ3D(glm::mat4(1), 1.0f, 0.0f);
    auto shear6 = glm::shearZ3D(glm::mat4(1), 0.0f, 1.0f);
    auto point = pointFactory(2, 3, 4);
    EXPECT_TRUE(shear1 * point == pointFactory(5, 3, 4));        
    EXPECT_TRUE(shear2 * point == pointFactory(6, 3, 4));    
    EXPECT_TRUE(shear3 * point == pointFactory(2, 5, 4));    
    EXPECT_TRUE(shear4 * point == pointFactory(2, 7, 4));    
    EXPECT_TRUE(shear5 * point == pointFactory(2, 3, 6));    
    EXPECT_TRUE(shear6 * point == pointFactory(2, 3, 7));    
}

TEST(Transformation, Chaining) {
    auto point = pointFactory(1, 0, 1);
    // pipeline
    glm::mat4 A = glm::mat4(1) 
        | rotate(M_PI_2f32, 1, 0, 0)
        | scale(5, 5, 5)
        | translate(10, 5, 7);
    EXPECT_TRUE(A * point == pointFactory(15, 0, 7));
}