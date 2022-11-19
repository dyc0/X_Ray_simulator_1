#include "XRaySimulator.hpp"

using namespace xrt;

XRay::XRay(xru::Point3D& o, xru::Vector3D& d)
{
    o_ = o;
    d_ = d;
}