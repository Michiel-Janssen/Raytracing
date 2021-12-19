#include "materials/material-properties.h"
#include "imaging/color.h"


using namespace imaging;

raytracer::MaterialProperties::MaterialProperties(
    const Color& ambient,
    const Color& diffuse,
    const Color& specular,
    const double specular_exponent,
    const Color& light_filtering,
    const double reflectivity)
    : ambient(ambient)
    , diffuse(diffuse)
    , specular(specular)
    , specular_exponent(specular_exponent)
    , light_filtering(light_filtering)
    , reflectivity(reflectivity)

{
    // NOP
}

raytracer::MaterialPropertiesBuilder::MaterialPropertiesBuilder()
    : m_ambient(colors::black())
    , m_diffuse(colors::black())
    , m_specular(colors::black())
    , m_specular_exponent(50)
    , m_light_filtering(colors::black())
    , m_reflectivity(0)
{
    // NOP
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::ambient(const imaging::Color& color)
{
    m_ambient = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::diffuse(const imaging::Color& color)
{
    m_diffuse = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::specular(const imaging::Color& color, const double x)
{
    m_specular = color;
    m_specular_exponent = x;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::light_filtering(const imaging::Color& color)
{
    m_light_filtering = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::reflectivity(const double x)
{
    m_reflectivity = x;

    return *this;
}

raytracer::MaterialPropertiesBuilder::operator raytracer::MaterialProperties() const
{
    return MaterialProperties(
        m_ambient,
        m_diffuse,
        m_specular,
        m_specular_exponent,
        m_light_filtering,
        m_reflectivity
    );
}
