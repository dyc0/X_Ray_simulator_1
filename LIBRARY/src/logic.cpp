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
    std::list<std::pair<double, int>*> entrances, exits;
    double intersections[2];
    int numintersections, current_intersection = 0;

    for (auto ray: rays_)
    {
        for (auto body: bodies_)
        {
            body->intersect(*ray, intersections, numintersections);
            if (numintersections == 2)
            {
                entrances.push_back(new std::pair<double, int>(intersections[0], body->material_));
                exits.push_back(new std::pair<double, int>(intersections[0], body->material_));
                traversing(entrances, exits, ray);
            }                      
        }

        entrances.clear();
        exits.clear();
    }
}


void xrl::Scene::traversing(std::list<std::pair<double, int>*> &entrances, std::list<std::pair<double, int>*> &exits, xrt::XRay* ray) const
{
    if (entrances.empty() || exits.empty()) return;

    std::sort(entrances.begin(), entrances.end());
    std::sort(exits.begin(), exits.end()); 

    std::pair<double, int> * entrance, * exit;
    bool is_exit = false, next_is_exit = false, first = true;


    // it must enter into a body first.
    entrance = entrances.front();
    entrances.pop_front();

    while (!entrances.empty() && !exits.empty())
    {   
        if (!first)
        {
            entrance = exit;
            is_exit = next_is_exit;
        }
        else first = false;

        if (entrances.front()->first < exits.front()->first - xrc::tolerance)
        {
            exit = entrances.front();
            entrances.pop_front();
            next_is_exit = false;
        }
        else
        {
            exit = exits.front();
            exits.pop_front();
            next_is_exit = true;
        }
    }
}
