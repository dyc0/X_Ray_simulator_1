#include "XRaySimulator.hpp"
#include "geometry.hpp"

using namespace xrg;

Body::Body(const double x, const double y, const double z, int material): centre_(x, y, z), material_(material) { };

xru::QuadraticCoef *xrg::Body::intersect_coefs(const xrt::XRay &ray) const
{
    return nullptr;
}

void xrg::Body::print(std::ostream &where) const
{
    where << "Body at " << centre_ << ", with material " << material_;
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

void xrg::Ellipsoid::print(std::ostream &where) const
{
    where << "Ellipsoid at " << centre_ << " with half-axes " << a_ << ", " << b_ << " and " << c_
          << " and material " << material_;
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

void xrg::Sphere::print(std::ostream &where) const
{
    where << "Sphere at " << centre_ << " with radius " << r_
          << " and material " << material_;
}

Cylinder::Cylinder(const double r, const double h, const double x, const double y, const double z): Body(x, y, z), h_(h), r_(r) { };

void xrg::Cylinder::intersect(const xrt::XRay &ray, double *intersections, int& numintersections) const
{
    bool intersects_planar_face = false;
    enum {UPPER = 1, LOWER = -1};

    numintersections = 0;

    // Cylinders are always along z-axis, so we need to check circle intersection, and z-bounds.
    xru::QuadraticCoef* qc = intersect_coefs(ray);
    int numroots;
    double roots[2];
    xru::QuadraticSolver(*qc, roots, numroots);

    for(int i = 0; i < numroots; i++)
        if ((ray.direction_.dz*roots[i] + xrt::XRay::source_.dz > centre_.dz - h_*0.5 - xrc::tolerance) &&
            (ray.direction_.dz*roots[i] + xrt::XRay::source_.dz < centre_.dz + h_*0.5 + xrc::tolerance))
            {
                intersections[i] = roots[i];
                numintersections++;
            }

    intersects_planar_face = planar_face_intersect(ray, intersections, numintersections, UPPER);
    intersects_planar_face = planar_face_intersect(ray, intersections, numintersections, LOWER) || intersects_planar_face;

    if (intersects_planar_face && numintersections == 2 && intersections[0] > intersections[1])
    {
        intersections[0] = intersections[0] + intersections[1];
        intersections[1] = intersections[0] - intersections[1];
        intersections[0] = intersections[0] - intersections[1];
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

bool xrg::Cylinder::planar_face_intersect(const xrt::XRay &ray, double *intersections, int &numintersections, const int side) const
{
    xru::Vector3D face_normal = xru::Vector3D(0, 0, 1) * side;
    xru::Vector3D face_centre = xru::Vector3D(0, 0, h_*0.5) * side + centre_;

    double d = (face_centre - xrt::XRay::source_).dot(face_normal) / ray.direction_.dot(face_normal);
    if (d < 0) return false;

    if ((ray.direction_*d - face_centre).dot(ray.direction_*d - face_centre) < r_*r_)
    {
        intersections[numintersections] = d;
        numintersections++;
        return true;
    }

    return false;
}

void xrg::Cylinder::print(std::ostream &where) const
{
    where << "Cylinder at " << centre_ << " with radius " << r_ << " and height " << h_
          << " and material " << material_;
}

std::ostream &xrg::operator<<(std::ostream &out, const Body &o)
{
    o.print(out);
    return out;
}
