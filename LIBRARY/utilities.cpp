#include "XRaySimulator.hpp"

using namespace xru;

Vector3D::Vector3D(): dx(0), dy(0), dz(0) { };

Vector3D::Vector3D(const double x, const double y, const double z): dx(x), dy(y), dz(z) { };

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(dy*other.dz - dz*other.dy, dz*other.dx - dx*other.dz, dx*other.dy - dy*other.dx);
}

double Vector3D::dot(const Vector3D &other) const
{
    return dx*other.dx + dy*other.dy + dz*other.dz;
}

double Vector3D::euclidian_distance(const Vector3D &other) const
{
    double Dx = dx - other.dx;
    double Dy = dy - other.dy;
    double Dz = dz - other.dz;
    return std::sqrt(Dx*Dx + Dy*Dy + Dz*Dz);
}

Vector3D Vector3D::operator - (Vector3D const &other)
{
    return Vector3D(dx-other.dx, dy-other.dy, dz-other.dz); 
}

double Vector3D::abs(Vector3D const &vec)
{
    return sqrt(vec.dx*vec.dx + vec.dy*vec.dy + vec.dz*vec.dz);
}


void QuadraticSolver(QuadraticCoef const &coef, double *roots, int &numroots)
{
    // Numercal stability possibly a problem.
    numroots     = 0;
    double delta = coef.phalf * coef.phalf - coef.q;
    if (delta < double(0)) return;

    delta           = std::sqrt(delta);
    roots[numroots] = -coef.phalf - delta;
    numroots += (roots[numroots] > double(0));

    roots[numroots] = -coef.phalf + delta;
    numroots += (roots[numroots] > double(0));
}
