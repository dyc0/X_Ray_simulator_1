#include "XRaySimulator.hpp"

using namespace xrl;

int main(int argc, const char* argv[])
{
    xrt::Detector* det = xrt::Detector::create_detector(xru::Point3D(4, 0, 0), xru::Vector3D(-1, 0, 0), xru::Vector3D(0, 0, 1));
    det->populate_pixels(380, 380, 1, 1);

    Scene* sc = new Scene(xru::Vector3D(0,0,0), det);

    xrg::Body* sph = new xrg::Sphere(0.5, 1.5, 0, 0);
    sph->set_material(xrc::materials::ADIPOSE);
    sc->add_body(sph);

    xrg::Body* cyl = new xrg::Cylinder(0.5, 2, 3, 0, 0);
    cyl->set_material(xrc::materials::LUNG);
    sc->add_body(cyl);

    xrg::Body* not_important = new xrg::Ellipsoid(1, 1, 1, -100, -100, -100);
    sc->add_body(not_important);

    xrg::Body* sph_outer = new xrg::Sphere(0.7, 1.5, 0, 0);
    sph_outer->set_material(xrc::materials::OVARY);
    sc->add_body(sph_outer);

    sc->generate_ray_field();

    sc->shoot_rays();
}