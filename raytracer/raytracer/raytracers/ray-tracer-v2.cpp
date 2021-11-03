#include "ray-tracer-v1.h"
#include "ray-tracer-v2.h"


using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::raytracers;
using namespace raytracer::raytracers::_private_;


	Color RayTracerV2::compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
	{
		auto n = hit.normal;
		auto L = light_ray.ray.origin;
		auto P = hit.position;
		auto CL = light_ray.color;
		auto CS = properties.diffuse;

		auto cos = math::cos_of_angle_between(n, L-P);

		if (cos > 0)
		{
			return cos * CL * CS;
		}
		else
		{
			return colors::black();
		}
	}

	Color RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay light_ray) const
	{
		Color hit_color = colors::black();

		hit_color += compute_diffuse(properties, hit, ray, light_ray);

		return hit_color;
	}

	Color RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightSource light_source) const
	{
		Color hit_color = colors::black();

		for each (LightRay light_ray in light_source->lightrays_to(hit.position))
		{
			hit_color += process_light_ray(scene, properties, hit, ray, light_ray);
		}

		return hit_color;
	}

	Color RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
	{
		Color hit_color = colors::black();

		for each (LightSource light_source in scene.light_sources)
		{
			hit_color += process_light_source(scene, properties, hit, ray, light_source);
		}

		return hit_color;
	}

	Color RayTracerV2::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
	{
		Color hit_color = colors::black();

		hit_color += RayTracerV1::determine_color(scene, properties, hit, ray);

		hit_color += process_lights(scene, properties, hit, ray);

		return hit_color;
	}

	raytracer::RayTracer raytracer::raytracers::v2()
	{
		return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
	}



