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

material mtrl{};
auto pos = pointFactory(0, 0, 0);

TEST(Shading, Lighting) {
    // lighting with the eye between the light and the surface
    auto eyev = vectorFactory(0, 0, -1);
    auto normv = vectorFactory(0, 0, -1);
    auto light = pointLight(pointFactory(0, 0, -10), color(1, 1, 1));
    auto res = lighting(mtrl, light, pos, eyev, normv);
    EXPECT_TRUE(res == color(1.9, 1.9, 1.9));

    // lighting with the eye between light and surface, eye offset 45'
    eyev = vectorFactory(0, std::sqrt(2)/2, -std::sqrt(2)/2);
    res = lighting(mtrl, light, pos, eyev, normv);
    EXPECT_TRUE(res == color(1.0, 1.0, 1.0));
    
    // lighting with eye opposite surface, light offset 45'
    eyev = vectorFactory(0, 0, -1);
    light = pointLight(pointFactory(0, 10, -10));
    res = lighting(mtrl, light, pos, eyev, normv);
    EXPECT_TRUE(res == color(0.7364, 0.7364, 0.7364));

    // lighting with eye inth path of the reflection vector
    eyev = vectorFactory(0, -std::sqrt(2)/2, -std::sqrt(2)/2);
    res = lighting(mtrl, light, pos, eyev, normv);
    EXPECT_TRUE(res == color(1.6364, 1.6364, 1.6364));

    // lighting with the light behing the surface
    eyev = vectorFactory(0, 0, -1);
    light = pointLight(pointFactory(0, 0, 10));
    res = lighting(mtrl, light, pos, eyev, normv);
    EXPECT_TRUE(res == color(0.1, 0.1, 0.1));
}