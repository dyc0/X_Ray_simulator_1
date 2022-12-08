#include "XRaySimulator.hpp"

using namespace xrg;

int main(int argc, const char* argv[])
{
    Body* sph = new Sphere(1, 2, 0, 0);
    Body* ell = new Ellipsoid(2.5,2,2, 4.5,0,0);
    Body* cyl = new Cylinder(1,2, 2,0,0);

    xru::Point3D o = xru::Point3D(0, 0, 0);
    xru::Vector3D d = xru::Vector3D(1, 0, 0);
    d.norm();
    xrt::XRay* xr = new xrt::XRay(d);
    xrt::XRay::set_source(o);

    Body* bodies[] = {sph, ell, cyl};

    double intersections[2];
    int numint;

    for (auto body: bodies)
    {
        intersections[0] = 0;
        intersections[1] = 0;
        numint = 0;

        body->intersect(*xr, intersections, numint);
        std::cout << intersections[0] << "," << intersections[1] << std::endl;
    }
}