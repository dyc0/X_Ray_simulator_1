#include "XRaySimulator.hpp"
#include <iostream>

using namespace xru;

int main(int argc, const char* argv[])
{   
    std::cout << "TESTING" << std::endl;

    std::cout << "Testing constructors" << std::endl;
    Vector3D a;
    Vector3D b(1, 0, 0);
    Vector3D c(0, 1, 0);
    Vector3D d(5, 3, 1);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "b cross c = " << b.cross(c) << std::endl;
    std::cout << "b dot   c = " << b.dot(c) << std::endl;
    std::cout << "b cross d = " << b.cross(d) << std::endl;
    std::cout << "b dot   d = " << b.dot(d) << std::endl;
    std::cout << "d - b = " << d-b << std::endl;
    std::cout << "abs d = " << Vector3D::abs(d) << std::endl;
    std::cout << "norm d = " << d.normed() << std::endl;
    std::cout << "norm c = " << c.normed() << std::endl;
    std::cout << "norm a = " << a.normed() << std::endl;
    std::cout << "d = " << d << std::endl;
    d.norm();
    std::cout << "normed d = " << d << std::endl;
    std::cout << "Euclidian distance (b, c) = " << b.euclidian_distance(c) << std::endl;

    return 0;
}