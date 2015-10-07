/**
 * This file holds an example to test SMT-RAT for Vpolytope reduction techniques.
 * @file example_useSMT.cpp
 */

#include "../src/lib/representations/Polytopes/VPolytope/VPolytope.h"
#include <random>

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;


	std::cout << "Reduce 1-polytope." << std::endl;
	// create v-poly 1-dim
	VPolytope<Number> onePoly;
	onePoly.insert(Point<Number>({1}));
	onePoly.insert(Point<Number>({-1}));
	onePoly.insert(Point<Number>({2}));

	std::cout << onePoly << std::endl;
	onePoly.removeRedundancy();
	std::cout << onePoly << std::endl;

	std::cout << "Reduce 2-polytope." << std::endl;
	// create v-poly 2-dim
	VPolytope<Number> twoPoly;
	twoPoly.insert(Point<Number>({-1,-1}));
	twoPoly.insert(Point<Number>({1,2}));
	twoPoly.insert(Point<Number>({-1,2}));
	twoPoly.insert(Point<Number>({1,-1}));
	twoPoly.insert(Point<Number>({0,1}));

	std::cout << twoPoly << std::endl;
	twoPoly.removeRedundancy();
	std::cout << twoPoly << std::endl;


	std::cout << "Reduce 3-polytope." << std::endl;
	// create v-poly 3-dim
	VPolytope<Number> threePoly;
	threePoly.insert(Point<Number>({-1,-1,-1}));
	threePoly.insert(Point<Number>({-1,-1,1}));
	threePoly.insert(Point<Number>({-1,1,-1}));
	threePoly.insert(Point<Number>({-1,1,1}));
	threePoly.insert(Point<Number>({1,-1,-1}));
	threePoly.insert(Point<Number>({1,-1,1}));
	threePoly.insert(Point<Number>({1,1,-1}));
	threePoly.insert(Point<Number>({1,1,1}));

	// add inside-points
	std::mt19937 mRand;
	std::uniform_real_distribution<Number> distr (Number(-1), Number(1));
	for(unsigned i = 0; i < 1000; ++i)
		threePoly.insert(Point<Number>({Number(distr(mRand)), Number(distr(mRand)), Number(distr(mRand))}));

	std::cout << threePoly << std::endl;
	threePoly.removeRedundancy();
	std::cout << threePoly << std::endl;

	return 0;
}