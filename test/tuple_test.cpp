#include <tuple.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Tuple, PointConstruct) {
    tuple<double> t = {1.0, 2.1, 3.4, 1};
    EXPECT_EQ(t.x, 1.0);
    EXPECT_EQ(t.y, 2.1);
    EXPECT_EQ(t.z, 3.4);
    EXPECT_EQ(t.flag, 1);
}

TEST(Tuple, VectorConstruct) {
    tuple<double> t = {2.3, 3.4, 2.6, 0};
    EXPECT_EQ(t.x, 2.3);
    EXPECT_EQ(t.y, 3.4);
    EXPECT_EQ(t.z, 2.6);
    EXPECT_EQ(t.flag, 0);
}

TEST(Tuple, Factory) {
    auto point = pointFactory<double>(2.3, 3.4, 4.5);
    EXPECT_EQ(point.x, 2.3);
    EXPECT_EQ(point.y, 3.4);
    EXPECT_EQ(point.z, 4.5);
    EXPECT_EQ(point.flag, 1);
    auto vector = vectorFactory<double>(3.5, 1.2, 5.6);
    EXPECT_EQ(vector.x, 3.5);
    EXPECT_EQ(vector.y, 1.2);
    EXPECT_EQ(vector.z, 5.6);
    EXPECT_EQ(vector.flag, 0);
}

// TO DO; test for pointOrVector

TEST(Tuple, AddOp) {
    auto point = pointFactory<double>(1.1, 1.2, 1.3);
    auto vector = vectorFactory<double>(2.1, 2.2, 2.3);
    auto p = point + vector;
    auto v = vector + vector;
    // neither a point nor a vector
    auto er = point + point;
    EXPECT_TRUE(nearlyEqual<double>(p.x, 3.2));
    EXPECT_TRUE(nearlyEqual<double>(p.y, 3.4));
    EXPECT_TRUE(nearlyEqual<double>(p.z, 3.6));
    EXPECT_TRUE(p.flag == 1);
    EXPECT_TRUE(nearlyEqual<double>(v.x, 4.2));
    EXPECT_TRUE(nearlyEqual<double>(v.y, 4.4));
    EXPECT_TRUE(nearlyEqual<double>(v.z, 4.6));
    EXPECT_TRUE(v.flag == 0);
    EXPECT_TRUE(er.flag == 2);
    // +=
    vector += v;
    EXPECT_TRUE(nearlyEqual<double>(vector.x, 6.3));
    EXPECT_TRUE(nearlyEqual<double>(vector.y, 6.6));
    EXPECT_TRUE(nearlyEqual<double>(vector.z, 6.9));
    EXPECT_TRUE(vector.flag == 0);
}

TEST(Tuple, SubOp) {
    auto point = pointFactory<double>(1.1, 1.2, 1.3);
    auto vector = vectorFactory<double>(2.1, 2.2, 2.3);
    auto p = point - vector;
    auto v1 = vector - vector;
    auto v2 = point - point;
    // error : cannot interpret
    auto er = vector - point;
    EXPECT_TRUE(nearlyEqual<double>(p.x, -1.0f));
    EXPECT_TRUE(nearlyEqual<double>(p.y, -1.0f));
    EXPECT_TRUE(nearlyEqual<double>(p.z, -1.0f));
    EXPECT_TRUE(p.flag == 1);
    EXPECT_TRUE(nearlyEqual<double>(v1.x, 0.0f));
    EXPECT_TRUE(nearlyEqual<double>(v1.y, 0.0f));
    EXPECT_TRUE(nearlyEqual<double>(v1.z, 0.0f));
    EXPECT_TRUE(v1.flag == 0);
    EXPECT_TRUE(nearlyEqual<double>(v2.x, 0.0f));
    EXPECT_TRUE(nearlyEqual<double>(v2.y, 0.0f));
    EXPECT_TRUE(nearlyEqual<double>(v2.z, 0.0f));
    EXPECT_TRUE(v2.flag == 0);
    EXPECT_TRUE(er.flag != 0 && er.flag != 1);
    // -=
    point -= vector;
    EXPECT_TRUE(nearlyEqual<double>(point.x, -1.0));
    EXPECT_TRUE(nearlyEqual<double>(point.y, -1.0));
    EXPECT_TRUE(nearlyEqual<double>(point.z, -1.0));
    EXPECT_TRUE(point.flag == 1);
}

TEST(Tuple, MulOp) {
    auto point = pointFactory<double>(1.1, 1.2, 1.3);
    auto vector = vectorFactory<double>(2.1, 2.2, 2.3);
    decltype(point.x) factor = 0.5;
    auto p = point * factor;
    EXPECT_TRUE(nearlyEqual<double>(p.x, 0.55));
    EXPECT_TRUE(nearlyEqual<double>(p.y, 0.6));
    EXPECT_TRUE(nearlyEqual<double>(p.z, 0.65));
    EXPECT_TRUE(p.flag == 1);
    // *=
    vector *= factor;
    EXPECT_TRUE(nearlyEqual<double>(vector.x, 1.05));
    EXPECT_TRUE(nearlyEqual<double>(vector.y, 1.1));
    EXPECT_TRUE(nearlyEqual<double>(vector.z, 1.15));
    EXPECT_TRUE(vector.flag == 0);
}

TEST(Tuple, DivOp) {
    auto point = pointFactory<double>(1.1, 1.2, 1.3);
    auto vector = vectorFactory<double>(2.1, 2.2, 2.3);
    decltype(point.x) factor = 2.0f;
    auto p = point / factor;
    EXPECT_TRUE(nearlyEqual<double>(p.x, 0.55));
    EXPECT_TRUE(nearlyEqual<double>(p.y, 0.6));
    EXPECT_TRUE(nearlyEqual<double>(p.z, 0.65));
    EXPECT_TRUE(p.flag == 1);
    // /=
    vector /= factor;
    EXPECT_TRUE(nearlyEqual<double>(vector.x, 1.05));
    EXPECT_TRUE(nearlyEqual<double>(vector.y, 1.1));
    EXPECT_TRUE(nearlyEqual<double>(vector.z, 1.15));
    EXPECT_TRUE(vector.flag == 0);
}

TEST(Tuple, Magnitude) {
    auto vector = vectorFactory<double>(1, 2, 3);
    // auto point = pointFactory<double>(1, 2, 1);
    EXPECT_TRUE(nearlyEqual<double>(vector.magnitude(), std::sqrt(14)));
    // exception for points
}

TEST(Tuple, Equality) {
    auto vector = vectorFactory<double>(1.1, 1.2, 1.3);
    EXPECT_TRUE(vector == tuple<double>(1.1, 1.2, 1.3, 0));
    EXPECT_TRUE(vector != tuple<double>(0.2, 1.2, 3.4, 1));
}