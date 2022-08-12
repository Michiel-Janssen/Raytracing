#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include "math/interval.h"
#include "math/interval-mapper.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;


raytracer::cameras::_private_::FisheyeCamera::FisheyeCamera(const math::Matrix4x4 transformation, const math::Angle& horizontal_angle, const math::Angle& vertical_angle)
    : DisplaceableCamera(transformation), horizontal_angle(horizontal_angle), vertical_angle(vertical_angle)
{
    // NOP
}



void raytracer::cameras::_private_::FisheyeCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(interval(0.0, 1.0).contains(point.x()));
    assert(interval(0.0, 1.0).contains(point.y()));


    Interval<Angle> interval_horizontal((horizontal_angle/2) - 90_degrees, -(horizontal_angle/2) - 90_degrees);
    Interval<Angle> interval_vertical(-(vertical_angle/2), (vertical_angle/2));

    IntervalMapper<double, Angle> intervalmapper_horizontal(Interval<double>(0.0, 1.0), interval_horizontal);
    IntervalMapper<double, Angle> intervalmapper_vertical(Interval<double>(0.0, 1.0), interval_vertical);

    Point3D p = Point3D::spherical(1, intervalmapper_horizontal[point.x()], intervalmapper_vertical[point.y()]);

    callback(Ray(math::Point3D(0, 0, 0), p));
}



Camera raytracer::cameras::fisheye(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    math::Angle horizontal_angle,
    math::Angle vertical_angle)
{
    assert(up.is_unit());

    Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);

    return Camera(std::make_shared<_private_::FisheyeCamera>(transformation, horizontal_angle, vertical_angle));
}