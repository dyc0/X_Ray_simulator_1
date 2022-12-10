#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace xrg {

    class Body {
        public:
        Body(const double x, const double y, const double z, int material = xrc::materials::VACUUM);

        virtual void intersect(const xrt::XRay &ray, double* intersections, int& numintersections) const = 0;
        virtual xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const = 0;

        void set_material(const int material);

        int material_;

        protected:
        xru::Point3D centre_;
    };

    class Ellipsoid: public Body {
        public:
        Ellipsoid(const double a, const double b, const double c, const double x, const double y, const double z);

        virtual void intersect(const xrt::XRay &ray, double* intersections, int& numintersections) const override;
        virtual xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        private:
        double a_, b_, c_;
    };

    class Sphere: public Body {
        public:
        Sphere(const double r, const double x, const double y, const double z);

        virtual void intersect(const xrt::XRay &ray, double* intersections, int& numintersections) const override;
        virtual xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        private:
        double r_;
    };

    class Cylinder: public Body {
        public:
        Cylinder(const double r, const double h, const double x, const double y, const double z);

        virtual void intersect(const xrt::XRay &ray, double* intersections, int& numintersections) const override;
        virtual xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        private:
        double r_, h_;
    };

}



#endif