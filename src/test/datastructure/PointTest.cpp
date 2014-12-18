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
        // p1
        typename Point<Number>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, Number(2)) );
        coordinates1.insert( std::make_pair(y, Number(5)) );
        p1 = Point<Number>(coordinates1);

        // p2
        typename Point<Number>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(a, Number(7)) );
        coordinates2.insert( std::make_pair(b, Number(8)) );
        p2 = Point<Number>(coordinates2);

        // p3
        typename Point<Number>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(c, Number(9)) );
        coordinates3.insert( std::make_pair(d, Number(-13)) );
        p3 = Point<Number>(coordinates3);
        
        // p4
        typename Point<Number>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(c, Number(5)) );
        coordinates4.insert( std::make_pair(d, Number(8)) );
        p4 = Point<Number>(coordinates4);
    }

    virtual void TearDown()
    {
    }
	
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    Variable a = pool.getFreshVariable("a");
    Variable b = pool.getFreshVariable("b");
    Variable c = pool.getFreshVariable("c");
    Variable d = pool.getFreshVariable("d");
	
    Point<Number> p1;
    Point<Number> p2;
    Point<Number> p3;
    Point<Number> p4;
};

TYPED_TEST(PointTest, Constructor)
{ 
    Point<TypeParam> p;
    EXPECT_EQ(p.dimension(), (unsigned) 0);
    
    p = Point<TypeParam>(this->y, 5);
    EXPECT_EQ(p.dimension(), (unsigned) 1);
    
    p[this->pool.getFreshVariable()] = 2;
    p[this->pool.getFreshVariable()] = 2;
    p[this->pool.getFreshVariable()] = 2;
    p[this->pool.getFreshVariable()] = 2;
    p[this->pool.getFreshVariable()] = 2;
    p[this->pool.getFreshVariable()] = 2;

    EXPECT_EQ(p.dimension(), (unsigned) 7);
    EXPECT_EQ(p[this->y], TypeParam(5));
    
    Point<TypeParam> pCopy = Point<TypeParam>(p);
    EXPECT_EQ(p, pCopy);
    
    Point<TypeParam> empty = this->p1.newEmpty();
    EXPECT_EQ(this->p1.dimension(), empty.dimension());
    EXPECT_TRUE(this->p1.haveSameDimensions(empty));
    EXPECT_EQ(0, empty[this->x]);

    typename Point<TypeParam>::coordinateMap map;
    map.insert(std::make_pair(this->a, TypeParam(123)));
    map.insert(std::make_pair(this->b, TypeParam(456)));
    Point<TypeParam> tmp(map);
    EXPECT_EQ(tmp[this->a], TypeParam(123));
    EXPECT_EQ(tmp[this->b], TypeParam(456));
    
    // Test copy constructor and typecast constructor
    Point<double> alien;
    alien[this->pool.getFreshVariable()] = 1;
    alien[this->pool.getFreshVariable()] = 3;
    
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
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = this->p2.polarCoordinates(this->p2.origin(), false);
    expectedRes = sqrt(TypeParam(113));
    EXPECT_EQ(pc.at(0), expectedRes);
    
    pc = this->p3.polarCoordinates(this->p3.origin(), false);
    expectedRes = sqrt(TypeParam(250));
    EXPECT_EQ(pc.at(0), expectedRes);
    
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
    EXPECT_EQ(this->p1[this->x], TypeParam(2));
    EXPECT_EQ(this->p1[this->y], TypeParam(5));
    EXPECT_EQ(this->p1.coordinate(this->x), TypeParam(2));
    EXPECT_EQ(this->p1.coordinate(this->y), TypeParam(5));
    EXPECT_EQ(this->p1.dimension(), (unsigned) 2);
    
    this->p1.incrementInFixedDim(this->y);
    EXPECT_EQ(this->p1[this->y], TypeParam(6));
    this->p1.incrementInAllDim(TypeParam(3));
    EXPECT_EQ(this->p1[this->x], TypeParam(5));
    EXPECT_EQ(this->p1[this->y], TypeParam(9));
    this->p1.decrementInFixedDim(this->y);
    EXPECT_EQ(this->p1[this->y], TypeParam(8));
    
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
    EXPECT_EQ(this->p1[this->x], TypeParam(4));
    EXPECT_EQ(this->p1[this->y], TypeParam(10));

    EXPECT_TRUE(this->p2.move(this->p3));
    EXPECT_EQ(this->p2[this->a], TypeParam(7));
    EXPECT_EQ(this->p2[this->b], TypeParam(8));
    EXPECT_EQ(this->p2[this->c], TypeParam(9));
    EXPECT_EQ(this->p2[this->d], TypeParam(-13));
}

/**
 * @covers <>
 */
