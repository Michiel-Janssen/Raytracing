#ifdef TEST_BUILD
#define multijittered_sampler_tests
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "math/rectangle2d.h"
#include <samplers/multijittered-sampler.h>

using namespace raytracer::samplers;
using namespace math;


bool multijittered_check(Point2D point, const Point2D leftunder, const Point2D righttop)
{
	if (point.x() > righttop.x() || point.y() > righttop.y() || point.x() < leftunder.x() || point.y() < leftunder.y())
	{
		return false;
	}
	return true;
}



TEST_CASE("multijittered sampler test 1")
{
	// Given a rectangle [0,1]×[0,1] and 1 sample, the returned sample should inside [0,1]×[0,1].

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	const auto sampler = multi_jittered(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(multijittered_check(points[0], Point2D(0, 0), Point2D(1, 1)));
}


TEST_CASE("multijittered sampler test 2")
{
	// Given a rectangle [4,8]×[6,7] and 1 sample, the returned sample should inside [4,8]×[6,7].

	const Rectangle2D rectangle(Point2D(4, 6), Vector2D(4, 0), Vector2D(0, 1));
	const auto sampler = multi_jittered(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(multijittered_check(points[0], Point2D(4, 6), Point2D(8, 7)));
}


TEST_CASE("multijittered sampler test 3")
{
	/*
		Given a rectangle [0,2]×[0,2] and 2×2 samples, 4 samples should be returned.

			Two samples should have their x-coordinate in [0,1]
			Two samples should have their x-coordinate in [1,2]

			Two samples should have their y-coordinate in [0,1]
			Two samples should have their y-coordinate in [1,2]
	*/

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(2, 0), Vector2D(0, 2));
	const auto sampler = multi_jittered(2);
	const auto points = sampler->sample(rectangle);

	unsigned x_in_part_one = 0;
	unsigned x_in_part_two = 0;
	unsigned y_in_part_one = 0;
	unsigned y_in_part_two = 0;

	REQUIRE(points.size() == 4);

	for (unsigned i = 0; i < 4; ++i)
	{
		auto rounded_x = floor(points[i].x());
		auto rounded_y = floor(points[i].y());

		if (rounded_x == 0) ++x_in_part_one;
		else if (rounded_x == 1) ++x_in_part_two;
		else REQUIRE(false);

		if (rounded_y == 0) ++y_in_part_one;
		else if (rounded_y == 1) ++y_in_part_two;
		else REQUIRE(false);
	}

	REQUIRE(x_in_part_one == 2);
	REQUIRE(x_in_part_two == 2);
	REQUIRE(y_in_part_one == 2);
	REQUIRE(y_in_part_two == 2);
}



TEST_CASE("multijittered sampler test 4")
{
	/*
		Given a rectangle [5,9]×[2,4] and 2×2 samples, 4 samples should be returned.

			Two samples should have their x-coordinate in [5,7]
			Two samples should have their x-coordinate in [7,9]

			Two samples should have their y-coordinate in [2,3]
			Two samples should have their y-coordinate in [3,4]
	*/

	const Rectangle2D rectangle(Point2D(5, 2), Vector2D(4, 0), Vector2D(0, 2));
	const auto sampler = multi_jittered(2);
	const auto points = sampler->sample(rectangle);

	unsigned x_in_part_one = 0;
	unsigned x_in_part_two = 0;
	unsigned y_in_part_one = 0;
	unsigned y_in_part_two = 0;

	REQUIRE(points.size() == 4);

	for (unsigned i = 0; i < 4; ++i)
	{
		if (points[i].x() >= 5 && points[i].x() <= 7) ++x_in_part_one;
		else if (points[i].x() >= 7 && points[i].x() <= 9) ++x_in_part_two;
		else REQUIRE(false);

		if (points[i].y() >= 2 && points[i].y() <= 3) ++y_in_part_one;
		else if (points[i].y() >= 3 && points[i].y() <= 4) ++y_in_part_two;
		else REQUIRE(false);
	}

	REQUIRE(x_in_part_one == 2);
	REQUIRE(x_in_part_two == 2);
	REQUIRE(y_in_part_one == 2);
	REQUIRE(y_in_part_two == 2);
}


TEST_CASE("multijittered sampler test 5")
{
	// Given a rectangle [2,8]×[6,7] and 1 sample, the returned sample should inside [2,8]×[6,7].

	const Rectangle2D rectangle(Point2D(2, 6), Vector2D(6, 0), Vector2D(0, 1));
	const auto sampler = multi_jittered(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(multijittered_check(points[0], Point2D(2, 6), Point2D(8, 7)));
}



#endif
