#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"

int main(int argc, char** argv) {
    
    using namespace hypro;
    using namespace carl;
    
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");
    
    Point<number_t> pt1;
    Point<number_t> pt2;
    Point<number_t> pt3;
    Point<number_t> pt4;
    
    Point<number_t>::coordinateMap c1;
    c1.insert( std::make_pair(x, FLOAT_T<number_t>(0)) );
    c1.insert( std::make_pair(y, FLOAT_T<number_t>(0)) );
    pt1 = Point<number_t>(c1);
    Point<number_t>::coordinateMap c2;
    c2.insert( std::make_pair(x, FLOAT_T<number_t>(0)) );
    c2.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
    pt2 = Point<number_t>(c2);
    Point<number_t>::coordinateMap c3;
    c3.insert( std::make_pair(x, FLOAT_T<number_t>(4)) );
    c3.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
    pt3 = Point<number_t>(c3);
    Point<number_t>::coordinateMap c4;
    c4.insert( std::make_pair(x, FLOAT_T<number_t>(4)) );
    c4.insert( std::make_pair(y, FLOAT_T<number_t>(0)) );
    pt4 = Point<number_t>(c4);
    
    Point<number_t>::pointSet ps1;
    ps1.insert(pt1);
    ps1.insert(pt2);
    ps1.insert(pt3);
    ps1.insert(pt4);
    hypro::Polytope<number_t> poly1;
    poly1 = Polytope<number_t>(ps1);
    
    number_t hdApprox = poly1.hausdorffError(0.5);
    std::cout << hdApprox << std::endl;
}