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

TEST(Matrix, Equality) {
    Matrix4d A, B, C;
    A << 1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2;
    B << 1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2;
    EXPECT_EQ(A, B);
    C << 2, 3, 4, 5,
         6, 7, 8, 9,
         8, 7, 6, 5,
         4, 3, 2, 1;
    EXPECT_TRUE(A != C);
}

TEST(Matrix, Multiplication) {
    Matrix4d A, B, C;
    A << 1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2;
    B << -2,  1,  2,  3,
          3,  2,  1, -1,
          4,  3,  6,  5,
          1,  2,  7,  8;
    C <<  20,  22,  50,  48,
          44,  54, 114, 108,
          40,  58, 110, 102,
          16,  26,  46,  42;
    EXPECT_EQ(A * B, C);
    Matrix4d D;
    Vector4d v, ans(18, 24, 33, 1);
    D << 1, 2, 3, 4,
         2, 4, 4, 2,
         8, 6, 4, 1,
         0, 0, 0, 1;
    v << 1, 2, 3, 1;
    EXPECT_EQ(D * v, ans);
}

TEST(Matrix, Identity) {
    Matrix4d A, E = Matrix4d::Identity();
    A << 0, 1, 2, 3,
         3, 4, 5, 4,
         9, 8, 4, 7,
         2, 4, 1, 9;
    EXPECT_EQ(A * E, A);
    EXPECT_EQ(E * A, A);
}

TEST(Matrix, Transpose) {
    Matrix4d A, B;
    A << 0, 1, 2, 3,
         3, 4, 5, 4,
         9, 8, 4, 7,
         2, 4, 1, 9;
    B << 0, 3, 9, 2,
         1, 4, 8, 4, 
         2, 5, 4, 1,
         3, 4, 7, 9;
    EXPECT_EQ(A.transpose(), B);
    EXPECT_EQ(Matrix4d::Identity().transpose(), Matrix4d::Identity());
}