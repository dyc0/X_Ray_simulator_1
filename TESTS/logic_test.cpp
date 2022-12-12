#include "XRaySimulator.hpp"

using namespace xrl;

int main(int argc, const char* argv[])
{
    xrt::Detector* det = xrt::Detector::create_detector(xru::Point3D(10, 0, 0), xru::Vector3D(-1, 0, 0), xru::Vector3D(0, 0, 1));
    det->populate_pixels(100, 100, 0.1, 0.1);

    Scene* sc = new Scene(xru::Vector3D(0,0,0), det);
    /**
    xrg::Body* cyl = new xrg::Cylinder(0.5, 3, 8, 0, 0);
    cyl->set_material(xrc::materials::LENS);
    sc->add_body(cyl);

    xrg::Body* sph = new xrg::Sphere(0.5, 7, 2, 0);
    sph->set_material(xrc::materials::BONE);
    sc->add_body(sph);

    xrg::Body* sph_2 = new xrg::Sphere(0.5, 5, 1, 0);
    sph_2->set_material(xrc::materials::ADIPOSE);
    sc->add_body(sph_2);
    **/

    xrg::Body* sph = new xrg::Sphere(4.5, 5, 0, 0);
    sph->set_material(xrc::materials::LUNG);
    sc->add_body(sph);

    xrg::Body* sph2 = new xrg::Sphere(3.5, 5, 0, 0);
    sph2->set_material(xrc::materials::ADIPOSE);
    sc->add_body(sph2);

    xrg::Body* sph3 = new xrg::Sphere(.5, 5, 0, 0);
    sph3->set_material(xrc::materials::BONE);
    sc->add_body(sph3);

    xrg::Body* sph4 = new xrg::Sphere(2.5, 5, 0, 0);
    sph4->set_material(xrc::materials::BREAST);
    sc->add_body(sph4);

    sc->generate_ray_field();

    sc->shoot_rays();

    sc->write_to_file("../../HELPERS/results.txt");
}