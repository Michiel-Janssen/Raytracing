#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
    namespace samplers
    {
        Sampler stratified_jittered(unsigned, unsigned);
    }
}

