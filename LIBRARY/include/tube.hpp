#ifndef XRAY_TUBE_HPP
#define XRAY_TUBE_HPP

namespace xrt {

    class XRay
    {
        public:
        XRay(xru::Point3D& o, xru::Vector3D& d);
        XRay(xru::Point3D& o, xru::Vector3D& d);

        // X-ray generation:

        static void set_source(double x, double y, double z);
        static void generate_rays();

        xru::Point3D o_;
        xru::Vector3D d_;

        static double source_x_, source_y_, source_z_;
    };

    class Source
    {
    };

    class Detector
    {

    };

}

#endif