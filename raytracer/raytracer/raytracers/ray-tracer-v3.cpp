#include "ray-tracer-v1.h"
#include "ray-tracer-v2.h"
#include "ray-tracer-v3.h"
#include <iostream>     
#include <cmath>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;

Color compute_specular(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray)
{
	auto L = light_ray.ray.origin;
	auto P = hit.position;
	auto E = ray.origin;
	auto CL = light_ray.color;
	auto CP = properties.specular;
	auto e = properties.specular_exponent;
	auto n = hit.normal;


	auto i = (P - L).normalized();
	auto r = i.reflect_by(n);
	auto v = (E - P).normalized();
	double cos_alpha = cos_of_angle_between(v, r);

	if (cos_alpha > 0)
	{
		return pow(cos_alpha, e) * CL * CP;
	}
	else {
		return colors::black();
	}
}

Color RayTracerV3::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
{
	Color hit_color = colors::black();

	hit_color = RayTracerV2::process_light_ray(scene, properties, hit, ray, light_ray);
	hit_color = compute_specular(properties, hit, ray, light_ray);

	return hit_color;
}


raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}