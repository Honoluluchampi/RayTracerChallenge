#pragma once
#include <math.h>
#include <iostream>

constexpr double EPSILON = 0.0001;

namespace renderer {

template <typename T>
struct tuple
{
    T x, y, z;
    // 1 indicates point, 0 indicates vector
    unsigned flag;
    tuple(T x_, T y_, T z_, unsigned f_) : x(x_), y(y_), z(z_), flag(f_) {}
    // the length of the vector
    T magnitude()
    {
        if(flag == 1) throw std::runtime_error("point doesnt have length.");
        else return std::sqrt(x*x + y*y + z*z);
    }
    tuple<T> normalize()
    {
        // exception for point normalization is thrown in magnitude();
        T mag = this->magnitude();
        x /= mag; y /= mag; z /= mag;
        return *this;
    }
};

// should be inline?
template <typename T> tuple<T> operator+ (const tuple<T>& lhs, const tuple<T>& rhs)
{ return tuple<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.flag + rhs.flag); }
template <typename T> tuple<T> operator- (const tuple<T>& lhs, const tuple<T>& rhs)
{ return tuple<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.flag - rhs.flag); }
template <typename T> tuple<T> operator* (const tuple<T>& lhs, const T& rhs)
{ return tuple<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.flag); }
template <typename T> tuple<T> operator/ (const tuple<T>& lhs, const T& rhs)
{ return tuple<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.flag); }
template <typename T> tuple<T>& operator+= (tuple<T>& lhs, const tuple<T>& rhs)
{ lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.flag += rhs.flag; return lhs; }
template <typename T> tuple<T>& operator-= (tuple<T>& lhs, const tuple<T>& rhs)
{ lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.flag -= rhs.flag; return lhs; }
template <typename T> tuple<T>& operator*= (tuple<T>& lhs, const T& rhs)
{ lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
template <typename T> tuple<T>& operator/= (tuple<T>& lhs, const T& rhs)
{ lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }

// for comparision
template <typename T>
bool nearlyEqual(T x, T y)
{
    if(std::abs(x-y) < EPSILON) return true;
    else return false;
}

template <typename T> bool operator== (const tuple<T>& lhs, const tuple<T>& rhs)
{ return (nearlyEqual<T>(lhs.x, rhs.x) && nearlyEqual<T>(lhs.y, rhs.y) && nearlyEqual<T>(lhs.z, rhs.z) && lhs.flag == rhs.flag); }
template <typename T> bool operator!= (const tuple<T>& lhs, const tuple<T>& rhs)
{ return !(lhs == rhs); }

template <typename T>
void pointOrVector(const tuple<T>& t)
{
    if(t.flag == 0) 
        std::cout << "this tuple is a point." << std::endl;
    else if(t.flag == 1)
        std::cout << "this tuple is a vector." << std::endl;
    else
        std::cout << "this is neither a point nor a vector." << std::endl;
}

template <typename T>
inline tuple<T> pointFactory(T x, T y, T z) { return tuple<T>(x, y, z, 1); }

template <typename T>
inline tuple<T> vectorFactory(T x, T y, T z) { return tuple<T>(x, y, z, 0); }

template <typename T>
void pointOrVector(const tuple<T>& t);

} // the end of the namespace