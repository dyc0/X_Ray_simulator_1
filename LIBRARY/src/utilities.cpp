#include "XRaySimulator.hpp"

namespace xru {

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
        return abs(*this-other);
    }

    Vector3D Vector3D::operator - (Vector3D const &other) const
    {
        return Vector3D(dx-other.dx, dy-other.dy, dz-other.dz); 
    }

    Vector3D Vector3D::normed() const
    {
        double A = Vector3D::abs(*this);
        if (A <= 0) return Vector3D();
        A = 1/A;
        return Vector3D(dx * A, dy * A, dz * A);
    }

    void Vector3D::norm()
    {
        double A = Vector3D::abs(*this);
        if (A <= 0) return;
        A = 1/A;
        dx = dx * A;
        dy = dy * A;
        dz = dz * A;
    }

    double Vector3D::abs(Vector3D const &vec)
    {
        return std::sqrt(vec.dot(vec));
    }

    std::ostream& operator<<(std::ostream& os, const Vector3D& obj)
    {
        os << "(" << obj.dx << ", " << obj.dy << ", " << obj.dz << ")";
        return os;
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

}