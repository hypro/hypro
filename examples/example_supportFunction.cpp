
#include "../src/lib/config.h"
#include "../src/lib/representations/SupportFunction/SupportFunction.h"
#include "../src/lib/util/Plotter.h"

using namespace hypro;

int main(int argc, char** argv) {
	matrix_t<double> matrix = matrix_t<double>(4,2);
	vector_t<double> distances = vector_t<double>(4);
	matrix << 0,1,
		1,0,
		0,-1,
		-1,0;
	distances << 1,1,1,1;
	matrix_t<double> matrix2 = matrix_t<double>(3,2);
	vector_t<double> distances2 = vector_t<double>(3);
	matrix2 << 1,1,
		-1,1,
		0,-1,
	distances2 << 1,1,0;
	vector_t<double> distances3 = vector_t<double>(4);
	distances3 << 1.5,1.5,-0.5,-0.5;

	matrix_t<double> linearMap = matrix_t<double>(2,2);
	linearMap << -1,-4,4,-1;
	double timestep = 0.01;

	linearMap = linearMap*timestep;
	matrix_t<double> exponential = linearMap.exp();

	std::shared_ptr<SupportFunction<double>> poly1 = SupportFunction<double>::create(SF_TYPE::POLY, matrix, distances);
	//SupportFunction<double> poly2(SF_TYPE::POLY, matrix2, distances2);
	std::shared_ptr<SupportFunction<double>> poly3 = SupportFunction<double>::create(SF_TYPE::POLY, matrix, distances3);
	std::shared_ptr<SupportFunction<double>> ball = SupportFunction<double>::create(SF_TYPE::INFTY_BALL, .5);
	
	
	std::shared_ptr<SupportFunction<double>> rounded1 = poly1->minkowskiSum(ball);
	//SupportFunction<double> rounded2 = poly2.minkowskiSum(ball);
	//SupportFunction<double> rounded = ball;
	std::shared_ptr<SupportFunction<double>> unionRes = poly1->unite(poly3);
	std::shared_ptr<SupportFunction<double>> intersectionRes = poly1->intersect(poly3);

	rounded1->print();


	// create array holding equaly distributed directions
	int resolution = 5;
	matrix_t<double> evaldirections = matrix_t<double>(resolution, 2);
	for(int pos = 0; pos < resolution; ++pos) {
		double angle = pos*(360/resolution);
		evaldirections(pos,0) = cos(angle*3.141592654/180);
		evaldirections(pos,1) = sin(angle*3.141592654/180);
		//std::cout << "angle: " << angle <<  " -> " << evaldirections(pos,0) << ", " << evaldirections(pos,1) << std::endl;
	}

	//std::cout << "evaldirections " << evaldirections << std::endl << std::endl;
	
	vector_t<double> result1 = rounded1->multiEvaluate(evaldirections);
	//vector_t<double> result2 = rounded2.multiEvaluate(evaldirections);

	vector_t<double> sf1 = poly1->multiEvaluate(evaldirections);
	//vector_t<double> sf2 = poly2->multiEvaluate(evaldirections);
	vector_t<double> sf3 = ball->multiEvaluate(evaldirections);
	vector_t<double> sf4 = unionRes->multiEvaluate(evaldirections);
	vector_t<double> sf5 = poly3->multiEvaluate(evaldirections);
	vector_t<double> sf6 = intersectionRes->multiEvaluate(evaldirections);
	//std::cout << result << std::endl;
	
	
	// plotting 
	hypro::Plotter<double>& plotter = hypro::Plotter<double>::getInstance();
	plotter.setFilename("out");
	std::vector<Point<double>> points;

	
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = result1(i);
		vec(1) = result1(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	plotter.addObject(points);
	/*
	points.erase(points.begin(), points.end());
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = result2(i);
		vec(1) = result2(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	//plotter.addObject(points);
	*/
	
	points.erase(points.begin(), points.end());
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = sf1(i);
		vec(1) = sf1(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	plotter.addObject(points);
	
	
	points.erase(points.begin(), points.end());
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = sf3(i);
		vec(1) = sf3(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	plotter.addObject(points);
	
	
	/*
	std::shared_ptr<SupportFunction<double>> res = rounded1->linearTransformation(exponential);
	//std::shared_ptr<SupportFunction<double>> res = rounded1->minkowskiSum(ball);
	res->print();

	for(unsigned iteration = 0; iteration < 20; ++iteration) {
		std::cout << "Example: res.multiEvaluate(evaldirections)" << std::endl;
		vector_t<double> tmp = res->multiEvaluate(evaldirections);
		points.erase(points.begin(), points.end());
		for(int i = 0; i < resolution; ++i) {
			//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
			matrix_t<double> matr = matrix_t<double>(2,2);
			matr.row(0) = evaldirections.row(i);
			matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
			vector_t<double> vec = vector_t<double>(2);
			vec(0) = tmp(i);
			vec(1) = tmp(((i-1+resolution)%resolution));
			Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
			//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
			points.push_back(res);
		}
		std::cout << "iteration: " << iteration << std::endl;
		res = res->linearTransformation(exponential);
		//res = res->minkowskiSum(ball);
		res->print();
		plotter.addObject(points);
	}
	*/
	/*
	points.erase(points.begin(), points.end());
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = sf4(i);
		vec(1) = sf4(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	plotter.addObject(points);
	*/
	/*
	points.erase(points.begin(), points.end());
	for(int i = 0; i < resolution; ++i) {
		//std::cout << "Calculate intersection between " << i << " and " << ((i-1+resolution)%resolution) << std::endl;
		matrix_t<double> matr = matrix_t<double>(2,2);
		matr.row(0) = evaldirections.row(i);
		matr.row(1) = evaldirections.row(((i-1+resolution)%resolution));
		vector_t<double> vec = vector_t<double>(2);
		vec(0) = sf5(i);
		vec(1) = sf5(((i-1+resolution)%resolution));
		Point<double> res = Point<double>(matr.colPivHouseholderQr().solve(vec));
		//std::cout << "solve " << matr << " = " << vec << std::endl << " => " << res << std::endl << std::endl;
		points.push_back(res);
	}
	plotter.addObject(points);
	*/
	
	plotter.plot2d();
	
}