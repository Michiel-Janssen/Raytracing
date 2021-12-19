#include "ray-tracer-v5.h"
#include <iostream>     
#include <cmath>
#include <list>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;

Color RayTracerV5::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
{
	auto hits = scene.root->find_all_hits(light_ray.ray);
	Color color_filter = colors::white();


	for (auto h : hits)
	{
		if (h->t > 0 && h->t < 0.9999)
		{
			MaterialProperties matProps = h->material->at(h->local_position);

			color_filter = color_filter * matProps.light_filtering;
		}
	}

	auto surviving_light_ray = LightRay(light_ray.ray, light_ray.color * color_filter);

	return RayTracerV3::process_light_ray(scene, properties, hit, ray, surviving_light_ray);
}

raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}

