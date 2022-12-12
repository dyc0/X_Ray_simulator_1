#include "XRaySimulator.hpp"
#include "tube.hpp"

using namespace xrt;

xru::Point3D XRay::source_ = xru::Point3D(0, 0, 0);
Detector* Detector::instance_ptr = nullptr;

XRay::XRay(const xru::Vector3D& direction):
    direction_(direction)
{  
    spectrum = xrc::spectrum;
}

void XRay::set_source(const xru::Point3D& origin)
{
    XRay::source_ = origin;
}

std::vector<XRay*>* XRay::generate_rays(const Detector& detector)
{
    assert(!detector.pixels.empty());

    std::vector<XRay*>* rays = new std::vector<XRay*>();

    for (auto px: detector.pixels)
        rays->push_back(new XRay((px->center_position - XRay::source_).normed()));

    return rays;
}

void xrt::XRay::weaken(const double path_length, const int material)
{
    if (material == -1) return;

    std::vector<double>::iterator si = spectrum.begin();
    std::vector<double>::const_iterator mi = (*xrc::materials_keys.at(material)).begin();
    for (; si != spectrum.end(); si++, mi++)
    {
        *si = *si * exp(- *mi * path_length * xrc::material_densities[material]);
    }
}

double xrt::XRay::sum_photons() const
{
    double sum = 0;
    for (auto ph_count: spectrum) sum += ph_count;
    return sum;
}

Pixel::Pixel(const xru::Point3D& center): center_position(center) { };


Detector::Detector(const xru::Point3D& center, const xru::Vector3D& face_direction, const xru::Vector3D& local_y_axis):
    center_(center), face_(face_direction.normed()), y_(local_y_axis.normed()), npixels_x_(0), npixels_y_(0) { };

Detector * Detector::create_detector(const xru::Point3D &center, const xru::Vector3D &face_direction, const xru::Vector3D &local_y_axis)
{
    if (instance_ptr != nullptr) 
    {
        std::cout << "Only one detector can be created per scene." << std::endl;
        return instance_ptr;
    }

    instance_ptr = new Detector(center, face_direction, local_y_axis); 
    return instance_ptr;
}

void Detector::populate_pixels(const int x_number, const int y_number, const double px_width, const double px_height)
{
    assert((x_number % 2 == 0) && (y_number % 2 == 0));

    npixels_x_ = x_number;
    npixels_y_ = y_number;

    xru::Vector3D x_ = y_.cross(face_);
    x_.norm();
    
    // TODO: Sort out edges
    for (int dy = -y_number/2; dy < y_number/2; dy++)
        for (int dx = -x_number/2; dx < x_number/2; dx++)
            {
                pixels.push_back(new Pixel(center_ + xru::Vector3D(x_ * px_width/2 * (2*dx+1)) + xru::Vector3D(y_ * px_height/2 * (2*dy+1))));
            }
    }

    void xrt::Detector::update_pixel(int px_index, xrt::XRay* ray)
    {
        pixels[px_index]->photons = (unsigned int) ray->sum_photons();
        // pixels[px_index]->intensity = ray->sum_photons();
    }
