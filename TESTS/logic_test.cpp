#include "XRaySimulator.hpp"

using namespace xrl;

int main(int argc, const char* argv[])
{
    xrt::Detector* det = xrt::Detector::create_detector(xru::Point3D(10, 0, 0), xru::Vector3D(-1, 0, 0), xru::Vector3D(0, 0, 1));
    det->populate_pixels(100, 100, 0.1, 0.1);

    Scene* sc = new Scene(xru::Vector3D(0,0,0), det);

    xrg::Body* cyl = new xrg::Cylinder(0.5, 3, 8, 0, 0);
    cyl->set_material(xrc::materials::LENS);
    sc->add_body(cyl);

    xrg::Body* sph = new xrg::Sphere(0.5, 7, 2, 0);
    sph->set_material(xrc::materials::BONE);
    sc->add_body(sph);

    xrg::Body* sph_2 = new xrg::Sphere(0.5, 5, 1, 0);
    sph_2->set_material(xrc::materials::ADIPOSE);
    sc->add_body(sph_2);

    sc->generate_ray_field();

    sc->shoot_rays();

    sc->write_to_file("../../HELPERS/results.txt");
}