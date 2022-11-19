#ifndef XRAY_LOGIC_HPP
#define XRAY_LOGIC_HPP

namespace xrl {

    class Scene
    {
        public:
        void generate_ray_field();
        
        std::vector<xrt::XRay*> ray_field;
        std::vector<xrg::Body*> bodies;
        xrt::Source* src;
        xrt::Detector* detect;
    };

    class Navigator
    {
        public:
        

        double intersect(const xrt::XRay& ray, const xrg::Sphere& sph) const;
        double intersect(const xrt::XRay& ray, const xrg::Ellipsoid& ell) const;
        double intersect(const xrt::XRay& ray, const xrg::Cylinder& ell) const;
    };

}

#endif