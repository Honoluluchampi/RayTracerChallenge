#include <gtest/gtest.h>
#include <renderer.hpp>

using namespace renderer;

TEST(Shading, Construct) {
    // point light 
    auto light = pointLight(pointFactory(0, 0, 0));
    EXPECT_TRUE(light.position_m == pointFactory(0, 0, 0));
    EXPECT_TRUE(light.intensity_m == color(1, 1, 1));
    // material
    auto mtrl = material();
    EXPECT_TRUE(mtrl.color_m == color(1, 1, 1));
    EXPECT_FLOAT_EQ(mtrl.ambient_m, 0.1f);
    EXPECT_FLOAT_EQ(mtrl.diffuse_m, 0.9f);
    EXPECT_FLOAT_EQ(mtrl.diffuse_m, 0.9f);
    EXPECT_FLOAT_EQ(mtrl.specular_m, 0.9f);
    EXPECT_FLOAT_EQ(mtrl.shininess_m, 100);
    // sphere material
    sphere sph{};
    EXPECT_TRUE(sph.getMaterial() == mtrl);
    mtrl.ambient_m = 1;
    sph.setMaterial(mtrl);
    EXPECT_TRUE(sph.getMaterial() == mtrl);
}