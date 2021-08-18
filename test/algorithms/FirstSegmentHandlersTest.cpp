/**
 * FirstSegmentHandlersTest.cpp
 *
 * Test suite for all types of FirstSegmentHandlers.
 *
 * @author Phillip Tse
 * @date 17.12.2019
 */

#include "../../hypro/algorithms/reachability/handlers/firstSegmentHandlers/TPolyFirstSegmentHandler.h"
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"

using namespace hypro;

template <typename Number>
class FirstSegmentHandlersTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		// triangle with corner points (0,0),(1,2),(2,0)
		triangleMat = matrix_t<Number>::Zero( 3, 2 );
		triangleMat << -1, 2, 1, 2, 0, -1;
		triangleVec = vector_t<Number>::Zero( 3 );
		triangleVec << 0, 2, 0;

		// box with corner points (2,2)(-2,2)(2,-2)(-2,-2)
		boxMat = matrix_t<Number>::Zero( 4, 2 );
		boxMat << 1, 0, -1, 0, 0, 1, 0, -1;
		boxVec = vector_t<Number>::Zero( 4 );
		boxVec << 2, 2, 2, 2;

		// halfspace parallel to y-axis
		positiveXWallMat = matrix_t<Number>::Zero( 1, 2 );
		positiveXWallMat << 1, 0;
		positiveXWallVec = vector_t<Number>::Zero( 1 );
		positiveXWallVec << 1;

		// outgoingFlow will increase x and y steadily
		outgoingFlow = matrix_t<Number>::Zero( 3, 3 );
		outgoingFlow << 2, 1, 0,  // increases x
			  0, 2, 1,			  // doubles y and adds 1
			  0, 0, 0;
		outgoingLoc = Location<Number>( outgoingFlow );
		outgoingLoc.setName( "outgoingLoc" );

		// trappingFlow will eventually direct everything to (0,0) and is therefore a posivite invariant
		trappingFlow = matrix_t<Number>::Zero( 3, 3 );
		trappingFlow << 0.5, 0.5, 0,  // shrinks x every timestep, never reaching 0
			  0.5, 0.5, 0,			  // shrinks y every timestep, never reaching 0
			  0, 0, 0;
		trappingLoc = Location<Number>( trappingFlow );
		trappingLoc.setName( "trappingLoc" );
	}

	virtual void TearDown() {}

	/* Shapes for representations or invariants */

	// Triangle
	matrix_t<Number> triangleMat;
	vector_t<Number> triangleVec;

	// Box
	matrix_t<Number> boxMat;
	vector_t<Number> boxVec;

	// Unbounded wall in x direction, a halfspace parallel to the y axis
	matrix_t<Number> positiveXWallMat;
	vector_t<Number> positiveXWallVec;

	/* Locations with different properties */

	// Outgoing location with no invariant attached yet
	matrix_t<Number> outgoingFlow;
	Location<Number> outgoingLoc;

	// Trapping location with no invariant attached yet
	matrix_t<Number> trappingFlow;
	Location<Number> trappingLoc;

	/* Different Representations */

	// Representations
	struct LocInvStrenghtening : TemplatePolyhedronDefault {
		static constexpr bool USE_LOCATION_INVARIANT_STRENGTHENING = true;
	};
	struct NoLocInvStrenghtening : TemplatePolyhedronDefault {
		static constexpr bool USE_LOCATION_INVARIANT_STRENGTHENING = false;
	};
	using TPolyLIS = TemplatePolyhedronT<Number, Converter<Number>, LocInvStrenghtening>;
	using TPolyNoLIS = TemplatePolyhedronT<Number, Converter<Number>, NoLocInvStrenghtening>;
	TPolyLIS tpoly;
	TPolyNoLIS tpolyNoLIS;

	/* States */

	// Empty state - just set locations and representations as needed for every test
	State_t<Number> state;

	/* Other parameters needed to initialize a FirstSegmentHandler */

	std::size_t index = 0;
	tNumber timestep = tNumber( 0.1 );
};

// One test for each FirstSegmentHandler
// TYPED_TEST(FirstSegmentHandlersTest, Timed){}
// TYPED_TEST(FirstSegmentHandlersTest, TimedElapse){}
// TYPED_TEST(FirstSegmentHandlersTest, Rectangular){}
// TYPED_TEST(FirstSegmentHandlersTest, LTI){}

/* TPolyFirstSegmentHandler Tests */

/*
TYPED_TEST(FirstSegmentHandlersTest, LieDerivative){

	//Initialize with box shaped tpoly and outgoing flow
	this->tpoly = typename FirstSegmentHandlersTest<TypeParam>::TPoly(this->boxMat, this->boxVec);
	this->state = State_t<TypeParam>(&this->outgoingLoc);
	this->state.setSet(this->tpoly,0);
	TPolyFirstSegmentHandler<State_t<TypeParam>> handler(&this->state, this->index, this->timestep);
	auto res = handler.lieDerivative(vector_t<TypeParam>::Ones(3));
	vector_t<TypeParam> controlVec = vector_t<TypeParam>::Zero(3);
	controlVec << 2,3,1;
	EXPECT_EQ(res,controlVec);

}
*/