TYPED_TEST(PointTest, BinaryOperatorTest)
{
    EXPECT_TRUE(this->p4 > this->p3);
    EXPECT_TRUE(this->p3 < this->p4);
    EXPECT_FALSE(this->p4 < this->p3);
    EXPECT_FALSE(this->p3 > this->p4);
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
    EXPECT_TRUE(this->p2.isInBoundary(this->p1));
    EXPECT_TRUE(this->p1.isInBoundary(this->p1));
	
    this->p1[this->x] = TypeParam(3);
    
    EXPECT_TRUE(this->p1.hasDimension(this->x));
    EXPECT_FALSE(this->p1.hasDimension(this->a));
    EXPECT_FALSE(this->p2.hasDimension(this->x));
    EXPECT_TRUE(this->p2.hasDimension(this->a));

    this->p2[this->x] = TypeParam(4);
    this->p2[this->y] = TypeParam(5);
	
    EXPECT_TRUE(this->p1.haveEqualCoordinate(this->p1));
    EXPECT_FALSE(this->p1.haveEqualCoordinate(this->p3));
    this->p2.removeDimension(this->a);
    this->p2.removeDimension(this->b);
    EXPECT_LT(this->p1, this->p2);
	
    this->p2[this->x] = TypeParam(3);
    this->p2.removeDimension(this->a);
	
    EXPECT_EQ(this->p1, this->p2);
    EXPECT_NE(this->p1, this->p3);
    
    EXPECT_TRUE(this->p3.haveSameDimensions(this->p4));
    EXPECT_FALSE(this->p2.haveSameDimensions(this->p4));
    
    EXPECT_TRUE(this->p1.hasDimensions(this->p1.variables()));
    EXPECT_TRUE(this->p2.hasDimensions(this->p2.variables()));
    EXPECT_TRUE(this->p3.hasDimensions(this->p3.variables()));
    EXPECT_TRUE(this->p4.hasDimensions(this->p4.variables()));
    EXPECT_FALSE(this->p1.hasDimensions(this->p4.variables()));
    EXPECT_FALSE(this->p4.hasDimensions(this->p1.variables()));
    EXPECT_TRUE(this->p3.hasDimensions(this->p4.variables()));
    EXPECT_TRUE(this->p4.hasDimensions(this->p3.variables()));
}

TYPED_TEST(PointTest, Neighbours)
{
    std::vector<Point<TypeParam> > neighbours = this->p1.getAllNeighborsForAFixedDimension(this->y);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    this->p1.decrementInFixedDim(this->x);
    EXPECT_EQ(this->p1, neighbours[0]);
    
    this->p2[this->c] = TypeParam(3);
    neighbours = this->p2.getAllNeighborsForAFixedDimension(this->a);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    this->p2.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    this->p2.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    this->p2.incrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p2) != neighbours.end());
    
    this->p3[this->a] = TypeParam(2);
    this->p3[this->b] = TypeParam(7);
    neighbours = this->p3.getAllNeighborsForAFixedDimension(this->a);
    std::cout << "neighbours: ";
    for (auto n : neighbours) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
    this->p3.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.incrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->d);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.incrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->b);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
    this->p3.decrementInFixedDim(this->c);
    EXPECT_TRUE(std::find(neighbours.begin(), neighbours.end(), this->p3) != neighbours.end());
}

TYPED_TEST(PointTest, LinearTransformation) {
	typename hypro::matrix_t<TypeParam> A = createMatrix(std::vector<std::vector<TypeParam> >({
			std::vector<TypeParam>({4, 5}),
			std::vector<TypeParam>({-2, 3})
	}));

	typename hypro::vector_t<TypeParam> v = createVector(std::vector<TypeParam>({6, 1}));

    typename Point<TypeParam>::coordinateMap coordinates;

	this->p1.linearTransformation(A, v); // (2; 5)

	coordinates.clear();
	coordinates[this->x] = -3; coordinates[this->y] = 36;
	EXPECT_EQ(Point<TypeParam>(coordinates), this->p1);


	this->p2.linearTransformation(A, v); // (7; 8)

	coordinates.clear();
	coordinates[this->a] = 6; coordinates[this->b] = 73;
	EXPECT_EQ(Point<TypeParam>(coordinates), this->p2);


	this->p3.linearTransformation(A, v); // (9; -13)

	coordinates.clear();
	coordinates[this->c] = 54; coordinates[this->d] = -1;
	EXPECT_EQ(Point<TypeParam>(coordinates), this->p3);


	this->p4.linearTransformation(A, v); // (5; 8)

	coordinates.clear();
	coordinates[this->c] = 0; coordinates[this->d] = 63;
	EXPECT_EQ(Point<TypeParam>(coordinates), this->p4);
}
