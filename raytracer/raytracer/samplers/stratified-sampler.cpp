#include "samplers/stratified-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
    class StratifiedSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        unsigned rows;
        unsigned columns;

        StratifiedSampler(unsigned amountRows, unsigned amountColumns) : rows(amountRows), columns(amountColumns) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto grid_of_mini_rectangles = Rasterizer(rectangle, columns, rows);

            for (unsigned i = 0; i <= rows; ++i)
            {
                for (unsigned j = 0; j <= columns; ++j)
                {
                    function(grid_of_mini_rectangles[Position2D(i,j)].center());
                }
            }
        }
    };
}

Sampler raytracer::samplers::stratified_fixed(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratifiedSampler>(rows, columns));
}
