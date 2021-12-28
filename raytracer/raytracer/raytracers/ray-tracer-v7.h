#pragma once

#pragma once

#include "ray-tracer-v6.h"
#include "raytracers/ray-tracer.h"
#include <memory>

namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV7 : public RayTracerV6
            {
            public:


            protected:
                imaging::Color determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray, double weight) const;
                imaging::Color compute_translucency(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const;
                TraceResult trace(const Scene& scene, const math::Ray& ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v7();
    }
}
