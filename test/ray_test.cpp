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
    ray r(pointFactory(0, 0, -5), vectorFactory(0, 0, 1));
    sphere s(pointFactory(0, 0, 0), 1.0f);
    auto info = intersect(r, s);
    EXPECT_EQ(info.count, 2);
    EXPECT_FLOAT_EQ(info.tList[0], 6.0f);
    EXPECT_FLOAT_EQ(info.tList[1], 4.0f);
}