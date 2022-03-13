#include <tuple.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Tuple, PointConstruct) {
    tuple t = {1.0, 2.1, 3.4, 1};
    EXPECT_EQ(t[0], 1.0);
    EXPECT_EQ(t[1], 2.1);
    EXPECT_EQ(t[2], 3.4);
    EXPECT_EQ(t[3], 1);
}

TEST(Tuple, VectorConstruct) {
    tuple t = {2.3, 3.4, 2.6, 0};
    EXPECT_EQ(t[0], 2.3);
    EXPECT_EQ(t[1], 3.4);
    EXPECT_EQ(t[2], 2.6);
    EXPECT_EQ(t[3], 0);
}

TEST(Tuple, Factory) {
    auto point = pointFactory(2.3, 3.4, 4.5);
    EXPECT_DOUBLE_EQ(point[0], 2.3);
    EXPECT_DOUBLE_EQ(point[1], 3.4);
    EXPECT_DOUBLE_EQ(point[2], 4.5);
    EXPECT_DOUBLE_EQ(point[3], 1);
    auto vector = vectorFactory(3.5, 1.2, 5.6);
    EXPECT_DOUBLE_EQ(vector[0], 3.5);
    EXPECT_DOUBLE_EQ(vector[1], 1.2);
    EXPECT_DOUBLE_EQ(vector[2], 5.6);
    EXPECT_DOUBLE_EQ(vector[3], 0);
}

// TO DO; test for pointOrVector

TEST(Tuple, AddOp) {
    auto point = pointFactory(1.1, 1.2, 1.3);
    auto vector = vectorFactory(2.1, 2.2, 2.3);
    auto p = point + vector;
    auto v = vector + vector;
    // neither a point nor a vector
    auto er = point + point;
    EXPECT_DOUBLE_EQ(p[0], 3.2);
    EXPECT_DOUBLE_EQ(p[1], 3.4);
    EXPECT_DOUBLE_EQ(p[2], 3.6);
    EXPECT_TRUE(p[3] == 1);
    EXPECT_DOUBLE_EQ(v[0], 4.2);
    EXPECT_DOUBLE_EQ(v[1], 4.4);
    EXPECT_DOUBLE_EQ(v[2], 4.6);
    EXPECT_TRUE(v[3] == 0);
    EXPECT_TRUE(er[3] == 2);
    // +=
    vector += v;
    EXPECT_DOUBLE_EQ(vector[0], 6.3);
    EXPECT_DOUBLE_EQ(vector[1], 6.6);
    EXPECT_DOUBLE_EQ(vector[2], 6.9);
    EXPECT_TRUE(vector[3] == 0);
}

TEST(Tuple, SubOp) {
    auto point = pointFactory(1.1, 1.2, 1.3);
    auto vector = vectorFactory(2.1, 2.2, 2.3);
    auto p = point - vector;
    auto v1 = vector - vector;
    auto v2 = point - point;
    // error : cannot interpret
    auto er = vector - point;
    EXPECT_DOUBLE_EQ(p[0], -1.0f);
    EXPECT_DOUBLE_EQ(p[1], -1.0f);
    EXPECT_DOUBLE_EQ(p[2], -1.0f);
    EXPECT_TRUE(p[3] == 1);
    EXPECT_DOUBLE_EQ(v1[0], 0.0f);
    EXPECT_DOUBLE_EQ(v1[1], 0.0f);
    EXPECT_DOUBLE_EQ(v1[2], 0.0f);
    EXPECT_TRUE(v1[3] == 0);
    EXPECT_DOUBLE_EQ(v2[0], 0.0f);
    EXPECT_DOUBLE_EQ(v2[1], 0.0f);
    EXPECT_DOUBLE_EQ(v2[2], 0.0f);
    EXPECT_TRUE(v2[3] == 0);
    EXPECT_TRUE(er[3] != 0 && er[3] != 1);
    // -=
    point -= vector;
    EXPECT_DOUBLE_EQ(point[0], -1.0);
    EXPECT_DOUBLE_EQ(point[1], -1.0);
    EXPECT_DOUBLE_EQ(point[2], -1.0);
    EXPECT_TRUE(point[3] == 1);
}

TEST(Tuple, MulOp) {
    auto point = pointFactory(1.1, 1.2, 1.3);
    auto vector = vectorFactory(2.1, 2.2, 2.3);
    double factor = 0.5;
    auto p = point * factor;
    EXPECT_DOUBLE_EQ(p[0], 0.55);
    EXPECT_DOUBLE_EQ(p[1], 0.6);
    EXPECT_DOUBLE_EQ(p[2], 0.65);
    EXPECT_DOUBLE_EQ(p[3], 0.5);
    // *=
    vector *= factor;
    EXPECT_DOUBLE_EQ(vector[0], 1.05);
    EXPECT_DOUBLE_EQ(vector[1], 1.1);
    EXPECT_DOUBLE_EQ(vector[2], 1.15);
    EXPECT_TRUE(vector[3] == 0);
}

TEST(Tuple, DivOp) {
    auto point = pointFactory(1.1, 1.2, 1.3);
    auto vector = vectorFactory(2.1, 2.2, 2.3);
    double factor = 2.0f;
    auto p = point / factor;
    EXPECT_DOUBLE_EQ(p[0], 0.55);
    EXPECT_DOUBLE_EQ(p[1], 0.6);
    EXPECT_DOUBLE_EQ(p[2], 0.65);
    EXPECT_DOUBLE_EQ(p[3], 0.5);
    // /=
    vector /= factor;
    EXPECT_DOUBLE_EQ(vector[0], 1.05);
    EXPECT_DOUBLE_EQ(vector[1], 1.1);
    EXPECT_DOUBLE_EQ(vector[2], 1.15);
    EXPECT_TRUE(vector[3] == 0);
}

TEST(Tuple, Magnitude) {
    auto vector = vectorFactory(1, 2, 3);
    // auto point = pointFactory(1, 2, 1);
    EXPECT_DOUBLE_EQ(vector.norm(), std::sqrt(14));
    // exception for points
}

TEST(Tuple, Equality) {
    auto vector = vectorFactory(1.1, 1.2, 1.3);
    EXPECT_TRUE(vector == tuple(1.1, 1.2, 1.3, 0));
    EXPECT_TRUE(vector != tuple(0.2, 1.2, 3.4, 1));
}

TEST(Tuple, Normalization) {
    using std::sqrt;
    auto vector = vectorFactory(4, 0, 0);
    vector.normalize();
    EXPECT_TRUE(vector == vectorFactory(1, 0, 0));
    vector = vectorFactory(1, 2, 3);
    vector.normalize();
    EXPECT_TRUE(vector == vectorFactory(1.0f/sqrt(14), 2.0f/sqrt(14), 3.0f/sqrt(14)));
}

TEST(Tuple, DotProduct) {
    auto a = vectorFactory(1, 2, 3);
    auto b = vectorFactory(2, 3, 4);
    EXPECT_EQ(a.dot(b), 20);
}

TEST(Tuple, CrossProduct) {
    auto a = vectorFactory(1, 2, 3);
    auto b = vectorFactory(2, 3, 4);
    EXPECT_TRUE(cross(a,b) == vectorFactory(-1, 2, -1));
    EXPECT_TRUE(cross(b,a) == vectorFactory(1, -2, 1));
}