#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"
#include "../src/lib/algorithms/reachability/util.h"

int main(int argc, char** argv) {

    using namespace hypro;
    using namespace carl;

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");

    typedef FLOAT_T<double> number_t;

    Point<number_t> pt1;
    Point<number_t> pt2;
    Point<number_t> pt3;
    Point<number_t> pt4;

    pt1 = Point<number_t>({0,0});
    pt2 = Point<number_t>({0,4});
    pt3 = Point<number_t>({4,4});
    pt4 = Point<number_t>({4,0});

    std::vector<Point<number_t>> pv1;
    pv1.push_back(pt1);
    pv1.push_back(pt2);
    pv1.push_back(pt3);
    pv1.push_back(pt4);
    hypro::Polytope<number_t> poly1;
    poly1 = Polytope<number_t>(pv1);

    // TODO: Fix!
    //number_t hdApprox = hausdorffError(0.5, poly1.matrix(), poly1.supremum_());
    // std::cout << hdApprox << std::endl;
}