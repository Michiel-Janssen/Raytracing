#include "samplers/stratified-jittered-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class StratifiedJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        unsigned rows;
        unsigned columns;

        StratifiedJitteredSampler(unsigned amountRows, unsigned amountColumns) : rows(amountRows), columns(amountColumns) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto grid_of_mini_rectangles = Rasterizer(rectangle, columns, rows);
            double x, y;

            for (unsigned i = 0; i < rows; ++i)
            {
                for (unsigned j = 0; j < columns; ++j)
                {
                    x = ((double)rand() / (RAND_MAX));
                    y = ((double)rand() / (RAND_MAX));
                    function(grid_of_mini_rectangles[Position2D(i, j)].from_relative(math::Point2D(x, y)));
                }
            }
        }
    };
}

Sampler raytracer::samplers::stratified_jittered(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratifiedJitteredSampler>(rows, columns));
}
