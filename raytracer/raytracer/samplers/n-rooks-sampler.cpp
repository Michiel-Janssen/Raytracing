#include "samplers/n-rooks-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class NRooksSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        unsigned sample_count;

        NRooksSampler(unsigned sample_count) : sample_count(sample_count) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            auto grid = Rasterizer(rectangle, sample_count, sample_count);
            std::vector<unsigned> all_y_values;

            for (unsigned i = 0; i < sample_count; ++i)
            {

                unsigned random;
                auto check = true;

                while (check) 
                {
                    random = (unsigned)floor(((double)rand() / (RAND_MAX)) * sample_count);
                    auto result = std::find(begin(all_y_values), end(all_y_values), random);

                    if (result == std::end(all_y_values))
                    {
                        check = false;
                        all_y_values.push_back(random);
                    }
                        
                }
                

                double x = (double)rand() / (RAND_MAX);
                double y = (double)rand() / (RAND_MAX);

                function(grid[Position2D(i, random)].from_relative(Point2D(x, y)));
                
            }
        }
    };
}

Sampler raytracer::samplers::n_rooks(unsigned sample_count)
{
    return Sampler(std::make_shared<NRooksSampler>(sample_count));
}
