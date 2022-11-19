#include "XRaySimulator.hpp"

using namespace xrl;

double Navigator::intersect(const xrt::XRay &ray, const xrg::Sphere& sph) const
{
    xru::QuadraticCoef* qc = sph.intersect_coefs(ray);
    int numroots = 0;
    double roots[2];
    xru::QuadraticSolver(*qc, roots, numroots);

    if (numroots == 0) return 0;
    else if (numroots == 1) return roots[0];
    else return roots[1] - roots[0];
}

double Navigator::intersect(const xrt::XRay &ray, const xrg::Ellipsoid& ell) const
{
    xru::QuadraticCoef* qc = ell.intersect_coefs(ray);
    int numroots = 0;
    double roots[2];
    xru::QuadraticSolver(*qc, roots, numroots);

    if (numroots == 0) return 0;
    else if (numroots == 1) return roots[0];
    else return roots[1] - roots[0];
}