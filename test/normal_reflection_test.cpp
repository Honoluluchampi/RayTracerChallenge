#include <renderer.hpp>
#include <gtest/gtest.h>

using namespace renderer;

TEST(NormalnReflection, Normal) {
    sphere sph{};
    auto n = sph.normalAt(pointFactory(1, 0, 0));
    EXPECT_EQ(n, vectorFactory(1, 0, 0));
    auto m = sph.normalAt(pointFactory(1, 1, 1));
    float v = std::sqrt(3)/3.0f;
    EXPECT_EQ(m, vectorFactory(v, v, v));
    // normal on a translated sphere
    sph.setTransform(glm::translate(glm::vec3(0, 1, 0)));
    n = sph.normalAt(pointFactory(0, 1.70711, -0.70711));
    EXPECT_EQ(n, vectorFactory(0, 0.70710683, -0.70710677));
    // EXPECT_FLOAT_EQ(n[0], 0);
    // EXPECT_FLOAT_EQ(n[1], 0.70710999);
    // EXPECT_FLOAT_EQ(n[2], -0.70710999);
    // EXPECT_EQ(n[3], 0);

    // transform sphere
    auto mat = glm::mat4(1) 
            | scale(1, 0.5, 1)
            | rotate(M_PI_2f32 / 5.0f, 0, 0, 1);
    sph.setTransform(std::move(mat));
    n = sph.normalAt(pointFactory(0, std::sqrt(2)/2.0f, -std::sqrt(2)/2.0f));
    // numerical error
    EXPECT_EQ(n, vectorFactory(1.0222112e-8, 0.97014254, -0.24253562));
    // EXPECT_FLOAT_EQ(n[1], 0.97014);
    // EXPECT_FLOAT_EQ(n[2], -0.24254);
    // EXPECT_EQ(n[3], 0);
}