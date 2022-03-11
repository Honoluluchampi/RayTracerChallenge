#include <color.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Color, Construct){
    auto c = color(-0.5, 0.4, 1.7);
    EXPECT_EQ(c.red, -0.5);
    EXPECT_EQ(c.green, 0.4);
    EXPECT_EQ(c.blue, 1.7);
}

 TEST(Color, AddOp){
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = color(0.7, 0.1, 0.25);
    EXPECT_EQ(c1 + c2, color(1.6, 0.7, 1.0));
    c1 += c2;
    EXPECT_EQ(c1, color(1.6, 0.7, 1.0));
 }

 TEST(Color, SubOp){
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = color(0.7, 0.1, 0.25);
    EXPECT_EQ(c1 - c2, color(0.2, 0.5, 0.5));
    c1 -= c2;
    EXPECT_EQ(c1, color(0.2, 0.5, 0.5));
 }

 TEST(Color, MulOpByScalar){
    auto c1 = color(0.2, 0.3, 0.4);
    EXPECT_EQ(c1 * 2, color(0.4, 0.6, 0.8));
    c1 *= 2;
    EXPECT_EQ(c1, color(0.4, 0.6, 0.8));
 }

 TEST(Color, MulOpByColor){
    auto c1 = color(1, 0.2, 0.4);
    auto c2 = color(0.9, 1, 0.1);
    EXPECT_EQ(c1 * c2, color(0.9, 0.2, 0.04));
    c1 *= c2;
    EXPECT_EQ(c1, color(0.9, 0.2, 0.04));
 }

 TEST(Color, Equality){
    auto c1 = color(1, 0.2, 0.4);
    auto c2 = color(0.9, 1, 0.1);
    EXPECT_TRUE(c1 != c2);
    EXPECT_TRUE(c1 == color(0.5, 0.1, 0.2) * 2);
 }