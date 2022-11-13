#ifndef UTILITES_HPP
#define UTILITES_HPP

#include <math.h>

namespace xru
{

    // Number can be float, double, or some data type for GPU (WIP).
    template <typename Real_t>
    struct Vector3D
    {
        Real_t dx, dy, dz;

        Vector3D(): dx(0), dy(0), dz(0) { };
        Vector3D(const Real_t x, const Real_t y, const Real_t z): dx(x), dy(y), dz(z) { };

        Vector3D cross(const Vector3D<Real_t> &other) const
        {
            return Vector3D(dy*other.dz - dz*other.dy, dz*other.dx - dx*other.dz, dx*other.dy - dy*other.dx);
        }

        Real_t dot(const Vector3D<Real_t> &other) const
        {
            return dx*other.dx + dy*other.dy + dz*other.dz;
        }

        Real_t euclidian_distance(const Vector3D<Real_t> &other) const
        {
            return std::sqrt(std::pow((dx-other.dx), 2) + 
                            std::pow((dy-other.dy), 2) + 
                            std::pow((dz-other.dz), 2));
        }

        Vector3D operator - (Vector3D<Real_t> const &other)
        {
            return Vector3D<Real_t>(dx-other.dx, dy-other.dy, dz-other.dz); 
        }
    };
    
    // Alias vector as point
    template <typename Real_t>
    using Point3D = Vector3D<Real_t>;


    // EQUATION SOLVING
    // (Taken from CERN's VecGeom Surface model branch.)

    ///< Second order equation coefficients, as in: <x * x + 2*phalf * x + q = 0>
    template <typename Real_t>
    struct QuadraticCoef {
        Real_t phalf{0}; // we don't need p itself when solving the equation, hence we store just p/2
        Real_t q{0};     // we do need q
    };

    template <typename Real_t>
    void QuadraticSolver(QuadraticCoef<Real_t> const &coef, Real_t *roots, int &numroots)
    {
        // Numercal stability possibly a problem.
        numroots     = 0;
        Real_t delta = coef.phalf * coef.phalf - coef.q;
        if (delta < Real_t(0)) return;

        delta           = std::sqrt(delta);
        roots[numroots] = -coef.phalf - delta;
        numroots += (roots[numroots] > Real_t(0));

        roots[numroots] = -coef.phalf + delta;
        numroots += (roots[numroots] > Real_t(0));
    }



}

#endif