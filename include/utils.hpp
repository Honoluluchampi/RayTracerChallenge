#pragma once
#include <math.h>
#include <glm_inc.hpp>
#include <iostream>

constexpr double EPSILON = 0.0001;

template <typename T>
inline bool nearlyEqual(const T& x, const T& y)
{ return std::abs(x-y) < EPSILON ? true :false; }

inline size_t pos2idx(const size_t x, const size_t y, const size_t width)
{ return x + y * width; }

inline void printMat(const glm::mat4& mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}