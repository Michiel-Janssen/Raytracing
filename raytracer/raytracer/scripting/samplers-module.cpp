#ifndef EXCLUDE_SCRIPTING

#include "scripting/samplers-module.h"
#include "samplers/samplers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct SamplerLibrary
    {
        Sampler single() const
        {
            return samplers::single();
        }

        Sampler random(double sample_count) const
        {
            return samplers::random(sample_count);
        }

        Sampler stratified_fixed(unsigned rows, unsigned columns) const
        {
            return samplers::stratified_fixed(rows, columns);
        }

        Sampler stratified_jittered(unsigned rows, unsigned columns) const
        {
            return samplers::stratified_jittered(rows, columns);
        }

        Sampler halfjittered(unsigned rows, unsigned columns) const
        {
            return samplers::stratified_half_jittered(rows, columns);
        }

        Sampler nrooks(unsigned sample_count) const
        {
            return samplers::n_rooks(sample_count);
        }

        Sampler multijittered(unsigned n) const
        {
            return samplers::multi_jittered(n);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Sampler>(*module, "Sampler");

    auto sampler_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(sampler_library), "Samplers");

#   define BIND(NAME)  module->add(fun(&SamplerLibrary::NAME), #NAME)
    BIND(single);
    BIND(random);
    BIND(stratified_fixed);
    BIND(stratified_jittered);
    BIND(halfjittered);
    BIND(nrooks);
    BIND(multijittered);
#   undef BIND

    return module;
}   

#endif
