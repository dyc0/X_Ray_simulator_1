#include "XRaySimulator.hpp"
#include "logic.hpp"

using namespace xrl;

Scene::Scene(const xru::Point3D& origin, xrt::Detector* detector): detector_(detector)
{
    xrt::XRay::set_source(origin);
}

void xrl::Scene::generate_ray_field()
{
    rays_ = *xrt::XRay::generate_rays(*detector_);
}

void xrl::Scene::add_body(xrg::Body *body) //TODO: material
{
    bodies_.push_back(body);
}

void xrl::Scene::shoot_rays() const
{
    std::vector<traversal_info> crossings;
    double intersections[2];
    int numintersections, current_intersection = 0;
    int px_index = 0;

    for (auto ray: rays_)
    {
        for (auto body: bodies_)
        {
            body->intersect(*ray, intersections, numintersections);
            if (numintersections == 2)
            {
                crossings.push_back(traversal_info(intersections[0], std::pair<int, bool> (body->material_, false)));
                crossings.push_back(traversal_info(intersections[1], std::pair<int, bool> (body->material_, true)));
            }                      
        }
        traversing(crossings, ray);
        detector_->update_pixel(px_index, ray);
        crossings.clear();
        px_index ++;
    }
}


void xrl::Scene::traversing(std::vector<traversal_info> &crossings, xrt::XRay* ray) const
{
    if (crossings.empty()) return;

    std::sort(crossings.begin(), crossings.end());

    double path_length = 0;
    std::stack<int> material;
    material.push(-1);
    std::vector<traversal_info>::iterator it1 = crossings.begin();
    std::vector<traversal_info>::iterator it2 = it1 + 1;
    for (; it2 != crossings.end(); it1++, it2++)
    {
        path_length = it2->first - it1->first;
        
        if (!it1->second.second) material.push(it1->second.first);
        else material.pop();
        ray->weaken(path_length, material.top());
    }
    
}

void xrl::Scene::write_to_file(const std::string &filename) const
{
    std::ofstream results;
    try { results.open(filename, std::ios::out); }
    catch (...) { std::cerr << "Error opening file " << filename << "." << std::endl; }

    std::string row_data;
    for (int row = 0; row < detector_->npixels_y_; row++)
    {   
        row_data = "";
        for (int column = 0; column < detector_->npixels_x_; column++)
            row_data.append(std::to_string(detector_->pixels[row*detector_->npixels_x_ + column]->photons)).append(" ");
        row_data.pop_back();
        results << row_data << std::endl;
    }

    results.close();
}
