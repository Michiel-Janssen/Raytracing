#pragma once

#include "raytracers/ray-tracer-v4.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV5 : public RayTracerV4
            {
            public:


            protected:
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const LightRay light_ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v5();
    }
}



