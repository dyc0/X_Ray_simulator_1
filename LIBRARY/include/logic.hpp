#ifndef XRAY_LOGIC_HPP
#define XRAY_LOGIC_HPP

namespace xrl {

    // (distance, (material, is_exit))
    typedef std::pair<double, std::pair<int, bool>> traversal_info;

    class Scene
    {
        public:
        Scene(const xru::Point3D& origin, xrt::Detector* detector);
        void generate_ray_field();
        void add_body(xrg::Body* body);

        void shoot_rays() const;
        void traversing(std::vector<traversal_info>& crossings, xrt::XRay* ray) const;

        void write_to_file(const std::string& filename) const;
        
        std::vector<xrt::XRay*> rays_;
        std::vector<xrg::Body*> bodies_;
        xrt::Detector* detector_;
    };

}

#endif