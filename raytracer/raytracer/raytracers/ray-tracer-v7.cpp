#include "ray-tracer-v7.h"
#include <iostream>     
#include <cmath>
#include <list>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;

TraceResult RayTracerV7::trace(const Scene& scene, const math::Ray& eye_ray, double weight) const
{
    Hit hit;

    if (weight > 0.01 && scene.root->find_first_positive_hit(eye_ray, &hit))
    {
        MaterialProperties matprops = hit.material->at(hit.local_position);
        Color color = determine_color(scene, matprops, hit, eye_ray, weight);
        return TraceResult(color, hit.group_id, eye_ray, hit.t);
    }
    else
    {
        return TraceResult::no_hit(eye_ray);
    }
}

TraceResult raytracer::raytracers::_private_::RayTracerV7::trace(const Scene& scene, const math::Ray& ray) const
{
    return trace(scene, ray, 1.0);
}

imaging::Color RayTracerV7::compute_translucency(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    auto translucency = material_properties.translucency;

    if (translucency > 0)
    {
        Vector3D new_direction = eye_ray.direction;
        
        
        Point3D new_origin = eye_ray.at(hit.t) + 0.0000001 * new_direction;


        Ray new_ray = Ray(new_origin, new_direction);

        double new_weight = weight * translucency;
        
        Color color = trace(scene, new_ray, new_weight).color;

        return translucency * color;
    }
    else 
    {
        return colors::black();
    }
}

imaging::Color RayTracerV7::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    Color result = colors::black();

    result += RayTracerV6::determine_color(scene, material_properties, hit, eye_ray, weight);

    result += compute_translucency(scene, material_properties, hit, eye_ray, weight);

    return result;
}


raytracer::RayTracer raytracer::raytracers::v7()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV7>());
}
