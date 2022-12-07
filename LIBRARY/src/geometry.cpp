#include "XRaySimulator.hpp"

using namespace xrg;

Body::Body(const double x, const double y, const double z): centre_(x, y, z) { };

Ellipsoid::Ellipsoid(const double a, const double b, const double c, const double x, const double y, const double z):
    a_(a), b_(b), c_(c), Body(x, y, z)
    {
        // This MUST be an ellipsoid
        assert( (a_!=0) );
        assert( (b_!=0) );
        assert( (c_!=0) );
    }

double Ellipsoid::weakening(const double path_length) const
{
    return 0;
}

xru::QuadraticCoef* Ellipsoid::intersect_coefs(const xrt::XRay &ray) const
{
    // Assuming this is non-zero:
    auto divider = 1 / ((ray.direction_.dz/c_)*(ray.direction_.dz/c_) +
                        (ray.direction_.dy/b_)*(ray.direction_.dy/b_) +
                        (ray.direction_.dx/a_)*(ray.direction_.dx/a_));

    xru::QuadraticCoef* qc = new xru::QuadraticCoef();
    qc->q = ((xrt::XRay::source_.dz/c_)*(xrt::XRay::source_.dz/c_) +
             (xrt::XRay::source_.dy/b_)*(xrt::XRay::source_.dy/b_) + 
             (xrt::XRay::source_.dx/b_)*(xrt::XRay::source_.dx/b_) ) * divider;
    qc->phalf = ( (xrt::XRay::source_.dz*ray.direction_.dz/(c_*c_)) +
                  (xrt::XRay::source_.dy*ray.direction_.dy/(b_*b_)) +
                  (xrt::XRay::source_.dx*ray.direction_.dx/(a_*a_)) ) * divider;

    return qc;
}

Sphere::Sphere(const double r, const double x, const double y, const double z):
    r_(r), Body(x, y, z) { };

xru::QuadraticCoef* Sphere::intersect_coefs(const xrt::XRay &ray) const
{
    // Assume line's direction vector is normalized and non-zero
    auto delta = xrt::XRay::source_ - centre_;

    xru::QuadraticCoef* qc = new xru::QuadraticCoef();
    qc->q = delta.dot(delta) - r_*r_;
    qc->phalf = ray.direction_.dot(delta);

    return qc;
}

double Sphere::weakening(const double path_length) const
{
    return 0;
}


Cylinder::Cylinder(const double r, const double h, const double x, const double y, const double z): Body(x, y, z) { };

xru::QuadraticCoef* Cylinder::intersect_coefs(const xrt::XRay &ray) const { return nullptr; };
double Cylinder::weakening(const double path_length) const { return 0; };