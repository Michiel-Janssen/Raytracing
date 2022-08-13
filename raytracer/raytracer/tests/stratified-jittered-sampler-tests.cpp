#ifdef TEST_BUILD
#define stratified_jittered_sampler_tests
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "math/rectangle2d.h"
#include <samplers/stratified-jittered-sampler.h>

using namespace raytracer::samplers;
using namespace math;


bool check(const math::Rectangle2D rectangle, std::vector<Point2D> actual)
{
	auto leftunder = rectangle.from_relative(Point2D(0, 0));
	auto righttop = rectangle.from_relative(Point2D(1, 1));


	for (auto i = 0; i < actual.size(); ++i)
	{
		auto point = actual[i];
		if (point.x() > righttop.x() || point.y() > righttop.y() || point.x() < leftunder.x() || point.y() < leftunder.y())
		{
			return false;
		}
	}

	return true;
}

TEST_CASE("Stratified jittered sampler test 1")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	const auto sampler = stratified_jittered(1, 1);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 2")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 1));
	const auto sampler = stratified_jittered(1, 1);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 3")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 2));
	const auto sampler = stratified_jittered(1, 1);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 4")
{
	const Rectangle2D rectangle(Point2D(5, 3), Vector2D(2, 0), Vector2D(0, 5));
	const auto sampler = stratified_jittered(1, 1);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 5")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 2));
	const auto sampler = stratified_jittered(2, 2);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 6")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(3, 0), Vector2D(0, 3));
	const auto sampler = stratified_jittered(3, 3);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 7")
{
	const Rectangle2D rectangle(Point2D(5, 5), Vector2D(5, 0), Vector2D(0, 5));
	const auto sampler = stratified_jittered(5, 5);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 8")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 5));
	const auto sampler = stratified_jittered(1, 1);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 9")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 4));
	const auto sampler = stratified_jittered(2, 2);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

TEST_CASE("Stratified jittered sampler test 10")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(4, 0), Vector2D(0, 8));
	const auto sampler = stratified_jittered(4, 4);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check(rectangle, actual) == true);
}

#endif
