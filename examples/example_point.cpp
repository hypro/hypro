/*
 * File:   example_point.cpp
 * Author: Johannes Neuhaus
 *
 * Created on November 16, 2015
 */

#include <random>
#include <chrono>
#include "../src/hypro/datastructures/Point.h"
#include <mpfr.h>
typedef carl::FLOAT_T<mpfr_t> number_t;

int* createArray(int firstElem, int* arr, size_t size) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000);
    arr[0] = firstElem; // if wanted force different points
    for (size_t i = 1; i < size; i++) {
        arr[i] = distribution(generator);
    }
    return arr;
}

int main(void) {
	/*
    //typedef
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::nanoseconds timeunit;

    hypro::Point<number_t> p1;
	hypro::Point<number_t> p2;
    size_t MAX_DIMENSION = 10;

    for (size_t i = 1; i < MAX_DIMENSION; i++) {
        int arr[i];
        p1 = hypro::Point<number_t>(*createArray(1, arr, i));
    	p2 = hypro::Point<number_t>(*createArray(2, arr, i));
        clock::time_point start = clock::now();
        bool testresult = p1 == p2;
        clock::time_point end = clock::now();

        std::cout
            << "Comparison result Dimension "
            << i
            << " run 1 in "
            << std::chrono::duration_cast<timeunit>( end - start ).count()
            << ": "
            << testresult
            << "\n";

        start = clock::now();
        testresult = p1 == p2;
        end = clock::now();
        std::cout
            << "Comparison result Dimension "
            << i
            << " run 2 in "
            << std::chrono::duration_cast<timeunit>( end - start ).count()
            << ": "
            << testresult
            << "\n";
        assert(p1 != p2);
    }
    return 0;
    */

    auto reduce = [=](Point<Number> orig) -> Point<Number> { return Point<Number>(orig.rawCoordinates().conservativeResize(orig.rawCoordinates().rows()-1, Eigen::NoChange_t)) };

	hypro::Point<Number> test({1,2,3,4});
	std::cout << test << std::endl;
	test = reduce(test);
	std::cout << test << std::endl;

	return 0;
}
