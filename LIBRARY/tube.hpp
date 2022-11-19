#ifndef XRAY_TUBE_HPP
#define XRAY_TUBE_HPP

namespace xrt {

    class XRay
    {
        public:
        XRay(xru::Point3D& o, xru::Vector3D& d);
        xru::Point3D o_;
        xru::Vector3D d_;
    };

    class Source
    {

    };

    class Detector
    {

    };

}

#endif