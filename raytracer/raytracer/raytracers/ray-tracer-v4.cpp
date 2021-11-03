#include "ray-tracer-v1.h"
#include "ray-tracer-v2.h"
#include "ray-tracer-v3.h"
#include "ray-tracer-v4.h"
#include <iostream>     
#include <cmath>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;

Color RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
{
	Hit newHit;
	
	auto light_hit = scene.root->find_first_positive_hit(ray, &newHit);

	if (light_hit && !(0 <= newHit.t) && !(newHit.t < 1))
	{
		return RayTracerV3::process_light_ray(scene, properties, hit, ray, light_ray);
	}
	else {
		return colors::black();
	}
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}