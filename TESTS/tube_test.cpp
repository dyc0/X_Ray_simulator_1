#include "XRaySimulator.hpp"
#include <fstream>

using namespace xrt;

// TODO: Visualize system using python script.

int main(int argc, char* argv[])
{
    // center, face and y-axis of detector
    xru::Vector3D center, face, y_axis;
    // count of pixels in x and y directions
    int x_cnt, y_cnt;
    // width and height of pixels
    double px_w, px_h;
    // source coordinates
    double s_x, s_y, s_z;

    if (argc == 17)
    {
        center = xru::Point3D(atof(argv[1]), atof(argv[2]), atof(argv[3]));
        face = xru::Point3D(atof(argv[4]), atof(argv[5]), atof(argv[6]));
        y_axis = xru::Point3D(atof(argv[7]), atof(argv[8]), atof(argv[9]));
        x_cnt = atoi(argv[10]);
        y_cnt = atoi(argv[11]);
        px_w = atof(argv[12]);
        px_h = atof(argv[13]);
        s_x = atof(argv[14]);
        s_y = atof(argv[15]);
        s_z = atof(argv[16]);
    }
    else
    {
        center = xru::Point3D(2, 0, 0);
        face = xru::Vector3D(-1, 0, 0);
        y_axis = xru::Vector3D(0, 0, 1);
        x_cnt = y_cnt = 2;
        px_w = px_h = 2;
        s_x = s_y = s_z = 0;
    }
    
    Detector* detector = Detector::create_detector(center, face, y_axis);
    detector->populate_pixels(x_cnt, y_cnt, px_w, px_h);

    XRay::set_source(xru::Vector3D(s_x, s_y, s_z));
    auto rays = XRay::generate_rays(*detector);

    std::cout << std::endl;
    std::cout << "\n\t------------------------------\n\tTESTING DETECTOR-SOURCE SYSTEM\n\t------------------------------\n\n";
    std::cout << "Pixel positions: " << std::endl;
    for (auto px_pos: detector->pixels)
        std::cout << px_pos->center_position << std::endl;
    std::cout << std::endl;

    std::cout << "Ray directions: " << std::endl;
    for (auto ray: rays)
        std::cout << ray->direction_ << std::endl;
    std::cout << std::endl;

    std::ofstream pixels_file("../HELPERS/sd_vis_data/pixels.txt");
    for (auto px_pos: detector->pixels)
        pixels_file << px_pos->center_position << std::endl;
    pixels_file.close();

    std::ofstream rays_file("../HELPERS/sd_vis_data/rays.txt");
    for (auto ray: rays)
        rays_file << ray->direction_ << std::endl;
    rays_file.close();
    
}
