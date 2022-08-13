#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
    namespace samplers
    {
        Sampler stratified_half_jittered(unsigned, unsigned);
    }
}
