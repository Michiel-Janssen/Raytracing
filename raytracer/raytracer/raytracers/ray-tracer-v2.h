#pragma once

#include "ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV2 : public RayTracerV1
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

                imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&) const override;
            protected:      
                virtual imaging::Color process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&) const;
                virtual imaging::Color process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const LightSource light_source) const;
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&, const LightRay light_ray) const;
                virtual imaging::Color compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray&, const LightRay light_ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v2();
    }
}
