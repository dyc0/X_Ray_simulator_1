#include "XRaySimulator.hpp"

int main(int argc, int argv[]) {

    xru::Vector3D v, p;
    v = xru::Vector3D(1, 1, 1);
    xrt::XRay xr = xrt::XRay(v);

    std::cout << "Value in ray spectrum: " << xr.spectrum[60.0] << std::endl;
    std::cout << "Value in generated spectrum: " << xrc::spectrum.at(60.0) << std::endl;

}
