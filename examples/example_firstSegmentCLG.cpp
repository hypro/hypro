#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/algorithms/reachability/Reach.h"
#include "../src/lib/algorithms/reachability/util.h"

int main(int argc, char** argv) {

    using namespace hypro;
    using Number = mpq_class;
    using Representation = HPolytope<Number>;

    matrix_t<Number> A = matrix_t<Number>::Zero(3,3);
    A << 0,-1,0,0,0,carl::rationalize<Number>(-9.81),0,0,0;

    std::pair<Point<Number>,Point<Number>> limitPair = std::make_pair(Point<Number>({10,0,0}), Point<Number>({carl::rationalize<Number>(10.2),0,0}));
    Box<Number> initBox = Box<Number>(limitPair);

    std::cout << "Init box " << initBox << std::endl;

    auto initSet = Converter<Number>::toHPolytope(initBox);

    std::cout << "initial set: " << initSet << std::endl;

    Number delta = carl::rationalize<Number>(0.01);

    Representation tmp = computeFirstSegmentCLG(A,initSet,delta);
}
