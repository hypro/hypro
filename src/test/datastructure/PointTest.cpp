/**
 *  Testfile for the point datastructure.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Benedikt Seidl
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/util/types.h"
#include "../../lib/datastructures/Point.h"
#include <carl/core/VariablePool.h>
#include "carl/numbers/numbers.h"
#include <mpfr.h>

using namespace hypro;
using namespace carl;

template<typename Number>
class PointTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
		a = pool.newCarlVariable();
		b = pool.newCarlVariable();
        // p1
//        typename Point<Number>::coordinateMap coordinates1;
//        coordinates1.insert( std::make_pair(x, Number(2)) );
//        coordinates1.insert( std::make_pair(y, Number(5)) );
        p1 = Point<Number>({2,5});

        // p2
//        typename Point<Number>::coordinateMap coordinates2;
//        coordinates2.insert( std::make_pair(a, Number(7)) );
//        coordinates2.insert( std::make_pair(b, Number(8)) );
        p2 = Point<Number>({7,8});

        // p3
//        typename Point<Number>::coordinateMap coordinates3;
//        coordinates3.insert( std::make_pair(c, Number(9)) );
//        coordinates3.insert( std::make_pair(d, Number(-13)) );
        p3 = Point<Number>({9,-13});
        
        // p4
//        typename Point<Number>::coordinateMap coordinates4;
//        coordinates4.insert( std::make_pair(c, Number(5)) );
//        coordinates4.insert( std::make_pair(d, Number(8)) );
        p4 = Point<Number>({5,8});
    }

    virtual void TearDown()
    {
    }
	
    hypro::VariablePool& pool = hypro::VariablePool::getInstance();
    carl::Variable x;
    carl::Variable y;
    carl::Variable a;
    carl::Variable b;
//    Variable c = pool.getFreshVariable("c");
//    Variable d = pool.getFreshVariable("d");
	
    Point<Number> p1;
    Point<Number> p2;
    Point<Number> p3;
    Point<Number> p4;
};

TYPED_TEST(PointTest, Constructor)
{ 
    Point<TypeParam> p;
    EXPECT_EQ(p.dimension(), (unsigned) 0);
    
    p = Point<TypeParam>(5);
    EXPECT_EQ(p.dimension(), (unsigned) 1);


    p[2] = 5;
    p[3] = 2;
    p[4] = 2;
    p[5] = 2;
    p[6] = 2;
    p[7] = 2;

    EXPECT_EQ(p.dimension(), (unsigned) 8);
    EXPECT_EQ(p[2], TypeParam(5));
    EXPECT_EQ(p[1], TypeParam(0));
    EXPECT_EQ(p[0], TypeParam(5));
    	
    Point<TypeParam> pCopy(p);
    EXPECT_EQ(p, pCopy);
    
    Point<TypeParam> empty = this->p1.newEmpty();
    EXPECT_EQ(this->p1.dimension(), empty.dimension());
    EXPECT_TRUE(this->p1.haveSameDimensions(empty));
    EXPECT_EQ(0, empty[1]);

    Point<TypeParam> tmp({123,456});
    EXPECT_EQ(tmp[0], TypeParam(123));
    EXPECT_EQ(tmp[1], TypeParam(456));
    
    // Test copy constructor and typecast constructor
    Point<double> alien = Point<double>({1,3});
    
    Point<double> alien2 = alien;
    Point<float> local = alien;

    
#ifdef SUPPORT_MPFR
    // convert to mpfr
    Point<carl::FLOAT_T<mpfr_t>> local2 = alien;
#endif
}

TYPED_TEST(PointTest, PolarCoordinates)
{
    std::vector<TypeParam> pc = this->p1.polarCoordinates(this->p1.origin(), false);
    TypeParam expectedRes;
    expectedRes = sqrt(TypeParam(29));
	// special case: Use double comparison
	if( hypro::eqTypes<double,TypeParam>() ) {
		EXPECT_TRUE(carl::AlmostEqual2sComplement(pc.at(0), expectedRes, 1));
	} else {
		EXPECT_EQ(pc.at(0), expectedRes);
	}
    
    
    pc = this->p2.polarCoordinates(this->p2.origin(), false);
    expectedRes = sqrt(TypeParam(113));
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = this->p3.polarCoordinates(this->p3.origin(), false);
    expectedRes = sqrt(TypeParam(250));
    if( hypro::eqTypes<double,TypeParam>() ) {
		EXPECT_TRUE(carl::AlmostEqual2sComplement(pc.at(0), expectedRes, 1));
	} else {
		EXPECT_EQ(pc.at(0), expectedRes);
	}
    
    pc = this->p4.polarCoordinates(this->p3, false);
}

/**
 * @covers Point::coordinate
 * @covers Point::dimension
 * @covers Point::IncrementInFixedDim
 * @covers Point::IncrementInAllDim
 * @covers Point::DecrementInFixedDim
 * @covers Point::setCoordinate
 */
