#ifdef TEST_BUILD
#define n_rooks_sampler_tests
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"
#include "math/rectangle2d.h"
#include <samplers/n-rooks-sampler.h>

using namespace raytracer::samplers;
using namespace math;


bool nrooks_check(Point2D point, const Point2D leftunder, const Point2D righttop)
{
	if (point.x() > righttop.x() || point.y() > righttop.y() || point.x() < leftunder.x() || point.y() < leftunder.y())
	{
		return false;
	}
	return true;
}



TEST_CASE("n rooks sampler test 1")
{
	// Given a rectangle [0,1]×[0,1] and N=1 sample, the returned sample should inside [0,1]×[0,1].

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	const auto sampler = n_rooks(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(nrooks_check(points[0], Point2D(0, 0), Point2D(1, 1)));
}


TEST_CASE("n rooks sampler test 2")
{
	// Given a rectangle [4,8]×[6,7] and N=1 sample, the returned sample should inside [4,8]×[6,7].

	const Rectangle2D rectangle(Point2D(4, 6), Vector2D(4, 0), Vector2D(0, 1));
	const auto sampler = n_rooks(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(nrooks_check(points[0], Point2D(4, 6), Point2D(8, 7)));
}


TEST_CASE("n rooks sampler test 3")
{
	/* 
		Given a rectangle [0,4]×[0,4] and N=4 samples, 4 samples should be returned.
			One sample should have its x-coordinate in [0,1]
			One sample should have its x-coordinate in [1,2]
			One sample should have its x-coordinate in [2,3]
			One sample should have its x-coordinate in [3,4]

			One sample should have its y-coordinate in [0,1]
			One sample should have its y-coordinate in [1,2]
			One sample should have its y-coordinate in [2,3]
			One sample should have its y-coordinate in [3,4]
	*/

	const Rectangle2D rectangle(Point2D(0, 0), Vector2D(4, 0), Vector2D(0, 4));
	const auto sampler = n_rooks(4);
	const auto points = sampler->sample(rectangle);

	REQUIRE(points.size() == 4);

	std::vector<unsigned> vector_x;
	std::vector<unsigned> vector_y;
	for (unsigned k = 0; k < 4; ++k)
	{
		vector_x.push_back(k);
		vector_y.push_back(k);
	}

	bool final = true;
	REQUIRE(vector_x.size() == 4);
	REQUIRE(vector_y.size() == 4);

	for (unsigned i = 0; i < 4; ++i)
	{
		auto point_x = floor(points[i].x());
		auto result_x = std::find(begin(vector_x), end(vector_x), point_x);

		if (result_x == std::end(vector_x)) final = false;
		else vector_x.erase(std::remove(vector_x.begin(), vector_x.end(), point_x), vector_x.end());
		

		auto point_y = floor(points[i].y());
		auto result_y = std::find(begin(vector_y), end(vector_y), point_y);

		if (result_y == std::end(vector_y)) final = false;
		else vector_y.erase(std::remove(vector_y.begin(), vector_y.end(), point_y), vector_y.end());
		
	}

	REQUIRE(final);
	REQUIRE(vector_x.size() == 0);
	REQUIRE(vector_y.size() == 0);
}


TEST_CASE("n rooks sampler test 4")
{
	/*
		Given a rectangle [4,7]×[4,7] and N=3 samples, 3 samples should be returned.
			One sample should have its x-coordinate in [4,5]
			One sample should have its x-coordinate in [5,6]
			One sample should have its x-coordinate in [6,7]

			One sample should have its y-coordinate in [4,5]
			One sample should have its y-coordinate in [5,6]
			One sample should have its y-coordinate in [6,7]
	*/

	const Rectangle2D rectangle(Point2D(4, 4), Vector2D(3, 0), Vector2D(0, 3));
	const auto sampler = n_rooks(3);
	const auto points = sampler->sample(rectangle);

	REQUIRE(points.size() == 3);

	std::vector<unsigned> vector_x;
	std::vector<unsigned> vector_y;
	for (unsigned k = 4; k < 7; ++k)
	{
		vector_x.push_back(k);
		vector_y.push_back(k);
	}

	bool final = true;
	REQUIRE(vector_x.size() == 3);
	REQUIRE(vector_y.size() == 3);

	for (unsigned i = 0; i < 3; ++i)
	{
		auto point_x = floor(points[i].x());
		auto result_x = std::find(begin(vector_x), end(vector_x), point_x);

		if (result_x == std::end(vector_x)) final = false;
		else vector_x.erase(std::remove(vector_x.begin(), vector_x.end(), point_x), vector_x.end());


		auto point_y = floor(points[i].y());
		auto result_y = std::find(begin(vector_y), end(vector_y), point_y);

		if (result_y == std::end(vector_y)) final = false;
		else vector_y.erase(std::remove(vector_y.begin(), vector_y.end(), point_y), vector_y.end());

	}

	REQUIRE(final);
	REQUIRE(vector_x.size() == 0);
	REQUIRE(vector_y.size() == 0);


}


TEST_CASE("n rooks sampler test 5")
{
	// Given a rectangle [8,10]×[6,10] and N=1 sample, the returned sample should inside [8,10]×[6,10].

	const Rectangle2D rectangle(Point2D(8, 6), Vector2D(2, 0), Vector2D(0, 4));
	const auto sampler = n_rooks(1);
	const auto points = sampler->sample(rectangle);

	REQUIRE(nrooks_check(points[0], Point2D(8, 6), Point2D(10, 10)));
}


#endif
