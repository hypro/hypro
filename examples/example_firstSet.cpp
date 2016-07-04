//
// Created by stefan on 04.07.16.
//

#include "../src/lib/representations/GeometricObject.h"
#include "../src/lib/util/Plotter.h"
#include "../src/lib/algorithms/reachability/util.h"
CLANG_WARNING_DISABLE("-Wdeprecated-register")
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>
CLANG_WARNING_RESET

using namespace hypro;

int main(int argc, char** argv)
{
	assert(argc == 2);

	using Number = mpq_class;
	Plotter<Number>& plt = Plotter<Number>::getInstance();
	gnuplotSettings settings = plt.settings();
	settings.dimensions = std::make_pair(1,0);
	settings.axes = true;
	settings.grid = true;
	settings.cummulative = true;

	plt.updateSettings(settings);

	// ###################### Parameters #############################
	Number delta = double(std::stod(argv[1]));
	unsigned steps = unsigned(std::stoi(argv[2]));
	// ###############################################################

	matrix_t<Number> constraints = matrix_t<Number>(4,2);
	vector_t<Number> constants = vector_t<Number>(4);
	constraints << 1,0,-1,0,0,1,0,-1;
	constants << carl::rationalize<Number>(10.2), carl::rationalize<Number>(-10),0,0;

	HPolytope<Number> initSet(constraints,constants);
	unsigned init = plt.addObject(initSet.vertices());
	plt.setObjectColor(init, colors[green]);

	matrix_t<Number> dynamic = matrix_t<Number>(3,3);
	dynamic << 0,1,0,0,0,carl::rationalize<Number>(-9.81),0,0,0;

	std::cout << "Dynamic: " << dynamic << std::endl;

	matrix_t<double> doubleDynamic = convert<Number,double>(delta*dynamic);
	matrix_t<double> tmp = doubleDynamic.exp();
	matrix_t<Number> eExpDelta = convert<double,Number>(tmp);

	std::cout << "Exponential: " << tmp << std::endl;

	vector_t<Number> transition = eExpDelta.block(0,2,2,1);
	matrix_t<Number> transform = eExpDelta.block(0,0,2,2);

	std::cout << "LinearTrafo: " << transform << ", " << transition << std::endl;

	HPolytope<Number> eExpDeltaInit = initSet.linearTransformation(transform, transition);
	unsigned eExpDeltaInitSet = plt.addObject(eExpDeltaInit.vertices());
	plt.setObjectColor(eExpDeltaInitSet, colors[orange]);

	double bloatingFactorDouble = (std::exp(carl::convert<Number,double>(delta)*carl::convert<Number,double>(inftyNorm(dynamic))) - 1 - carl::convert<Number,double>(delta)*carl::convert<Number,double>(inftyNorm(dynamic)))*carl::convert<Number,double>(initSet.supremum());
	std::cout << "delta*A: " << carl::convert<Number,double>(delta)*carl::convert<Number,double>(inftyNorm(dynamic)) << std::endl;
	std::cout << "Alpha: " << bloatingFactorDouble << std::endl;

	HPolytope<Number> bloatingBall = computePolytope<Number,HPolytope<Number>>(2,Number(carl::rationalize<Number>(bloatingFactorDouble)));
	//unsigned bloatingBallPlt = plt.addObject(bloatingBall.vertices());

	HPolytope<Number> bloatedSetAtDelta = eExpDeltaInit.minkowskiSum(bloatingBall);
	unsigned bloatedSet = plt.addObject(bloatedSetAtDelta.vertices());
	plt.setObjectColor(bloatedSet, colors[lila]);

	HPolytope<Number> firstSegment = bloatedSetAtDelta.unite(initSet);
	unsigned firstSegmentPlt = plt.addObject(firstSegment.vertices());
	plt.setObjectColor(firstSegmentPlt, colors[red]);

	HPolytope<Number> currentSegment = firstSegment;
	for(unsigned step = 0; step < steps; ++step) {
		currentSegment = currentSegment.linearTransformation(transform,transition);
		plt.addObject(currentSegment.vertices());
	}

	plt.plot2d();
	plt.plotTex();
}
