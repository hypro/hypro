/**
 * @file    ConverterTest.cpp
 * @covers  Converter
 * 
 * @author  Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-05-13
 * @version 2015-05-13
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/Converter.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class ConverterTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
        std::map<const carl::Variable, carl::Interval<Number> > boundaries;
        boundaries.insert(std::make_pair(x, carl::Interval<Number>(2,6)));
        boundaries.insert(std::make_pair(y, carl::Interval<Number>(1,3)));
        box = hypro::Box<Number>(boundaries);

        matrix = matrix_t<Number>(3,2);
		distances = vector_t<Number>(3);
		matrix << 1,1,
			-1,1,
			0,-1,
		distances << 1,1,0;

		vector_t<Number> center = vector_t<Number>(2);
		center << 2.0, 2.0;
		matrix_t<Number> generators = matrix_t<Number>(2,2);
		generators << 0.0, 1.0, 1.0, -1.0;
		zonotope = Zonotope<Number>(center, generators);

		vector_t<Number> p1 = vector_t<Number>(2);
		p1(0) = 1;
		p1(1) = 2;
		vector_t<Number> p2 = vector_t<Number>(2);
		p2(0) = 3;
		p2(1) = 2;
		vector_t<Number> p3 = vector_t<Number>(2);
		p3(0) = 3;
		p3(1) = 4;
		vector_t<Number> p4 = vector_t<Number>(2);
		p4(0) = 1;
		p4(1) = 4;
		typename VPolytope<Number>::pointVector points;
		points.push_back(Point<Number>(p1));
		points.push_back(Point<Number>(p2));
		points.push_back(Point<Number>(p3));
		points.push_back(Point<Number>(p4));
		vpolytope = VPolytope<Number>(points);

		std::vector<vector_t<Number>> coordinates;
		coordinates.push_back(p1);
		coordinates.push_back(p2);
		coordinates.push_back(p3);
		coordinates.push_back(p4);
		polytope = hypro::Polytope<Number>(coordinates);
    }
	
    virtual void TearDown()
    {
    }
	
    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    carl::Variable x;
    carl::Variable y;

    matrix_t<Number> matrix;
    vector_t<Number> distances;

    hypro::Box<Number> box;
    hypro::Polytope<Number> polytope;
    VPolytope<Number> vpolytope;
    Zonotope<Number> zonotope;
    
};

TYPED_TEST(ConverterTest, toBox)
{
	std::shared_ptr<hypro::SupportFunction<TypeParam>> supportFunction = hypro::SupportFunction<TypeParam>::create(SF_TYPE::POLY, this->matrix, this->distances);
	hypro::Box<TypeParam> result;
	convert(this->box, result);
	convert(this->polytope, result);
	convert(supportFunction, result);
	convert(this->vpolytope, result);
	convert(this->zonotope, result);
	SUCCEED();
}

TYPED_TEST(ConverterTest, toPolytope)
{
	SUCCEED();
}

TYPED_TEST(ConverterTest, toSupportFunction)
{
	SUCCEED();
}

TYPED_TEST(ConverterTest, toVPolytope)
{
	SUCCEED();
}

TYPED_TEST(ConverterTest, toZonotope)
{
	SUCCEED();
}