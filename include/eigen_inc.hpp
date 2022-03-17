// configure eigen in this file
// Eigen (doc : https://eigen.tuxfamily.org/index.php?title=Main_Page)
#pragma once

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/LU>