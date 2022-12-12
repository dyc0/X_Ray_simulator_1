#ifndef XRAY_TUBE_HPP
#define XRAY_TUBE_HPP

namespace xrt {

    class Pixel;
    class Detector;

    class XRay
    {
        public:
        XRay(const xru::Vector3D& d);

        void weaken(const double path_length, const int material);
        double sum_photons() const;

        xru::Vector3D direction_;
        std::vector<double> spectrum;

        // X-ray generation:

        static void set_source(const xru::Point3D& origin);
        static std::vector<XRay*>* generate_rays(const Detector& detector);

        static xru::Point3D source_;
    };

    struct Pixel {
        Pixel(const xru::Point3D& center);

        xru::Point3D center_position;
        double intensity;
        unsigned int photons: 12;
    };

    class Detector
    {
        private:
        Detector(const xru::Point3D& center, const xru::Vector3D& face_direction, const xru::Vector3D& local_y_axis);
        Detector(const Detector&) = delete;

        public:
        static Detector* create_detector(const xru::Point3D& center, const xru::Vector3D& face_direction, const xru::Vector3D& local_y_axis);
        void populate_pixels(const int x_number, const int y_number, const double px_width, const double px_height);

        void update_pixel(int px_index, xrt::XRay* ray);

        static Detector* instance_ptr;
        std::vector<Pixel*> pixels;
        xru::Vector3D center_, face_, y_;
        int npixels_x_, npixels_y_;
    };

}

#endif