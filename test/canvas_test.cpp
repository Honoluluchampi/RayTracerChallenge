#include <canvas.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(Canvas, CanvasConstruction){
    auto cvs = canvas(10, 20);
    EXPECT_EQ(cvs.width, 10);
    EXPECT_EQ(cvs.height, 20);
    for(size_t x = 0; x < 10; x++)
        for(size_t y = 0; y < 20; y++)
            EXPECT_TRUE(cvs.readPixel(x, y) == color(0,0,0));
}

TEST(Canvas, ReadWrite){
    auto cvs = canvas(10, 20);
    cvs.writePixel(2,3,color(0.5,0.5,0.5));
    EXPECT_EQ(cvs.readPixel(2,3), color(0.5,0.5,0.5));
}