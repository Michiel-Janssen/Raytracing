#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v2.h"
#include "raytracers/ray-tracer-v3.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV4 : public RayTracerV3
            {
            public:
                /// <summary>
                /// Traces the given ray.
                /// </summary>
                /// <param name="scene">
                /// Scene to be rendered.
                /// </param>
                /// <param name="eye_ray">
                /// Ray originating in the camera's eye and travelling through the scene.
                /// </param>
                /// <returns>
                /// Information about how to render the point where the eye_ray intersects the scene.
                /// </returns>


            protected:
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const LightRay light_ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v4();
    }
}


