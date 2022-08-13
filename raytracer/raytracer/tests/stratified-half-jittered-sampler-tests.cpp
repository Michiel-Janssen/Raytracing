#ifdef TEST_BUILD
#define stratified_half_jittered_sampler_tests
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "math/rectangle2d.h"
#include <samplers/stratified-half-jittered-sampler.h>

using namespace raytracer::samplers;
using namespace math;


bool check(Point2D point, const Point2D leftunder, const Point2D righttop)
{		
	if (point.x() > righttop.x() || point.y() > righttop.y() || point.x() < leftunder.x() || point.y() < leftunder.y())
	{
		return false;
	}
	return true;
}



TEST_CASE("Stratified half jittered sampler test 1")
{
	// Given a rectangle [0,1]×[0,1] and 1×1 samples, the returned sample should inside [0.25,0.75]×[0.25,0.75].

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(0.25, 0.25), Point2D(0.75, 0.75)));
}


TEST_CASE("Stratified half jittered sampler test 2")
{
	// Given a rectangle [0,2]×[0,1] and 1×1 samples, the returned sample should inside [0.5,1.5]×[0.25,0.75]

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 1));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(0.5, 0.25), Point2D(1.5, 0.75)));
}


TEST_CASE("Stratified half jittered sampler test 3")
{
	// Given a rectangle [0,1]×[0,2] and 1×1 samples, the returned sample should inside [0.25,0.75]×[0.5,1.5].	

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 2));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(0.25, 0.5), Point2D(0.75, 1.5)));
}


TEST_CASE("Stratified half jittered sampler test 4")
{
	// Given a rectangle [5,9]×[2,6] and 1×1 samples, the returned sample should inside [6,8]×[3,5].

	const Rectangle2D rectangle(Point2D(5, 2), Vector2D(4, 0), Vector2D(0, 4));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(6, 3), Point2D(8, 5)));
}


TEST_CASE("Stratified half jittered sampler test 5")
{
	// Given a rectangle [0,8]×[0,8] and 2×2 samples, the returned samples should inside [1,3]×[1,3], [1,3]×[5,7], [5,7]×[1,3] and [5,7]×[5,7].

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(8, 0), Vector2D(0, 8));
	const auto sampler = stratified_half_jittered(2, 2);
	const auto points = sampler->sample(rectangle);

	auto result = true;
	for (auto i = 0; i < points.size(); ++i)
	{
		result = (check(points[i], Point2D(1, 1), Point2D(3, 3)) ||
			check(points[i], Point2D(1, 5), Point2D(3, 7)) ||
			check(points[i], Point2D(5, 1), Point2D(7, 3)) ||
			check(points[i], Point2D(5, 5), Point2D(7, 7)));
	}

	REQUIRE(result == true);
}


TEST_CASE("Stratified half jittered sampler test 6")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(8, 0), Vector2D(0, 8));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(2, 2), Point2D(6, 6)));
}


TEST_CASE("Stratified half jittered sampler test 7")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(8, 0), Vector2D(0, 8));
	const auto sampler = stratified_half_jittered(1, 2);
	const auto points = sampler->sample(rectangle);

	
	auto result = true;
	for (auto i = 0; i < points.size(); ++i)
	{
		result = (check(points[i], Point2D(2, 1), Point2D(6, 3)) ||
			check(points[i], Point2D(2, 5), Point2D(6, 7)));
	}
	

	REQUIRE(result == true);
}


TEST_CASE("Stratified half jittered sampler test 8")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(8, 0), Vector2D(0, 8));
	const auto sampler = stratified_half_jittered(2, 1);
	const auto points = sampler->sample(rectangle);

	auto result = true;
	for (auto i = 0; i < points.size(); ++i)
	{
		result = (check(points[i], Point2D(1, 2), Point2D(3, 6)) ||
			check(points[i], Point2D(5, 2), Point2D(7, 6)));
	}

	REQUIRE(result == true);
}


TEST_CASE("Stratified half jittered sampler test 9")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(8, 0), Vector2D(0, 4));
	const auto sampler = stratified_half_jittered(1, 1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(check(points[0], Point2D(2, 1), Point2D(6, 3)));
}


TEST_CASE("Stratified half jittered sampler test 10")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(100, 0), Vector2D(0, 100));
	const auto sampler = stratified_half_jittered(2, 2);
	const auto points = sampler->sample(rectangle);

	auto result = true;
	for (auto i = 0; i < points.size(); ++i)
	{
		result = (check(points[i], Point2D(12.5, 12.5), Point2D(37.5, 37.5)) ||
			check(points[i], Point2D(12.5, 62.5), Point2D(37.5, 87.5)) ||
			check(points[i], Point2D(62.5, 12.5), Point2D(87.5, 37.5)) ||
			check(points[i], Point2D(62.5, 62.5), Point2D(87.5, 87.5)));
	}

	REQUIRE(result == true);
}



#endif
