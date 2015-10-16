/*
 * This example file shows the usage of the Polytope class.
 *
 * @file   example_polytope.h
 * @author Tayfun Oezen <tayfun.oezen@rwth-aachen.de>
 *
 * @since       2014-11-23
 * @version     2014-11-23
 */

#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"

int main(int argc, char** argv) {

	typedef carl::FLOAT_T<double> number_t;

	hypro::Polytope<number_t> polytope1 = hypro::Polytope<number_t>();
	hypro::Polytope<number_t> polytope2 = hypro::Polytope<number_t>(polytope1);

	if(polytope1.empty() && polytope2.empty())
	{
		hypro::Point<number_t> p1;
		hypro::Point<number_t> p2;
		hypro::Point<number_t> p3;
		hypro::Point<number_t> p4;

		p1 = hypro::Point<number_t>({1,1});
		p2 = hypro::Point<number_t>({1,3});
		p3 = hypro::Point<number_t>({3,1});
		p4 = hypro::Point<number_t>({3,3});

		std::vector<hypro::Point<number_t>> pv;
		pv.push_back(p1);
		pv.push_back(p2);
		pv.push_back(p3);
		pv.push_back(p4);
		polytope1 = hypro::Polytope<number_t>(pv);

		if(polytope1.contains(p1))
		{

			p1 = hypro::Point<number_t>({1.5,1.5});
			p2 = hypro::Point<number_t>({2.5,1.5});
			p3 = hypro::Point<number_t>({1.5,2.5});
			p4 = hypro::Point<number_t>({2.5,2.5});

			polytope2.addPoint(p1);
			polytope2.addPoint(p2);
			polytope2.addPoint(p3);
			polytope2.addPoint(p4);

			hypro::Polytope<number_t> polytope3 = hypro::Polytope<number_t>();

			polytope1 = polytope2.minkowskiSum(polytope3);

			polytope1.updatePoints();
			polytope2.updatePoints();
			polytope3.updatePoints();

			polytope3 = polytope1.intersect(polytope2);

			polytope1.updatePoints();
			polytope2.updatePoints();
			polytope3.updatePoints();

			hypro::Polytope<number_t> polytope4 = hypro::Polytope<number_t>();

			polytope1 = polytope3.unite(polytope4);

			polytope1.updatePoints();
			polytope2.updatePoints();
			polytope3.updatePoints();
			polytope4.updatePoints();
		}
	}
		return 0;
}
