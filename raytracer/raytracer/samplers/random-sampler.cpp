#include "random-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
	class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		 double sample_count;
		 double random;

		 RandomSampler(double samplecount) : sample_count(samplecount), random(((double)rand() / (RAND_MAX))) {}

		 void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		 {
			 for (auto i = 0; i <= this->sample_count; ++i)
			 {
				 double x = ((double)rand() / (RAND_MAX));
				 double y = ((double)rand() / (RAND_MAX));
				 //math::Point2D point = math::Point2D(x,y);
				 auto sample = rectangle.from_relative(math::Point2D(x, y));

				 function(sample);
			}
		 }
	};
}

Sampler samplers::random(double sample_count)
{
	return Sampler(std::make_shared<RandomSampler>(sample_count));
}
