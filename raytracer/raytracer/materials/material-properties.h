#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
    private:
        MaterialProperties(
            const imaging::Color& ambient,
            const imaging::Color& diffuse,
            const imaging::Color& specular,
            const double specular_exponent,
            const imaging::Color& light_filtering,
            const double reflectivity);

    public:
        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;
        const imaging::Color light_filtering;
        const double reflectivity;

        friend class MaterialPropertiesBuilder;
    };

    class MaterialPropertiesBuilder
    {
    public:
        MaterialPropertiesBuilder();

        MaterialPropertiesBuilder& ambient(const imaging::Color& color);
        MaterialPropertiesBuilder& diffuse(const imaging::Color& color);
        MaterialPropertiesBuilder& specular(const imaging::Color& specular, const double specular_exponent);
        MaterialPropertiesBuilder& light_filtering(const imaging::Color& light_filtering);
        MaterialPropertiesBuilder& reflectivity(const double reflectivity);

        operator raytracer::MaterialProperties() const;

    private:
        imaging::Color m_ambient;
        imaging::Color m_diffuse;
        imaging::Color m_specular;
        double m_specular_exponent;
        imaging::Color m_light_filtering;
        double m_reflectivity;
    };

    inline MaterialPropertiesBuilder create_material_properties_with()
    {
        return MaterialPropertiesBuilder();
    }
}