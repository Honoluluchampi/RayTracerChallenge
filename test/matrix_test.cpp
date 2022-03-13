// no original cpp file

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY
#include <eigen3/Eigen/Core>
#include <gtest/gtest.h>

using namespace Eigen;

TEST(Matrix, Construction) {
    Matrix4d mat;
    mat <<  1.0 , 2.0 , 3.0 , 4.0 ,
            5.5 , 6.5 , 7.5 , 8.5 ,
            9.0 , 10.0, 11.0, 12.0,
            13.5, 14.5, 15.5, 16.5;
    EXPECT_EQ(mat(0,0), 1);
    EXPECT_EQ(mat(0,3), 4);
    EXPECT_EQ(mat(1,0), 5.5);
    EXPECT_EQ(mat(1,2), 7.5);
    EXPECT_EQ(mat(2,2), 11);
    EXPECT_EQ(mat(3,0), 13.5);
    EXPECT_EQ(mat(3,2), 15.5);
}

TEST(Matrix, 2x2) {
    Matrix2d mat;
    mat <<  -3, 5,
             1,-2;
    EXPECT_EQ(mat(0,0), -3);
    EXPECT_EQ(mat(0,1), 5);
    EXPECT_EQ(mat(1,0), 1);
    EXPECT_EQ(mat(1,1), -2);
}

TEST(Matrix, 3x3) {
    Matrix3d mat;
    mat << -3, 5, 0,
            1,-2,-7,
            0, 1, 1;
    EXPECT_EQ(mat(0,0), -3);
    EXPECT_EQ(mat(1,1), -2);
    EXPECT_EQ(mat(2,2), 1);
}