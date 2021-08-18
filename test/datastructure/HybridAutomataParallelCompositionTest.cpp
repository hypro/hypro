/**
 * Testfile for parallel composition of hybrid automata.
 */

#include "../defines.h"
#include "carl/core/VariablePool.h"
#include "datastructures/HybridAutomaton/Condition.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/Reset.h"
#include "datastructures/HybridAutomaton/State.h"
#include "datastructures/HybridAutomaton/Transition.h"
#include "representations/GeometricObjectBase.h"
#include "gtest/gtest.h"

using namespace hypro;
using namespace carl;

template <typename Number>
using valuation_t = VPolytope<Number>;

template <typename Number>
class HybridAutomataParallelCompositionTest : public ::testing::Test {
	/**
	 * Test Setup:
	 * Something
	 */
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

/**
 * combine condition test, also overs combine for matrix_t
 */
TYPED_TEST( HybridAutomataParallelCompositionTest, combineCondition ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Condition<TypeParam> firstCondition;
	Condition<TypeParam> secondCondition;
	Condition<TypeParam> resultCondition;
	matrix_t<TypeParam> firstInvariant;
	vector_t<TypeParam> firstInvConsts;
	matrix_t<TypeParam> secondInvariant;
	vector_t<TypeParam> secondInvConsts;
	matrix_t<TypeParam> resultInvariant;
	vector_t<TypeParam> resultInvConsts;

	// no shared variables
	haVar = { "a", "b", "c", "d" };
	lhsVar = { "a", "c" };
	rhsVar = { "b", "d" };

	// two empty conditions
	EXPECT_EQ( Condition<TypeParam>(),
			   combine( Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	firstInvariant = matrix_t<TypeParam>( 2, 2 );
	firstInvariant << 3, 1, 1, 2;
	firstInvConsts = vector_t<TypeParam>( 2 );
	firstInvConsts << 0, 1;
	firstCondition = Condition<TypeParam>( firstInvariant, firstInvConsts );

	resultInvariant = matrix_t<TypeParam>( 2, 4 );
	resultInvariant << 3, 0, 1, 0, 1, 0, 2, 0;
	resultInvConsts = vector_t<TypeParam>( 2 );
	resultInvConsts << 0, 1;
	resultCondition = Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	secondInvariant = matrix_t<TypeParam>( 2, 2 );
	secondInvariant << 1, 1, 1, 2;
	secondInvConsts = vector_t<TypeParam>( 2 );
	secondInvConsts << 0, 1;
	secondCondition = Condition<TypeParam>( secondInvariant, secondInvConsts );

	resultInvariant = matrix_t<TypeParam>( 4, 4 );
	resultInvariant << 3, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 1, 0, 1, 0, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );

	// only shared variables
	haVar = { "a", "b" };
	lhsVar = { "a", "b" };
	rhsVar = { "a", "b" };

	// two empty conditions
	EXPECT_EQ( Condition<TypeParam>(),
			   combine( Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	EXPECT_EQ( firstCondition, combine( firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	resultInvariant = matrix_t<TypeParam>( 4, 2 );
	resultInvariant << 3, 1, 1, 2, 1, 1, 1, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );

	// shared and non shared variables
	haVar = { "a", "b", "c" };
	lhsVar = { "a", "b" };
	rhsVar = { "b", "c" };

	// two empty conditions
	EXPECT_EQ( Condition<TypeParam>(),
			   combine( Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// one empty condition
	resultInvariant = matrix_t<TypeParam>( 2, 3 );
	resultInvariant << 3, 1, 0, 1, 2, 0;
	resultInvConsts = vector_t<TypeParam>( 2 );
	resultInvConsts << 0, 1;
	resultCondition = Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar ) );

	// no empty condition
	resultInvariant = matrix_t<TypeParam>( 4, 3 );
	resultInvariant << 3, 1, 0, 1, 2, 0, 0, 1, 1, 0, 1, 2;
	resultInvConsts = vector_t<TypeParam>( 4 );
	resultInvConsts << 0, 1, 0, 1;
	resultCondition = Condition<TypeParam>( resultInvariant, resultInvConsts );
	EXPECT_EQ( resultCondition, combine( firstCondition, secondCondition, haVar, lhsVar, rhsVar ) );
}

/**
 * combine reset test
 */
TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest1 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	Reset<TypeParam> resultReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;
	matrix_t<TypeParam> resultMatrix;
	vector_t<TypeParam> resultConsts;

	// no shared variables
	haVar = { "a", "b", "c", "d" };
	lhsVar = { "a", "c" };
	rhsVar = { "b", "d" };

	// two empty resets
	// EXPECT_EQ(Reset<TypeParam>(), combine(Reset<TypeParam>(), Reset<TypeParam>(), haVar, lhsVar, rhsVar));

	// two non-empty resets
	firstMatrix = matrix_t<TypeParam>( 2, 2 );
	firstMatrix << 1, 2, 3, 4;
	firstConsts = vector_t<TypeParam>( 2 );
	firstConsts << 5, 6;
	secondMatrix = matrix_t<TypeParam>( 2, 2 );
	secondMatrix << 3, 1, 4, 2;
	secondConst = vector_t<TypeParam>( 2 );
	secondConst << 6, 7;
	resultMatrix = matrix_t<TypeParam>( 4, 4 );
	resultMatrix << 1, 0, 2, 0, 0, 3, 0, 1, 3, 0, 4, 0, 0, 4, 0, 2;
	resultConsts = vector_t<TypeParam>( 4 );
	resultConsts << 5, 6, 6, 7;
	EXPECT_EQ( Reset<TypeParam>( resultMatrix, resultConsts ),
			   combine( Reset<TypeParam>( firstMatrix, firstConsts ), Reset<TypeParam>( secondMatrix, secondConst ),
						haVar, lhsVar, rhsVar ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest2 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	Reset<TypeParam> resultReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;
	matrix_t<TypeParam> resultMatrix;
	vector_t<TypeParam> resultConsts;

	// shared and non-shared variables
	haVar = { "a", "b", "c" };
	lhsVar = { "a", "b" };
	rhsVar = { "b", "c" };

	// same reset for shared variable
	firstMatrix = matrix_t<TypeParam>( 2, 2 );
	firstMatrix << 1, 0, 0, 2;
	firstConsts = vector_t<TypeParam>( 2 );
	firstConsts << 3, 4;
	secondMatrix = matrix_t<TypeParam>( 2, 2 );
	secondMatrix << 2, 0, 0, 3;
	secondConst = vector_t<TypeParam>( 2 );
	secondConst << 4, 5;
	resultMatrix = matrix_t<TypeParam>( 3, 3 );
	resultMatrix << 1, 0, 0, 0, 2, 0, 0, 0, 3;
	resultConsts = vector_t<TypeParam>( 3 );
	resultConsts << 3, 4, 5;
	EXPECT_EQ( Reset<TypeParam>( resultMatrix, resultConsts ),
			   combine( Reset<TypeParam>( firstMatrix, firstConsts ), Reset<TypeParam>( secondMatrix, secondConst ),
						haVar, lhsVar, rhsVar ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest3 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;

	// invalid
	// shared and non-shared variables
	haVar = { "a", "b", "c" };
	lhsVar = { "a", "b" };
	rhsVar = { "b", "c" };

	// contradicting reset for shared variable
	firstMatrix = matrix_t<TypeParam>( 2, 2 );
	firstMatrix << 1, 0, 0, 3;
	firstConsts = vector_t<TypeParam>( 2 );
	firstConsts << 3, 4;
	secondMatrix = matrix_t<TypeParam>( 2, 2 );
	secondMatrix << 2, 0, 0, 3;
	secondConst = vector_t<TypeParam>( 2 );
	secondConst << 4, 5;
	ASSERT_NO_FATAL_FAILURE( combine( Reset<TypeParam>( firstMatrix, firstConsts ),
									  Reset<TypeParam>( secondMatrix, secondConst ), haVar, lhsVar, rhsVar ) );
}

TYPED_TEST( HybridAutomataParallelCompositionTest, combineRest4 ) {
	std::vector<std::string> haVar;
	std::vector<std::string> lhsVar;
	std::vector<std::string> rhsVar;
	Reset<TypeParam> firstReset;
	Reset<TypeParam> secondReset;
	matrix_t<TypeParam> firstMatrix;
	vector_t<TypeParam> firstConsts;
	matrix_t<TypeParam> secondMatrix;
	vector_t<TypeParam> secondConst;

	// contradicting reset for shared variable
	firstMatrix = matrix_t<TypeParam>( 1, 1 );
	firstMatrix << 1;
	firstConsts = vector_t<TypeParam>( 1 );
	firstConsts << 3;
	secondMatrix = matrix_t<TypeParam>( 1, 1 );
	secondMatrix << 1;
	secondConst = vector_t<TypeParam>( 1 );
	secondConst << 4;
	ASSERT_NO_FATAL_FAILURE( combine( Reset<TypeParam>( firstMatrix, firstConsts ),
									  Reset<TypeParam>( secondMatrix, secondConst ), haVar, lhsVar, rhsVar ) );
}