
/**
 * \example example_box.cpp This example shows how to use a box representation. It covers creation of a box, an affine transformation
 * of the created box as well as the intersection with a half space and an included test for emptiness of the resulting set.
 */

#include "representations/GeometricObject.h"
#include "datastructures/Halfspace.h"
#include "util/plotting/Plotter.h"
#include <sys/time.h>

int main()
{
	// use rational arithmetic.
	typedef mpq_class Number;
	struct timeval t1, t2;
    	double elapsedTime;

	// create a box out of two given limit points.
	hypro::Box<Number> box1(std::make_pair(hypro::Point<Number>({-2,2,-4}), hypro::Point<Number>({2,4,-2})));

	// create some transformation matrix.
	hypro::matrix_t<Number> A = hypro::matrix_t<Number>::Zero(3,3);
	A(0,0) = 1;
	A(1,1) = carl::convert<double,Number>(carl::cos(45));
	A(1,2) = carl::convert<double,Number>(-carl::sin(45));
	A(2,1) = carl::convert<double,Number>(carl::sin(45));
	A(2,2) = carl::convert<double,Number>(carl::cos(45));

	// create some translation vector.
	hypro::vector_t<Number> b = hypro::vector_t<Number>::Zero(3);
	b(0) = 1;
	b(1) = 2;
	b(2) = 3;

	std::cout << "------------------------------"<< std::endl;
 	std::cout << "vertices" << std::endl;
 	std::cout << "------------------------------"<< std::endl;

	// start timer
	gettimeofday(&t1, NULL);

	// compute all vertices of the box and output them.
	std::vector<hypro::Point<Number>> tvertices = box1.vertices();

	// stop timer
	gettimeofday(&t2, NULL);
	
	
	for(const auto& vertex : tvertices)
		std::cout << vertex << std::endl;

	std::cout << box1 << std::endl;
	

	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	std::cout << "Time spent: " << elapsedTime << "ms\n" << std::endl;

	std::cout << "------------------------------"<< std::endl;
 	std::cout << "Minkowski sum" << std::endl;
 	std::cout << "------------------------------"<< std::endl;
	
	hypro::Box<Number> box2(std::make_pair(hypro::Point<Number>({7,-12,-4}), hypro::Point<Number>({20,0,-2})));

	// start timer
	gettimeofday(&t1, NULL);

	// compute all vertices of the box and output them.
		
	hypro::Box<Number> res = box1.minkowskiSum(box2);
	// stop timer
	gettimeofday(&t2, NULL);
	
	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	std::cout << "Time spent: " << elapsedTime << "ms\n" << std::endl;
	
	std::cout << "------------------------------"<< std::endl;
 	std::cout << "Affine transformation" << std::endl;
 	std::cout << "------------------------------"<< std::endl;	
	
	// start timer
	gettimeofday(&t1, NULL);

	// transform the initial box with the created matrix and vector (affine transformation).
	hypro::Box<Number> res2 = box1.affineTransformation(A,b);

	std::vector<hypro::Point<Number>> tve = res2.vertices();
	for(const auto& vertex : tve)
		std::cout << vertex << std::endl;

	// stop timer
	gettimeofday(&t2, NULL);
	
	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	std::cout << "Time spent: " << elapsedTime << "ms\n" << std::endl;


 	std::cout << "------------------------------"<< std::endl;
 	std::cout << "union" << std::endl;
 	std::cout << "------------------------------"<< std::endl;

	// start timer
	gettimeofday(&t1, NULL);

	hypro::Box<Number> res3 = box1.unite(box2);
	// stop timer
	gettimeofday(&t2, NULL);
	
	std::vector<hypro::Point<Number>> tve2 = res3.vertices();
	for(const auto& vertex : tve2)
		std::cout << vertex << std::endl;
	
	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	std::cout << "Time spent: " << elapsedTime << "ms\n" << std::endl;
	
	std::cout << "------------------------------"<< std::endl;
 	std::cout << "intersect" << std::endl;
 	std::cout << "------------------------------"<< std::endl;

	// start timer
	gettimeofday(&t1, NULL);

	hypro::Box<Number> res4 = box1.intersect(box2);
	
	// stop timer
	gettimeofday(&t2, NULL);
	
	std::vector<hypro::Point<Number>> tve3 = res4.vertices();
	for(const auto& vertex : tve3)
		std::cout << vertex << std::endl;
	
	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

	std::cout << "Time spent: " << elapsedTime << "ms\n" << std::endl;
	
	
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	
//	carl::Interval<Number> intv1 = new carl::Interval<Number>(0,1);
//	carl::Interval<Number> intv2 = new carl::Interval<Number>(1,1);

//	carl::Interval<Number> res1 = intv1 + intv2;

	return 0;
}

