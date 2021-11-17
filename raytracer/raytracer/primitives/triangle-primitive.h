#pragma once

#include "primitives/primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive triangle(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3);
    }
}