#include "ray-tracer-v6.h"
#include <iostream>     
#include <cmath>
#include <list>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;

imaging::Color RayTracerV6::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    Color result = colors::black();

    //LightSource
    result += RayTracerV5::determine_color(scene, material_properties, hit, eye_ray);

    result += compute_reflection(scene, material_properties, hit, eye_ray, weight);

    return result;
}

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& eye_ray, double weight) const
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


TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& ray) const
{
    /*Hit hit;

    if (scene.root->find_first_positive_hit(ray, &hit))
    {*/
        return trace(scene, ray, 1.0);
    /* }
    else
    {
        return TraceResult::no_hit(ray);
    }*/
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_reflection(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    auto reflectivity = material_properties.reflectivity;

    if (reflectivity > 0)
    {        
        //hit - origin en normalized om vector te maken en dan pak van de direction de reflect op een hit
        Vector3D reflected_ray_direction = ((hit.position - eye_ray.origin).normalized()).reflect_by(hit.normal);

        //zoek het punt van waar de reflect ray start
        Point3D reflected_ray_origin = eye_ray.at(hit.t) + 0.00000001 * reflected_ray_direction;

        //Calculate the reflected ray als ray
        Ray reflected_ray = Ray(reflected_ray_origin, reflected_ray_direction);

        //Zoek de kleur
        Color relflected_color = trace(scene, reflected_ray, weight * reflectivity).color;

        return reflectivity * relflected_color;
    }
    else {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v6()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}
