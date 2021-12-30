#ifdef TEST_BUILD
#define HOMO_VAN_SCHIJNDEL
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include <math/rectangle2d.h>
#include <samplers/stratified-sampler.h>

using namespace math;
using namespace raytracer::samplers;

bool check(const Point2D point, std::vector<Point2D> actual)
{
	if (std::find(actual.begin(), actual.end(), point) != actual.end())
	{
		return true;
	}
	return false;
}

bool check2(const Point2D point1, const Point2D point2, std::vector<Point2D> actual)
{
	if (std::find(actual.begin(), actual.end(), point1) != actual.end())
	{
		if (std::find(actual.begin(), actual.end(), point2) != actual.end())
		{
			return true;
		}
	}
	return false;
}

bool check3(std::vector<Point2D> actual)
{
	bool result;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			auto point = Point2D(0.5 + i, 0.5 + j);
			if (std::find(actual.begin(), actual.end(), point) != actual.end())
			{
				result = true;
			}
			else
			{
				return false;
			}
			
		}
	}
	return result;
}


TEST_CASE("Stratified sampler test 1")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	const auto sampler = stratified_fixed(1, 1);
	const auto actual = sampler->sample(rectangle);
	const auto point = Point2D(0.5, 0.5);

	REQUIRE(check(point, actual) == true);
}

TEST_CASE("Stratified sampler test 2")
{
	const Rectangle2D rectangle(Point2D(5, 3), Vector2D(2, 0), Vector2D(0, 4));
	const auto sampler = stratified_fixed(1, 1);
	const auto actual = sampler->sample(rectangle);
	const auto point = Point2D(6, 5);

	REQUIRE(check(point, actual) == true);
}

TEST_CASE("Stratified sampler test 3")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 2));
	const auto sampler = stratified_fixed(1, 1);
	const auto actual = sampler->sample(rectangle);
	const auto point = Point2D(1, 1);

	REQUIRE(check(point, actual) == true);
}

TEST_CASE("Stratified sampler test 4")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(4, 0), Vector2D(0, 2));
	const auto sampler = stratified_fixed(1, 2);
	const auto actual = sampler->sample(rectangle);
	const auto point1 = Point2D(1, 1);
	const auto point2 = Point2D(3, 1);

	REQUIRE(check2(point1, point2, actual) == true);
}

TEST_CASE("Stratified sampler test 5")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 4));
	const auto sampler = stratified_fixed(2, 1);
	const auto actual = sampler->sample(rectangle);
	const auto point1 = Point2D(1, 1);
	const auto point2 = Point2D(1, 3);

	REQUIRE(check2(point1, point2, actual) == true);
}

TEST_CASE("Stratified sampler test 6")
{
	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(4, 0), Vector2D(0, 4));
	const auto sampler = stratified_fixed(4, 4);
	const auto actual = sampler->sample(rectangle);

	REQUIRE(check3(actual) == true);
}

#endif
