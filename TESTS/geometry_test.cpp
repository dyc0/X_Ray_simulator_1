#include "XRaySimulator.hpp"

using namespace xrg;

void test_intersect(xrt::XRay* ray, Body* body, int exp_numroots, double* expected_roots)
{
    double intersections[2] = {0, 0};
    int numint = 0;

    body->intersect(*ray, intersections, numint);
    std::cout << std::endl << *body << std::endl;
    std::cout << "There are " << numint << " intersections, at " << intersections[0] << " and " << intersections[1] << std::endl;

    if (numint != exp_numroots) throw -1;
    else
        switch (numint)
        {
            case 2: if (abs(intersections[1] - expected_roots[1]) > xrc::tolerance) throw -2;
            case 1: if (abs(intersections[0] - expected_roots[0]) > xrc::tolerance) throw -3;
        }
}

int main(int argc, const char* argv[])
{
    try
    {
       Body* sph = new Sphere(1, 2, 0, 0);
        Body* sph_behind = new Sphere(1, -2, 0, 0);
        Body* ell = new Ellipsoid(2.5,2,2, 4.5,0,0);
        Body* ell_behind = new Ellipsoid(2.5,2,2, -4.5,0,0);

        xru::Point3D o = xru::Point3D(0, 0, 0);
        xru::Vector3D d = xru::Vector3D(1, 0, 0);
        d.norm();
        xrt::XRay* xrx = new xrt::XRay(d);
        xrt::XRay::set_source(o);

        Body* bodies[] = {sph, sph_behind, ell, ell_behind};
        int exp_numroots[] = {2, 0, 2, 0};
        double exp_roots[][2] = {{1,3}, {0,0}, {2,7}, {0,0}};

        std::cout << std::endl;
        std::cout << "\n\t------------------------------\n\tTESTING SPHERES AND ELLIPSOIDS\n\t------------------------------\n\n";
        std::cout << "----Using ray: " << xrx->direction_ << "----" << std::endl;

        for (int i = 0; i < 4; i++)
            test_intersect(xrx, bodies[i], exp_numroots[i], exp_roots[i]);
        std::cout << std::endl;

        Body* cyl = new Cylinder(1,2, 2,0,0);
        Body* cyl_z = new Cylinder(1,2, 0,0,2);
        Body* cyl_behind = new Cylinder(1,2, 0,0,-2);
        xrt::XRay* xrz = new xrt::XRay(xru::Vector3D(0,0,1));

        double exp_roots_cyl[2];

        std::cout << std::endl;
        std::cout << "\n\t-----------------\n\tTESTING CYLINDERS\n\t-----------------\n\n";
        
        std::cout << "----Using ray: " << xrx->direction_ << "----" << std::endl;
        exp_roots_cyl[0] = 1;
        exp_roots_cyl[1] = 3;
        test_intersect(xrx, cyl, 2, exp_roots_cyl);
        std::cout << std::endl;

        std::cout << "----Using ray: " << xrz->direction_ << "----" << std::endl;
        exp_roots_cyl[0] = 1;
        exp_roots_cyl[1] = 3;
        test_intersect(xrz, cyl_z, 2, exp_roots_cyl);

        exp_roots_cyl[0] = 1;
        exp_roots_cyl[1] = 3;
        test_intersect(xrz, cyl_behind, 0, exp_roots_cyl);
        std::cout << std::endl;

        xrt::XRay* xr_angle = new xrt::XRay(xru::Vector3D(0.5, 0, 1));
        std::cout << "----Using ray: " << xr_angle->direction_ << "----" << std::endl;
        exp_roots_cyl[0] = 1;
        exp_roots_cyl[1] = 2;
        test_intersect(xr_angle, cyl_z, 2, exp_roots_cyl);
        std::cout << std::endl;

        return 0;
    }
    catch(int e)
    {
        std::cerr << "ERROR: " << e << '\n';
        return e;
    }
    
    
}