#include <color.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Color, Construct){
    auto c = color(-0.5, 0.4, 1.7);
    EXPECT_EQ(c.red, -0.5);
    EXPECT_EQ(c.green, 0.4);
    EXPECT_EQ(c.blue, 1.7);
}