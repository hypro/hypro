#include "../src/hypro/representations/GeometricObject.h"
#include "../src/hypro/algorithms/reachability/Reach.h"
#include "../src/hypro/algorithms/reachability/util.h"
#include "../src/hypro/util/Plotter.h"

int main() {

    using namespace hypro;
    using Number = mpq_class;
    using Representation = HPolytope<Number>;

    matrix_t<Number> A = matrix_t<Number>::Zero(3,3);
    A << 0,1,0,0,0,carl::rationalize<Number>(-9.81),0,0,0;
    Number delta = carl::rationalize<Number>(0.01);

    matrix_t<double> tmpDouble = convert<Number,double>(delta*A);
    matrix_t<double> tmpM = tmpDouble.exp();
    matrix_t<Number> trafoMatrix = convert<double,Number>(tmpM);

    matrix_t<Number> trafo = trafoMatrix.block(0,0,2,2);
    vector_t<Number> trans = trafoMatrix.block(0,2,2,1);

    std::cout << "A: " << convert<Number,double>(A) << std::endl;

    std::cout << "TrafoMatrix: " << convert<Number,double>(trafoMatrix) << std::endl << "Resized: " << convert<Number,double>(trafo) << std::endl << " and vector: " << convert<Number,double>(trans) << std::endl;

    std::pair<Point<Number>,Point<Number>> limitPair = std::make_pair(Point<Number>({10,0}), Point<Number>({carl::rationalize<Number>(10.2),0}));
    Box<Number> initBox = Box<Number>(limitPair);

    std::cout << "Init box " << initBox << std::endl;

    auto initSet = Converter<Number>::toHPolytope(initBox);
    Representation deltaValuation = initSet.linearTransformation(trafo,trans);

    std::cout << "initial set: " << initSet << std::endl;

    std::vector<Box<Number>> errorBoxVector = errorBoxes(delta, A, initSet, trafoMatrix);

    Representation tmp =  deltaValuation;
    if(!errorBoxVector[1].empty()) {
    	tmp = deltaValuation.minkowskiSum(Representation(errorBoxVector[1].vertices()));
    }
	Representation firstSegment = tmp.unite(initSet);
	Box<Number> differenceBox = errorBoxVector[2];
	std::cout << "Diffbox: " << convert<Number,double>(differenceBox) << std::endl;
	differenceBox = Number(Number(1)/Number(4)) * differenceBox;
	std::cout << "Diffbox: " << convert<Number,double>(differenceBox) << std::endl;
	std::cout << "Diffbox vertices: " << std::endl;
	for(const auto& vertex : differenceBox.vertices()) {
		std::cout << vertex << std::endl;
	}
	firstSegment = firstSegment.minkowskiSum( Representation(differenceBox.matrix(), differenceBox.vector()) );


    Plotter<Number>& plt = Plotter<Number>::getInstance();
    unsigned x0Box = plt.addObject(errorBoxVector[0].vertices());
    //unsigned uBox = plt.addObject(errorBoxVector[1].vertices());
    unsigned eBox = plt.addObject(errorBoxVector[2].vertices());
    unsigned fSeg = plt.addObject(firstSegment.vertices());
    unsigned init = plt.addObject(initSet.vertices());
    unsigned dVal = plt.addObject(deltaValuation.vertices());

    plt.setObjectColor(init, colors[blue]);
    plt.setObjectColor(dVal, colors[red]);
    plt.setObjectColor(fSeg, colors[green]);

    plt.setObjectColor(x0Box, colors[lila]);
    //plt.setObjectColor(uBox, colors[petrol]);
    plt.setObjectColor(eBox, colors[orange]);

    plt.plot2d();
    plt.plotGen();
}
