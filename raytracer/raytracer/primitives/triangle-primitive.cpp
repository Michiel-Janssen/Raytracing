#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Point3D a, b, c;
        Vector3D n;

        TriangleImplementation(const Point3D& a, const Point3D& b, const Point3D& c) : a(a), b(b), c(c), n((b - a).cross(c - a).normalized())
        {
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            auto t = ((a - ray.origin).dot(n)) / (ray.direction.dot(n));

            auto H = ray.origin + ray.direction * t;

            if ((((b - a).cross(H - a)).dot(n) >= 0) && (((c - b).cross(H - b)).dot(n) >= 0) && (((a - c).cross(H - c)).dot(n) >= 0))
            {
                std::vector<std::shared_ptr<Hit>> hits;
                auto hit = std::make_shared<Hit>();

                // INITIALIZE_HIT

                hit->t = t;
                hit->position = ray.at(hit->t);
                hit->local_position.xyz = hit->position;
                hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());

                // je wilt dat de normaal tegen in je oog straal gaat.
                hit->normal = ray.direction.dot(n) <= 0 ? n : -n;
                hits.push_back(hit);
                return hits;
            }
            return std::vector<std::shared_ptr<Hit>>();
        }

        math::Box bounding_box() const override
        {
            auto xmin = std::min({ a.x(), b.x(), c.x() });
            auto xmax = std::max({ a.x(), b.x(), c.x() });

            auto ymin = std::min({ a.y(), b.y(), c.y() });
            auto ymax = std::max({ a.y(), b.y(), c.y() });

            auto zmin = std::min({ a.z(), b.z(), c.z() });
            auto zmax = std::max({ a.z(), b.z(), c.z() });

            auto xinterval = interval(xmin, xmax);
            auto yinterval = interval(ymin, ymax);
            auto zinterval = interval(zmin, zmax);

            return math::Box(xinterval, yinterval, zinterval);
        }

    };
}

Primitive raytracer::primitives::triangle(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3)
{
    return Primitive(std::make_shared<TriangleImplementation>(vertex1, vertex2, vertex3));
}