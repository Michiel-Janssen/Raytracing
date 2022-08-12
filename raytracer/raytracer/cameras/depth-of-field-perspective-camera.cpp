#include "cameras/depth-of-field-perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;




raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::DepthOfFieldPerspectiveCamera(const math::Matrix4x4 transformation, const std::vector<Camera> cameras)
    : DisplaceableCamera(transformation), cameras(cameras)
{
}


void raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(interval(0.0, 1.0).contains(point.x()));
    assert(interval(0.0, 1.0).contains(point.y()));

    for (auto camera : cameras)
    {
        camera->enumerate_rays(point, callback);
    }
}





Camera raytracer::cameras::depthoffieldperspective(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double distance,
    double aspect_ratio,
    double eye_size,
    Sampler eye_sampler)
{
    
    //assert(up.is_unit()); 
    Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);

    
    auto canonical_look_at = Point3D(0, 0, distance);
    //assert(canonical_look_at.x == 0);
    //assert(canonical_look_at.y == 0);
    //assert(canonical_look_at.z == math::distance(eye, look_at));

   
    auto canonical_up = up;

    std::vector<Camera> cameras;

    auto left_under = -(eye_size / 2);
    auto eye_area = Rectangle2D(Point2D(left_under, left_under), Vector2D(eye_size, 0), Vector2D(0, eye_size));
    //assert(eye_area->center == Point2D(0, 0));


    /*
            Camera perspective(
            const Point3D& eye,
            const Point3D& look_at,
            const Vector3D& up,
            double distance,
            double aspect_ratio) const
        
            return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    */
         
    auto add_camera = [canonical_look_at, canonical_up, distance, aspect_ratio, &cameras] (math::Point2D eye_2d)
    {
        auto canonical_eye = Point3D(eye_2d.x(), eye_2d.y(), 0);
        auto camera = perspective(canonical_eye, canonical_look_at, canonical_up, distance, aspect_ratio);
        cameras.push_back(camera);
    };
    

    
    eye_sampler->sample(eye_area, add_camera);


    return Camera(std::make_shared<_private_::DepthOfFieldPerspectiveCamera>(transformation, cameras));
    return Camera();
}
    