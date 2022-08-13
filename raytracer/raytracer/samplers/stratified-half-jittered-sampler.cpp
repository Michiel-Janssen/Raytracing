#include "samplers/stratified-half-jittered-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class StratifiedHalfJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        unsigned rows;
        unsigned columns;

        StratifiedHalfJitteredSampler(unsigned amountRows, unsigned amountColumns) : rows(amountRows), columns(amountColumns) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto grid = Rasterizer(rectangle, rows, columns);

            for (unsigned i = 0; i < rows; ++i)
            {
                for (unsigned j = 0; j < columns; ++j)
                {
                    // random getal tussen 0 en 0.5, dan plus 0.25

                    double x = (((double)rand() / (RAND_MAX)) / 2) + 0.25;
                    double y = (((double)rand() / (RAND_MAX)) / 2) + 0.25;


                    function(grid[Position2D(i,j)].from_relative(Point2D(x, y)));
                }
            }
        }
    };
}

Sampler raytracer::samplers::stratified_half_jittered(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratifiedHalfJitteredSampler>(rows, columns));
}
