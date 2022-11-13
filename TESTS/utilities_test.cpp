#include "utilities.hpp"
#include <iostream>

using namespace xru;

int main(int argc, const char* argv[])
{   
    std::cout << "TESTING" << std::endl;

    std::cout << "Testing constructors" << std::endl;
    Vector3D<double> a;
    Vector3D<double> b(9., 3., 5.);

    std::cout << "Empty constructor: " << a.dx << " " << a.dy << " " << a.dz << std::endl;
    std::cout << "Argumented constructor: " << b.dx << " " << b.dy << " " << b.dz << std::endl;

    return 0;
}