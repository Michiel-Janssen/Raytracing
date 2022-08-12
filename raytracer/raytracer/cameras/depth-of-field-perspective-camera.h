#pragma once

#include "cameras/displaceable-camera.h"
#include "cameras/perspective-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle3d.h"
#include <memory>
#include <samplers/sampler.h>



namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class DepthOfFieldPerspectiveCamera : public DisplaceableCamera
            {
            public:
                DepthOfFieldPerspectiveCamera(const math::Matrix4x4 transformation, const std::vector<Camera> cameras);

            protected:
                void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            private:
                std::vector<Camera> cameras;
            };
        }

        Camera depthoffieldperspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio,
            double eye_size,
            Sampler eye_sampler);
    }
}