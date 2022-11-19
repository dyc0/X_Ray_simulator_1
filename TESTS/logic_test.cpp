#include "XRaySimulator.hpp"

int main(int argc, const char* argv[])
{
    xrl::Navigator* n = new xrl::Navigator();
    xrg::Sphere* sph = new xrg::Sphere(1, 1,1,1);
    xru::Point3D o = xru::Point3D(0, 0, 0);
    xru::Vector3D d = xru::Vector3D(-1, -1, -1);
    d.norm();
    xrt::XRay* xr = new xrt::XRay(o, d);

    double length = n->intersect(*xr, *sph);
    std::cout << length << std::endl;
}