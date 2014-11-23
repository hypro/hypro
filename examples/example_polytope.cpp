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

using namespace hypro;

int main(int argc, char** argv) {
	carl::VariablePool& pool = carl::VariablePool::getInstance();
	carl::Variable x = pool.getFreshVariable("x");
	carl::Variable y = pool.getFreshVariable("y");

	hypro::Polytope<number_t> polytope1 = new Polytope();
	hypro::Polytope<number_t> polytope2 = new Polytope(polytope1);

	if(polytope1.isEmpty() && polytope2.isEmpty())
	{
		Point<number_t> p1;
		Point<number_t> p2;
		Point<number_t> p3;
		Point<number_t> p4;

		Point<number_t>::coordinateMap coordinates1;
		coordinates1.insert( std::make_pair(x, carl::FLOAT_T<number_t>(1)) );
		coordinates1.insert( std::make_pair(y, carl::FLOAT_T<number_t>(1)) );
		p1 = Point<number_t>(coordinates1);

		Point<number_t>::coordinateMap coordinates2;
		coordinates2.insert( std::make_pair(x, carl::FLOAT_T<number_t>(1)) );
		coordinates2.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
		p2 = Point<number_t>(coordinates2);

		Point<number_t>::coordinateMap coordinates3;
		coordinates3.insert( std::make_pair(x, carl::FLOAT_T<number_t>(3)) );
		coordinates3.insert( std::make_pair(y, carl::FLOAT_T<number_t>(1)) );
		p3 = Point<number_t>(coordinates3);

		Point<number_t>::coordinateMap coordinates4;
		coordinates4.insert( std::make_pair(x, carl::FLOAT_T<number_t>(3)) );
		coordinates4.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
		p4 = Point<number_t>(coordinates4);

		Point<number_t>::pointSet ps;
		ps.insert(p1);
		ps.insert(p2);
		ps.insert(p3);
		ps.insert(p4);
		polytope1 = Polytope<number_t>(ps);

		if(polytope1.contains(p1))
		{
			coordinates1.insert( std::make_pair(x, carl::FLOAT_T<number_t>(1.5)) );
			coordinates1.insert( std::make_pair(y, carl::FLOAT_T<number_t>(1.5)) );
			p1 = Point<number_t>(coordinates1);

			coordinates2.insert( std::make_pair(x, carl::FLOAT_T<number_t>(2.5)) );
			coordinates2.insert( std::make_pair(y, carl::FLOAT_T<number_t>(1.5)) );
			p2 = Point<number_t>(coordinates2);

			coordinates3.insert( std::make_pair(x, carl::FLOAT_T<number_t>(1.5)) );
			coordinates3.insert( std::make_pair(y, carl::FLOAT_T<number_t>(2.5)) );
			p3 = Point<number_t>(coordinates3);

			coordinates4.insert( std::make_pair(x, carl::FLOAT_T<number_t>(2.5)) );
			coordinates4.insert( std::make_pair(y, carl::FLOAT_T<number_t>(2.5)) );
			p4 = Point<number_t>(coordinates4);

			polytope2.addPoint(p1);
			polytope2.addPoint(p2);
			polytope2.addPoint(p3);
			polytope2.addPoint(p4);

			hypro::Polytope<number_t> polytope3 = new Polytope();

			if(polytope1.contains(polytope2))
			{
				if(polytope2.minkowskiSum(polytope3, polytope1))
				{
					polytope1.updatePoints();
					polytope2.updatePoints();
					polytope3.updatePoints();

					if(!polytope3.isEmpty() && polytope1.intersect(polytope2, polytope3))
					{
						polytope1.updatePoints();
						polytope2.updatePoints();
						polytope3.updatePoints();

						hypro::Polytope<number_t> polytope4 = new Polytope();

						if(!polytope2.isEmpty() && polytope3.unite(polytope4, polytope1))
						{
							polytope1.updatePoints();
							polytope2.updatePoints();
							polytope3.updatePoints();
							polytope4.updatePoints();
						}
					}
				}
			}
		}
	}
		return 0;
}
