#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace xrg {

    class Body {
        public:
        Body(const double x, const double y, const double z);
        virtual double weakening(const double d1, const double d2, const xrt::XRay &ray);

        protected:
        virtual xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const = 0;

        double x_, y_, z_;
        double coef; // For weakening
    };

    class Ellipsoid: public Body {
        public:
        Ellipsoid(const double a, const double b, const double c, const double x, const double y, const double z);

        private:
        xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        double a_, b_, c_;
    };

    class Sphere: public Body {
        public:
        Sphere(const double r, const double x, const double y, const double z);

        private:
        xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        double r_;
    };

    class Cylinder: public Body {
        public:
        Cylinder(const double r, const double h, const double x, const double y, const double z);

        private:
        xru::QuadraticCoef* intersect_coefs(const xrt::XRay &ray) const override;

        double r_, h_;
    }

}



#endif