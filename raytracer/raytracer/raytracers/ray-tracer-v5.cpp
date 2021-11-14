#include "ray-tracer-v1.h"
#include "ray-tracer-v2.h"
#include "ray-tracer-v3.h"
#include "ray-tracer-v4.h"
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
	auto hits = scene.root->find_all_hits(ray);
	Color color_filter = colors::white();


	std::vector<Hit> hitList;

	for (auto h : hits)
	{
		if (0 < h->t && h->t < 1)
		{
			hitList.push_back(*h);
		}
	}

	for (Hit hit : hitList)
	{
		MaterialProperties matProps = hit.material->at(hit.local_position);

		color_filter = color_filter * matProps.light_filtering;
	}

	auto surviving_ligth_ray = LightRay(light_ray.ray, light_ray.color * color_filter);

	return RayTracerV3::process_light_ray(scene, properties, hit, ray, surviving_ligth_ray);
}

raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}