TYPED_TEST(PointTest, CoordinateDimensionTest)
{
    EXPECT_EQ(this->p1[0], TypeParam(2));
    EXPECT_EQ(this->p1[1], TypeParam(5));
    EXPECT_EQ(this->p1.coordinate(0), TypeParam(2));
    EXPECT_EQ(this->p1.coordinate(1), TypeParam(5));
    EXPECT_EQ(this->p1.dimension(), (unsigned) 2);
    
    this->p1.incrementInFixedDim(1);
    EXPECT_EQ(this->p1[1], TypeParam(6));
    this->p1.incrementInAllDim(TypeParam(3));
    EXPECT_EQ(this->p1[0], TypeParam(5));
    EXPECT_EQ(this->p1[1], TypeParam(9));
    this->p1.decrementInFixedDim(1);
    EXPECT_EQ(this->p1[1], TypeParam(8));
	
    this->p1[this->x] = TypeParam(3);
    this->p1[this->y] = TypeParam(-1);
    EXPECT_EQ(this->p1[this->x], TypeParam(3));
    EXPECT_EQ(this->p1[this->y], TypeParam(-1));
    this->p1.setCoordinate(this->x, 4);
    this->p1.setCoordinate(this->y, 7);
    EXPECT_EQ(this->p1[this->x], TypeParam(4));
    EXPECT_EQ(this->p1[this->y], TypeParam(7));
}

/**
 * @covers Point::move
 */
TYPED_TEST(PointTest, OperationTest)
{
    EXPECT_FALSE(this->p1.move(this->p1));
    EXPECT_EQ(this->p1[0], TypeParam(4));
    EXPECT_EQ(this->p1[1], TypeParam(10));

    EXPECT_TRUE(this->p2.move(this->p3));
    EXPECT_EQ(this->p2[0], TypeParam(16));
    EXPECT_EQ(this->p2[1], TypeParam(-5));
}

/**
 * @covers <>
 */
TYPED_TEST(PointTest, BinaryOperatorTest)
{
    EXPECT_FALSE(this->p4 > this->p3);
    EXPECT_FALSE(this->p3 < this->p4);
    EXPECT_TRUE(this->p4 < this->p3);
    EXPECT_TRUE(this->p3 > this->p4);
    EXPECT_FALSE(this->p4 < this->p4);
    EXPECT_FALSE(this->p4 > this->p4);
    EXPECT_EQ(this->p4, this->p4);
    EXPECT_NE(this->p3, this->p4);
}

/**
 * @covers Point::isInBoundary
 * @covers Point::compareReducedDimension
 * @covers Point::haveEqualCoordinate
 */
TYPED_TEST(PointTest, BooleanTest)
{
    EXPECT_TRUE(this->p1.isInBoundary(this->p2));
    EXPECT_FALSE(this->p2.isInBoundary(this->p1));
    EXPECT_FALSE(this->p1.isInBoundary(this->p1));
	
    this->p1[1] = TypeParam(3);
    
    EXPECT_TRUE(this->p1.hasDimension(this->x));
    EXPECT_FALSE(this->p1.hasDimension(this->a));
    EXPECT_TRUE(this->p2.hasDimension(this->x));
    EXPECT_FALSE(this->p2.hasDimension(this->a));

    this->p2[0] = TypeParam(2);
    this->p2[1] = TypeParam(5);
	
    EXPECT_TRUE(this->p1.haveEqualCoordinate(this->p1));
    EXPECT_FALSE(this->p1.haveEqualCoordinate(this->p3));
//    this->p2.removeDimension(this->a);
//    this->p2.removeDimension(this->b);
//    EXPECT_LT(this->p1, this->p2);
	
    this->p2[1] = TypeParam(3);
//    this->p2.removeDimension(this->a);
	
    EXPECT_EQ(this->p1, this->p2);
    EXPECT_NE(this->p1, this->p3);
    
    EXPECT_TRUE(this->p3.haveSameDimensions(this->p4));
    EXPECT_TRUE(this->p2.haveSameDimensions(this->p4));
    
//    EXPECT_TRUE(this->p1.hasDimensions(this->p1.variables()));
//    EXPECT_TRUE(this->p2.hasDimensions(this->p2.variables()));
//    EXPECT_TRUE(this->p3.hasDimensions(this->p3.variables()));
//    EXPECT_TRUE(this->p4.hasDimensions(this->p4.variables()));
//    EXPECT_FALSE(this->p1.hasDimensions(this->p4.variables()));
//    EXPECT_FALSE(this->p4.hasDimensions(this->p1.variables()));
//    EXPECT_TRUE(this->p3.hasDimensions(this->p4.variables()));
//    EXPECT_TRUE(this->p4.hasDimensions(this->p3.variables()));
}

TYPED_TEST(PointTest, LinearTransformation) {
	typename hypro::matrix_t<TypeParam> A = createMatrix(std::vector<std::vector<TypeParam> >({
			std::vector<TypeParam>({4, 5}),
			std::vector<TypeParam>({-2, 3})
	}));

	typename hypro::vector_t<TypeParam> v = createVector(std::vector<TypeParam>({6, 1}));
	typename Point<TypeParam>::coordinateMap coordinates;

	EXPECT_EQ(Point<TypeParam>({39,12}), this->p1.linearTransformation(A, v));
	EXPECT_EQ(Point<TypeParam>({74,11}), this->p2.linearTransformation(A, v));
	EXPECT_EQ(Point<TypeParam>({-23,-56}), this->p3.linearTransformation(A, v));
	EXPECT_EQ(Point<TypeParam>({66,15}), this->p4.linearTransformation(A, v));
}
