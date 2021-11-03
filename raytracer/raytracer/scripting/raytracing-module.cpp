#ifndef EXCLUDE_SCRIPTING

#include "scripting/raytracing-module.h"
#include "raytracers/ray-tracers.h"
#include "scripting/scripting-util.h"
#include "raytracers/ray-tracer-v1.h"


using namespace chaiscript;
using namespace raytracer;
using namespace raytracer::scripting;


namespace
{
    struct RaytracerLibrary
    {
        RayTracer v0() const { return raytracer::raytracers::v0(); }

        RayTracer v1() const { return raytracer::raytracers::v1(); }
    };

    std::shared_ptr<Scene> create_scene(Camera camera, Primitive root, const std::vector<Boxed_Value>& boxed_lights)
    {
        auto unboxed_lights = util::cast_vector_elements<LightSource>(boxed_lights);
        return std::make_shared<Scene>(camera, root, unboxed_lights);
    }
}

ModulePtr raytracer::scripting::_private_::create_raytracing_module()
{
    // Create new chaiscript module
    auto module = std::make_shared<chaiscript::Module>();

    // Tell chaiscript about the RayTracer type
    raytracer::scripting::util::register_type<raytracer::RayTracer>(*module, "RayTracer");

    // Create library
    auto raytracer_library = std::make_shared<RaytracerLibrary>();

    // Expose library under the given name (member functions need to be exposed separately)
    module->add_global_const(chaiscript::const_var(raytracer_library), "Raytracers");

    // Expose each member of the library
#   define BIND_AS(INTERNAL, EXTERNAL)  module->add(fun(&RaytracerLibrary::INTERNAL), #EXTERNAL)
#   define BIND(NAME)                   BIND_AS(NAME, NAME)
    BIND(v0);
    BIND(v1);
    BIND_AS(v1, latest);
#   undef BIND

    // Expose create_scene under the same name
    module->add(fun(&create_scene), "create_scene");

    return module;
}

#endif
