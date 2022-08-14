#include "samplers/multijittered-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class MultijitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        unsigned n;

        MultijitteredSampler(unsigned n) : n(n) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto big_grid = Rasterizer(rectangle, n, n);
            std::vector<Point2D> all_locations;

            for (unsigned x = 0; x < n; ++x)
            {
                for (unsigned y = 0; y < n; ++y)
                {
                    all_locations.push_back(Point2D(x, y));
                }
            }



            for (unsigned i = 0; i < n; ++i)
            {
                for (unsigned j = 0; j < n; ++j)
                {
                    auto small_grid = Rasterizer(big_grid[Position2D(i, j)], n, n);
                    unsigned id_location = (unsigned)floor(((double)rand() / (RAND_MAX)) * all_locations.size());
                    auto location = all_locations[id_location];

                    double correction_x = (double)rand() / (RAND_MAX);
                    double correction_y = (double)rand() / (RAND_MAX);

                    function(small_grid[Position2D((unsigned)location.x(), (unsigned)location.y())].from_relative(Point2D(correction_x, correction_y)));
                    all_locations.erase(std::remove(all_locations.begin(), all_locations.end(), location), all_locations.end());

                }
            }
        }
    };
}

Sampler raytracer::samplers::multi_jittered(unsigned n)
{
    return Sampler(std::make_shared<MultijitteredSampler>(n));
}
