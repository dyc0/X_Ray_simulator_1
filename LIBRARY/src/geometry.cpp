#include "XRaySimulator.hpp"
#include "geometry.hpp"

using namespace xrg;

Body::Body(const double x, const double y, const double z, int material): centre_(x, y, z), material_(material) { };

xru::QuadraticCoef *xrg::Body::intersect_coefs(const xrt::XRay &ray) const
{
    return nullptr;
}

void xrg::Body::set_material(const int material)
{
    material_ = material;
}

Ellipsoid::Ellipsoid(const double a, const double b, const double c, const double x, const double y, const double z) : a_(a), b_(b), c_(c), Body(x, y, z)
{
    // This MUST be an ellipsoid
    assert((a_ != 0));
    assert((b_ != 0));
    assert((c_ != 0));
}

void xrg::Ellipsoid::intersect(const xrt::XRay &ray, double *intersections, int& numintersections) const
{
    xru::QuadraticCoef* qc = intersect_coefs(ray);
    xru::QuadraticSolver(*qc, intersections, numintersections);
}

xru::QuadraticCoef *Ellipsoid::intersect_coefs(const xrt::XRay &ray) const
{
    // Assuming this is non-zero:
    auto divider = 1 / ((ray.direction_.dz/c_)*(ray.direction_.dz/c_) +
                        (ray.direction_.dy/b_)*(ray.direction_.dy/b_) +
                        (ray.direction_.dx/a_)*(ray.direction_.dx/a_));

    xru::QuadraticCoef* qc = new xru::QuadraticCoef();
    qc->q = ( (xrt::XRay::source_.dz - centre_.dz)*(xrt::XRay::source_.dz - centre_.dz) / (c_*c_) +
              (xrt::XRay::source_.dy - centre_.dy)*(xrt::XRay::source_.dy - centre_.dy) / (b_*b_) +
              (xrt::XRay::source_.dx - centre_.dx)*(xrt::XRay::source_.dx - centre_.dx) / (a_*a_) -
              1 )* divider;
    qc->phalf = ( ((xrt::XRay::source_.dz-centre_.dz)*ray.direction_.dz/(c_*c_)) +
                  ((xrt::XRay::source_.dy-centre_.dy)*ray.direction_.dy/(b_*b_)) +
                  ((xrt::XRay::source_.dx-centre_.dx)*ray.direction_.dx/(a_*a_)) ) * divider;

    return qc;
}

Sphere::Sphere(const double r, const double x, const double y, const double z):
    r_(r), Body(x, y, z) { };

void xrg::Sphere::intersect(const xrt::XRay &ray, double *intersections, int& numintersections) const
{
    xru::QuadraticCoef* qc = intersect_coefs(ray);
    xru::QuadraticSolver(*qc, intersections, numintersections);
}

xru::QuadraticCoef *Sphere::intersect_coefs(const xrt::XRay &ray) const
{
    // Assume line's direction vector is normalized and non-zero
    auto delta = xrt::XRay::source_ - centre_;

    xru::QuadraticCoef* qc = new xru::QuadraticCoef();
    qc->q = delta.dot(delta) - r_*r_;
    qc->phalf = ray.direction_.dot(delta);

    return qc;
}

Cylinder::Cylinder(const double r, const double h, const double x, const double y, const double z): Body(x, y, z), h_(h), r_(r) { };

void xrg::Cylinder::intersect(const xrt::XRay &ray, double *intersections, int& numintersections) const
{
    // Cylinders are always along z-axis, so we need to check circle intersection, and z-bounds.
    xru::QuadraticCoef* qc = intersect_coefs(ray);
    int numroots;
    double roots[2];
    xru::QuadraticSolver(*qc, roots, numroots);

    numintersections = 0;
    for(; numroots>0; numroots--)
        if ((ray.direction_.dz*roots[numroots] + xrt::XRay::source_.dz > - h_*0.5 - xrc::tolerance) &&
            (ray.direction_.dz*roots[numroots] + xrt::XRay::source_.dz <   h_*0.5 + xrc::tolerance))
            {
                intersections[numintersections] = roots[numintersections];
                numintersections++;
            }
        
}

xru::QuadraticCoef *Cylinder::intersect_coefs(const xrt::XRay &ray) const
{
    // Cylinder is always along z-axis, so this is checking circle
    xru::Vector3D ray_projection = xru::Vector3D(ray.direction_.dx, ray.direction_.dy, 0);
    xru::QuadraticCoef* qc = new xru::QuadraticCoef();

    double divider = ray_projection.dot(ray_projection);
    divider = 1/divider;

    qc->phalf = (ray_projection.dot(xrt::XRay::source_) - ray_projection.dot(centre_)) * divider;
    qc->q = ((xrt::XRay::source_.dx - centre_.dx) * (xrt::XRay::source_.dx - centre_.dx) + 
             (xrt::XRay::source_.dy - centre_.dy) * (xrt::XRay::source_.dy - centre_.dy)
             - r_*r_) * divider;

    return qc;
}