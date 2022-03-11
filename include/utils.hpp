#pragma once
#include <math.h>

constexpr double EPSILON = 0.00001;

template <typename T>
bool nearlyEqual(const T& x, const T& y)
{
    if(std::abs(x-y) < EPSILON) return true;
    else return false;
}