TYPED_TEST( FirstSegmentHandlersTest, TemplatePoly ) {
	/* TEST 1: Location has no invariant */

	// Initialize handler with box shaped tpoly and outgoing flow
	this->tpoly = typename FirstSegmentHandlersTest<TypeParam>::TPolyLIS( this->boxMat, this->boxVec );
	this->state = State_t<TypeParam>( &this->outgoingLoc );
	this->state.setSet( this->tpoly, 0 );
	TPolyFirstSegmentHandler<State_t<TypeParam>> handler( &this->state, this->index, this->timestep );

	// Test whether segment progressed -> all offset values got bigger
	handler.handle();
	auto res1 = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<TypeParam>>(), this->state.getSet( 0 ) );
	EXPECT_TRUE( this->state.getLocation() == &this->outgoingLoc );
	EXPECT_EQ( handler.getRelaxedInvariant(), std::nullopt );
	// EXPECT_EQ(handler.getRelaxedInvariant(), vector_t<TypeParam>::Zero(2));
	EXPECT_EQ( res1.matrix(), this->tpoly.matrix() );
	EXPECT_EQ( res1.rGetMatrixPtr(), this->tpoly.rGetMatrixPtr() );
	for ( int i = 0; i < res1.matrix().rows(); ++i ) {
		EXPECT_TRUE( res1.vector()( i ) > this->tpoly.vector()( i ) );
	}

	/* TEST 2: Location has partially bounded invariant */

	// Initialize handler with box shaped tpoly and outgoing flow and partially bounded invariant
	// The rest if implicitly affected by this.
	this->outgoingLoc.setInvariant( Condition<TypeParam>( this->positiveXWallMat, this->positiveXWallVec ) );
	EXPECT_FALSE( this->state.getLocation()->getInvariant().empty() );
	this->tpoly = typename FirstSegmentHandlersTest<TypeParam>::TPolyLIS( this->boxMat, this->boxVec );

	// Test whether segment progressed -> all offset values got bigger
	handler.handle();
	auto res2 = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<TypeParam>>(), this->state.getSet( 0 ) );
	EXPECT_TRUE( this->state.getLocation() == &this->outgoingLoc );
	// EXPECT_EQ(handler.getRelaxedInvariant(), vector_t<TypeParam>::Zero(2));
	EXPECT_EQ( handler.getRelaxedInvariant(), std::nullopt );
	EXPECT_EQ( res2.matrix(), this->tpoly.matrix() );
	for ( int i = 0; i < res2.matrix().rows(); ++i ) {
		EXPECT_TRUE( res2.vector()( i ) > this->tpoly.vector()( i ) );
		EXPECT_TRUE( res2.vector()( i ) > res1.vector()( i ) );
	}

	/* TEST 3: Location has completely bounded invariant but outgoing/negative flow */

	// Location with box invariant corners (6,6)(-6,6)(6,-6)(-6,-6)
	this->outgoingLoc.setInvariant( Condition<TypeParam>( this->boxMat, 3 * this->boxVec ) );
	this->tpoly = typename FirstSegmentHandlersTest<TypeParam>::TPolyLIS( this->boxMat, this->boxVec );

	// Test whether segment progressed -> all offset values got bigger
	handler.handle();
	auto res3 = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<TypeParam>>(), this->state.getSet( 0 ) );
	EXPECT_TRUE( this->state.getLocation() == &this->outgoingLoc );
	// EXPECT_EQ(handler.getRelaxedInvariant(), vector_t<TypeParam>::Zero(2));
	EXPECT_EQ( handler.getRelaxedInvariant(), std::nullopt );
	EXPECT_EQ( res3.matrix(), this->tpoly.matrix() );
	for ( int i = 0; i < res3.matrix().rows(); ++i ) {
		EXPECT_TRUE( res3.vector()( i ) > this->tpoly.vector()( i ) );
		EXPECT_TRUE( res3.vector()( i ) > res2.vector()( i ) );
	}

	/* TEST 4: Location has completely bounded invariant but inwards/positive flow */

	// Location with box invariant but positive flow
	this->trappingLoc.setInvariant( Condition<TypeParam>( this->boxMat, 3 * this->boxVec ) );
	this->state.setLocation( &this->trappingLoc );
	this->tpoly = typename FirstSegmentHandlersTest<TypeParam>::TPolyLIS( this->boxMat, this->boxVec );

	// Test whether segment progressed -> all offset values got bigger
	handler.handle();
	auto res4 = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<TypeParam>>(), this->state.getSet( 0 ) );
	EXPECT_TRUE( this->state.getLocation() == &this->trappingLoc );
	// EXPECT_EQ(handler.getRelaxedInvariant(), vector_t<TypeParam>::Zero(2));
	EXPECT_EQ( handler.getRelaxedInvariant(), std::nullopt );
	EXPECT_EQ( res4.matrix(), this->tpoly.matrix() );
	for ( int i = 0; i < res4.matrix().rows(); ++i ) {
		EXPECT_TRUE( res4.vector()( i ) > this->tpoly.vector()( i ) );
		EXPECT_TRUE( res4.vector()( i ) > res3.vector()( i ) );
	}

	/* TEST 5: Test with Setting USE_LOCATION_INVARIANT_STRENGTHENING off */

	/* TEST 6: Test with Setting DIRECTLY_COMPUTE_ROOTS off */
}
