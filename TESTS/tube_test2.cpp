#include "XRaySimulator.hpp"
#include <fstream>

using namespace xrt;

int main(int argc, char* argv[])
{
    xrt::XRay* ray = new xrt::XRay(xru::Vector3D(1, 0, 0));

    std::cout << "First weakening: " << std::endl;
    ray->weaken(1000, xrc::materials::BONE);
    for (int i = 0; i < xrc::spectrum.size(); i++)
    {
        if (abs(xrc::spectrum[i] - ray->spectrum[i]) > xrc::tolerance)
            std::cout << xrc::spectrum[i] - ray->spectrum[i] << ", ";
    }

    ray->weaken(1000, xrc::materials::LUNG);
    std::cout << "Second weakening: " << std::endl;
    for (int i = 0; i < xrc::spectrum.size(); i++)
    {
        if (abs(xrc::spectrum[i] - ray->spectrum[i]) > xrc::tolerance)
            std::cout << xrc::spectrum[i] - ray->spectrum[i] << ", ";
    }
}