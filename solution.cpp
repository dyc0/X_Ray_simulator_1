#include "XRaySimulator.hpp"

int main(int argc, const char* argv[])
{
    xrt::Detector* dt = xrt::Detector::create_detector(xru::Point3D(0, 7, 0), xru::Vector3D(0, -1, 0), xru::Vector3D(0, 0, 1));
    dt->populate_pixels(380, 380, 0.1, 0.1);
    xrl::Scene* sc = new xrl::Scene(xru::Point3D(0, -100, 0), dt);

    xrg::Body* ellipsoid = new xrg::Ellipsoid(30, 6, 30, 0, 0, 0);
    ellipsoid->set_material(xrc::materials::WATER);
    sc->add_body(ellipsoid);

    xrg::Body* sph1 = new xrg::Sphere(2, -12, -1, 5);
    sph1->set_material(xrc::materials::BLOOD);
    sc->add_body(sph1);

    xrg::Body* sph2 = new xrg::Sphere(3, -6, 0, -10);
    sph2->set_material(xrc::materials::MUSCLE);
    sc->add_body(sph2);

    xrg::Body* sph3 = new xrg::Sphere(3,  5,  1, 5);
    sph3->set_material(xrc::materials::BONE);
    sc->add_body(sph3);

    xrg::Body* cyl  = new xrg::Cylinder(2, 8, 0, 0, 0);
    cyl->set_material(xrc::materials::LUNG);
    sc->add_body(cyl);

    sc->generate_ray_field();
    sc->shoot_rays();
    sc->write_to_file("../HELPERS/results.txt");
}