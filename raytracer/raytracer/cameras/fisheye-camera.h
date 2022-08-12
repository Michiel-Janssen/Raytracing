#pragma once

#include "cameras/displaceable-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle3d.h"
#include <memory>


namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class FisheyeCamera : public DisplaceableCamera
            {
            public:
                FisheyeCamera(const math::Matrix4x4 transformation, const math::Angle& horizontal_angle, const math::Angle& vertical_angle);

            protected:
                void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            private:
                math::Angle horizontal_angle;
                math::Angle vertical_angle;
            };
        }

        Camera fisheye(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            math::Angle horizontal_angle,
            math::Angle vertical_angle);
    }
}