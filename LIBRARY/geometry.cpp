#include "XRaySimulator.hpp"

using namespace xrg;

Body::Body(const double x, const double y, const double z): x_(x), y_(y), z_(z) { };

Ellipsoid::Ellipsoid(const double a, const double b, const double c, const double x, const double y, const double z):
    a_(a), b_(b), c_(c), Body(x, y, z) { };

xru::QuadraticCoef* Ellipsoid::intersect_coefs(xrt::XRay &ray) const
{

}