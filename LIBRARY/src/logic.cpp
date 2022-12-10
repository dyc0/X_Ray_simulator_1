#include "XRaySimulator.hpp"
#include "logic.hpp"

using namespace xrl;

Scene::Scene(const xru::Point3D& origin, xrt::Detector* detector): detector_(detector)
{
    xrt::XRay::set_source(origin);
}

void xrl::Scene::generate_ray_field(const xrt::Detector &detector)
{
    rays_ = *xrt::XRay::generate_rays(detector);
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
        crossings.clear();
        
    }
}


void xrl::Scene::traversing(std::vector<traversal_info> &crossings, xrt::XRay* ray) const
{
    if (crossings.empty()) return;

    std::sort(crossings.begin(), crossings.end());

    double path_length = 0, material = -1;
    std::vector<traversal_info>::iterator it1 = crossings.begin();
    std::vector<traversal_info>::iterator it2 = it1 + 1;
    for (; it2 != crossings.end(); it1++, it2++)
    {
        path_length = it2->first - it1->first;
        material = (it1->second.second) ? it2->second.first : it1->second.first;
        ray->weaken(path_length, material);
    }
    
}
