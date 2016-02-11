/**
 * @file    ConverterTest.cpp
 * @covers  Converter
 *
 * @author  Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Simon Froitzheim
 *
 * @since	2015-05-13
 * @version     2015-12-16
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/conversion/Converter.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class ConverterTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
                //box
                std::vector<carl::Interval<Number>> boundaries;
                boundaries.push_back(carl::Interval<Number>(2,6));
                boundaries.push_back(carl::Interval<Number>(1,3));
                box = Box(boundaries);

                // first support function
                matrix = matrix_t<Number>(3,2);
		distances = vector_t<Number>(3);
		matrix << 1,1,
                        -1,1,
                        0,-1;
		distances << 1,1,0;

                support = hypro::SupportFunction<Number>(SF_TYPE::POLY, this->matrix, this->distances);

                // second support function (box)
                matrix2 = matrix_t<Number>(4,2);
                distances2 = vector_t<Number>(4);
                matrix2 << 0, 1, 0, -1, 1, 0, -1, 0;
                distances2 << 2, 2, 1, 1;

                support2 = hypro::SupportFunction<Number>(SF_TYPE::POLY, this->matrix2, this->distances2);

                //first zonotope
		vector_t<Number> center = vector_t<Number>(2);
		center << 2, 2;
		matrix_t<Number> generators = matrix_t<Number>(2,2);
		generators << 0, 1, 1, -1;
		zonotope = Zonotope<Number>(center, generators);

                //second zonotope (box)
                vector_t<Number> center2 = vector_t<Number>(2);
                center2 << 1, 1;
                matrix_t<Number> generators2 = matrix_t<Number>(2,2);
                generators2 << 0, 1, 1, 0;
                zonotope2 = Zonotope<Number>(center2, generators2);

                //first v-polytope (box)
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
		typename VPolytope::pointVector points;
		points.push_back(Point<Number>(p1));
		points.push_back(Point<Number>(p2));
		points.push_back(Point<Number>(p3));
		points.push_back(Point<Number>(p4));
		vpolytope = VPolytope(points);

                //second v-polytope
                vector_t<Number> p5 = vector_t<Number>(2);
                p5(0) = 0;
                p5(1) = 2;
                typename VPolytope::pointVector points2;
                points2.push_back(Point<Number>(p5));
                points2.push_back(Point<Number>(p2));
                points2.push_back(Point<Number>(p3));
                points2.push_back(Point<Number>(p4));
                vpolytope2 = VPolytope(points2);

                //alternative polytope
		std::vector<vector_t<Number>> coordinates;
		coordinates.push_back(p1);
		coordinates.push_back(p2);
		coordinates.push_back(p3);
		coordinates.push_back(p4);
		polytope = hypro::Polytope<Number>(coordinates);

                // A rectangle (for H-Polytope)
		Hyperplane<Number> hp1({1,0},2);
		Hyperplane<Number> hp2({0,1},2);
		Hyperplane<Number> hp3({-1,0},2);
		Hyperplane<Number> hp4({0,-1},2);

                planes.push_back(hp1);
		planes.push_back(hp2);
		planes.push_back(hp3);
		planes.push_back(hp4);

                hpolytope = HPolytope(this->planes);

                //second H-Polytope
                Hyperplane<Number> hp5({1,1},carl::rationalize<Number>(1.4));
                Hyperplane<Number> hp6({0,-1},1);
                Hyperplane<Number> hp7({-1,0},1);

                planes2.push_back(hp5);
                planes2.push_back(hp6);
                planes2.push_back(hp7);

                hpolytope2 = HPolytope(this->planes2);

    }

    virtual void TearDown()
    {
    }

    matrix_t<Number> matrix;
    matrix_t<Number> matrix2;
    vector_t<Number> distances;
    vector_t<Number> distances2;
    SupportFunction<Number> support;
    SupportFunction<Number> support2;

    Box box;

    hypro::Polytope<Number> polytope;
    VPolytope vpolytope;
    VPolytope vpolytope2;

    Zonotope<Number> zonotope;
    Zonotope<Number> zonotope2;

    typename HPolytope::HyperplaneVector planes;
    typename HPolytope::HyperplaneVector planes2;
    HPolytope hpolytope;
    HPolytope hpolytope2;
};

TYPED_TEST(ConverterTest, toBox)
{
	hypro::Box result;
	EXPECT_TRUE(convert(this->box, result));
        //std::cout << " Box: " << std::endl;
        //result.print();
	EXPECT_TRUE(convert(this->support, result));
        //std::cout << " Support:" << std::endl;
        //result.print();
        EXPECT_FALSE(convert(this->support, result, EXACT));
        //result.print();
        EXPECT_TRUE(convert(this->support2, result));
        //result.print();
        EXPECT_TRUE(convert(this->support2, result, EXACT));
        //result.print();
	EXPECT_TRUE(convert(this->vpolytope, result));
        //std::cout << " V:" << std::endl;
        //result.print();
        EXPECT_TRUE(convert(this->vpolytope, result, EXACT));
        //result.print();
        EXPECT_TRUE(convert(this->vpolytope2, result));
        //result.print();
        EXPECT_FALSE(convert(this->vpolytope2, result, EXACT));
        //result.print();
	EXPECT_TRUE(convert(this->zonotope, result));
        //std::cout << " Zonotope:" << std::endl;
        //result.print();
        EXPECT_FALSE(convert(this->zonotope, result, EXACT));
        //result.print();
        EXPECT_TRUE(convert(this->zonotope2, result));
        //result.print();
        EXPECT_TRUE(convert(this->zonotope2, result, EXACT));
        //result.print();
        EXPECT_TRUE(convert(this->hpolytope, result));
        //std::cout << " H:" << std::endl;
        //result.print();
        EXPECT_TRUE(convert(this->hpolytope, result, EXACT));
        //result.print();
        EXPECT_TRUE(convert(this->hpolytope2, result));
        //result.print();
        EXPECT_FALSE(convert(this->hpolytope2, result, EXACT));
        //result.print();
}

TYPED_TEST(ConverterTest, toHPolytope)
{

	SUCCEED();
}

TYPED_TEST(ConverterTest, toSupportFunction)
{
        SupportFunction<TypeParam> result = hypro::SupportFunction<TypeParam>();
        convert (this->support, result);
        //result.print();
        convert(this->hpolytope, result);
        //std::cout << " HPolytope: " << std::endl;
        //result.print();
        convert(this->hpolytope2, result);
        //result.print();
        convert(this->box, result);
        //std::cout << " Box: " << std::endl;
        //result.print();
        convert(this->vpolytope, result);
        //std::cout << " VPolytope: " << std::endl;
        //result.print();
        convert(this->vpolytope2, result);
        //result.print();
        convert(this->zonotope, result);
        //std::cout << " Zonotope: " << std::endl;
        //result.print();
        convert(this->zonotope2, result);
        //result.print();
	SUCCEED();
}

TYPED_TEST(ConverterTest, toVPolytope)
{
	SUCCEED();
}

TYPED_TEST(ConverterTest, toZonotope)
{
        Zonotope<TypeParam> result = hypro::Zonotope<TypeParam>();
        convert (this->zonotope, result);
        result.print();
        convert (this->box, result);
        std::cout << " Box: " << std::endl;
        result.print();
	SUCCEED();
}