/**
 * This example file shows the basic usage of the fileWriter.
 */

#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"

using namespace hypro;

int main(int argc, char** argv) {
    
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");
	
    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
    Point<number_t> p4;

    // p1
    Point<number_t>::coordinateMap coordinates1;
    coordinates1.insert( std::make_pair(x, carl::FLOAT_T<number_t>(4)) );
    coordinates1.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
    p1 = Point<number_t>(coordinates1);

    // p2
    Point<number_t>::coordinateMap coordinates2;
    coordinates2.insert( std::make_pair(x, carl::FLOAT_T<number_t>(5)) );
    coordinates2.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
    p2 = Point<number_t>(coordinates2);

    // p3
    Point<number_t>::coordinateMap coordinates3;
    coordinates3.insert( std::make_pair(x, carl::FLOAT_T<number_t>(7)) );
    coordinates3.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
    p3 = Point<number_t>(coordinates3);

    // p4
    Point<number_t>::coordinateMap coordinates4;
    coordinates4.insert( std::make_pair(x, carl::FLOAT_T<number_t>(8)) );
    coordinates4.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
    p4 = Point<number_t>(coordinates4);
    
    Point<number_t>::pointSet ps;
    ps.insert(p1);
    ps.insert(p2);
    ps.insert(p3);
    ps.insert(p4);
    hypro::Polytope<number_t> polytope = Polytope<number_t>(ps);
    
    polytope.writeToFile("testPolytope.txt");
    
    return 0;
}