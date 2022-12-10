#ifndef XRAY_LOGIC_HPP
#define XRAY_LOGIC_HPP

namespace xrl {

    class Scene
    {
        public:
        Scene(const xru::Point3D& origin, xrt::Detector* detector);
        void generate_ray_field(const xrt::Detector& detector);
        void add_body(xrg::Body* body);

        void shoot_rays() const;
        void traversing(std::list<std::pair<double, int>*>& entrances, std::list<std::pair<double, int>*>& exits, xrt::XRay* ray) const;
        
        std::vector<xrt::XRay*> rays_;
        std::vector<xrg::Body*> bodies_;
        xrt::Detector* detector_;
    };

}

#endif