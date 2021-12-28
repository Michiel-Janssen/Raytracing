#ifndef EXCLUDE_SCRIPTING

#include "scripting/materials-module.h"
#include "scripting/scripting-util.h"
#include "materials/materials.h"
#include "imaging/color.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    /// <summary>
    /// Material Library. Groups all material-related functions together.
    /// </summary>
    struct MaterialLibrary
    {
        Material uniform(
            const Color& ambient,
            const Color& diffuse,
            const Color& specular,
            const double specular_exponent,
            const Color& light_filtering,
            const double reflectivity,
            const double translucency) const
        {
            MaterialProperties properties = create_material_properties_with()
                .ambient(ambient)
                .diffuse(diffuse)
                .specular(specular, specular_exponent)
                .light_filtering(light_filtering)
                .reflectivity(reflectivity)
                .translucency(translucency);

            return raytracer::materials::uniform(properties);
        }

        Material uniform_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(Color, ambient, colors::black());
            OPTIONAL_ARGUMENT(Color, diffuse, colors::black());
            OPTIONAL_ARGUMENT(Color, specular, colors::black());
            OPTIONAL_ARGUMENT(double, specular_exponent, 50);
            OPTIONAL_ARGUMENT(Color, light_filtering, colors::black());
            OPTIONAL_ARGUMENT(double, reflectivity, 0);
            OPTIONAL_ARGUMENT(double, translucency, 0);
            END_ARGUMENTS();

            MaterialProperties properties = create_material_properties_with()
                .ambient(ambient)
                .diffuse(diffuse)
                .specular(specular, specular_exponent)
                .light_filtering(light_filtering)
                .reflectivity(reflectivity)
                .translucency(translucency);

            return raytracer::materials::uniform(properties);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_materials_module()
{
    // Create new module
    auto module = std::make_shared<chaiscript::Module>();

    // Tell chaiscript about Material type
    util::register_type<Material>(*module, "Material");

    // Create library
    auto material_library = std::make_shared<MaterialLibrary>();

    // Expose library (member functions still need to be exposed separately)
    module->add_global_const(chaiscript::const_var(material_library), "Materials");

    // Exposes library function named INTERNAL as chaiscript function named EXTERNAL
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&MaterialLibrary::INTERNAL), #EXTERNAL)

    // Exposes library function under the same name
#   define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(uniform);
    BIND_AS(uniform_by_map, uniform);
#   undef BIND
#   undef BIND_AS

    return module;
}

#endif
