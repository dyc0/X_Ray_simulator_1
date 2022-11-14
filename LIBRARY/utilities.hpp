#ifndef UTILITES_HPP
#define UTILITES_HPP

#include <math.h>

namespace xru
{

    struct Vector3D
    {
        double dx, dy, dz;

        Vector3D();
        Vector3D(const double x, const double y, const double z);

        Vector3D cross(const Vector3D &other) const;
        double dot(const Vector3D &other) const;
        double euclidian_distance(const Vector3D &other) const;

        Vector3D operator - (Vector3D const &other);

        static double abs(Vector3D const &vec);
    };
    
    // Alias vector as point
    using Point3D = Vector3D;


    // EQUATION SOLVING
    // (Taken from CERN's VecGeom Surface model branch.)

    ///< Second order equation coefficients, as in: <x * x + 2*phalf * x + q = 0>
    struct QuadraticCoef {
        double phalf{0}; // we don't need p itself when solving the equation, hence we store just p/2
        double q{0};     // we do need q
    };

    void QuadraticSolver(QuadraticCoef const &coef, double *roots, int &numroots);



}

#endif