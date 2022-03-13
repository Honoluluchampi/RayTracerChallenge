#define EIGEN_NO_DEBUG
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY
#include <eigen3/Eigen/Core>

namespace renderer
{
    using namespace Eigen;
    using tuple = Vector4d;
    inline tuple pointFactory(const double& x, const double& y, const double& z)
    { return tuple(x,y,z,1); }
    inline tuple vectorFactory(const double&x, const double& y, const double& z)
    { return tuple(x,y,z,0); }
    inline tuple cross(const tuple& a, const tuple& b)
    { 
        if (a[3] != 0 || b[3] != 0) throw std::runtime_error("argument is not a vector."); 
        // can be parallelized?
        return tuple(a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0], 0);
    }
} // the end of the namesapce renderer