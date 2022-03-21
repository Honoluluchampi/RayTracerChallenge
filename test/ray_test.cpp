#include <renderer.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Ray, Construction) {
    auto origin = pointFactory(1, 2, 3);
    auto direction = vectorFactory(4, 5, 6);
    ray r(origin, direction);
    EXPECT_EQ(r.origin, origin);
    EXPECT_EQ(r.direction, direction);
}

TEST(Ray, Proceed) {
    ray r(pointFactory(2, 3, 4), vectorFactory(1, 0, 0));
    EXPECT_EQ(r.proceed(0), pointFactory(2, 3, 4));
    EXPECT_EQ(r.proceed(1), pointFactory(3, 3, 4));
    EXPECT_EQ(r.proceed(-1), pointFactory(1, 3, 4));
    EXPECT_EQ(r.proceed(2.5), pointFactory(4.5, 3, 4));
}

TEST(Ray, Intersection) {
    // intersect with two points
    ray r(pointFactory(0, 0, -5), vectorFactory(0, 0, 1));
    sphere s(pointFactory(0, 0, 0), 1.0f);
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 2);
    EXPECT_FLOAT_EQ(r.itscList[0].t, 4.0f);
    EXPECT_FLOAT_EQ(r.itscList[1].t, 6.0f);
    EXPECT_FLOAT_EQ(r.hit().value().t, 4.0f);
    // no hitting itsc
    r = ray(pointFactory(0, 0, 5), vectorFactory(0, 0, 1));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 2);
    EXPECT_FLOAT_EQ(r.itscList[0].t, -6.0f);
    EXPECT_FLOAT_EQ(r.itscList[1].t, -4.0f);
    EXPECT_FALSE(r.hit());
    // intersect with one point (return two points)
    r = ray(pointFactory(0, 1, -5), vectorFactory(0, 0, 1));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 2);
    EXPECT_FLOAT_EQ(r.itscList[0].t, 5.0f);
    EXPECT_FLOAT_EQ(r.itscList[1].t, 5.0f);
    EXPECT_FLOAT_EQ(r.hit().value().t, 5.0f);
    // no intersection
    r = ray(pointFactory(0, 2, -5), vectorFactory(0, 0, 1));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 0);
    EXPECT_FALSE(r.hit());
    // begin from the inside of sphere
    r = ray(pointFactory(0, 0, 0), vectorFactory(0, 0, 1));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 2);
    EXPECT_FLOAT_EQ(r.itscList[0].t, -1.0f);
    EXPECT_FLOAT_EQ(r.itscList[1].t, 1.0f);
    EXPECT_FLOAT_EQ(r.hit().value().t, 1.0f);
}

TEST(Ray, Tranfrom) {
    // translation
    ray r {pointFactory(1, 2, 3), vectorFactory(0, 1, 0)};
    glm::mat4 a = glm::translate(glm::vec3(3, 4, 5));
    auto r2 = r.transform(a);
    EXPECT_EQ(r2.origin, pointFactory(4, 6, 8));
    EXPECT_EQ(r2.direction, vectorFactory(0, 1, 0));
    // scaling
    a = glm::scale(glm::vec3(2, 3, 4));
    r2 = r.transform(a);
    EXPECT_EQ(r2.origin, pointFactory(2, 6, 12));
    EXPECT_EQ(r2.direction, vectorFactory(0, 3, 0));
}    

TEST(Ray, appliedTransform) {
    // sphere transform
    ray r(pointFactory(0, 0, -5), vectorFactory(0, 0, 1));
    sphere s;
    s.setTransform(glm::scale(glm::vec3(2, 2, 2)));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 2);
    EXPECT_FLOAT_EQ(r.hit().value().t, 3.0f);
    EXPECT_FLOAT_EQ(r.itscList[1].t, 7.0f);

    r = ray(pointFactory(0, 0, -5), vectorFactory(0, 0, 1));
    s.setTransform(glm::translate(glm::vec3(5, 0, 0)));
    r.calcIntersect(s);
    EXPECT_EQ(r.itscCount(), 0);
}