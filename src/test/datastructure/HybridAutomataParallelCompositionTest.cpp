/**
 * Testfile for parallel composition of hybrid automata.
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/Transition.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/State.h"
#include "representations/GeometricObject.h"
#include "carl/core/VariablePool.h"
#include "datastructures/HybridAutomaton/Condition.h"


using namespace hypro;
using namespace carl;

template <typename Number>
using valuation_t = VPolytope<Number>;

template<typename Number>
class HybridAutomataParallelCompositionTest : public ::testing::Test
{
/**
 * Test Setup:
 * Something
 */
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

/**
 * combine condition test, also overs combine for matrix_t
 */
TYPED_TEST(HybridAutomataParallelCompositionTest, combineCondition)
{
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
	haVar = {"a","b","c","d"};
	lhsVar = {"a", "c"};
	rhsVar = {"b","d"};

	// two empty conditions
	EXPECT_EQ(Condition<TypeParam>(), combine(Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// one empty condition
	firstInvariant = matrix_t<TypeParam>(2,2);
	firstInvariant << 3, 1,
	                  1, 2;
	firstInvConsts = vector_t<TypeParam>(2);
	firstInvConsts << 0,
	                  1;
	firstCondition = Condition<TypeParam>(firstInvariant, firstInvConsts);

	resultInvariant = matrix_t<TypeParam>(2, 4);
	resultInvariant << 3, 0, 1, 0,
	                   1, 0, 2, 0;
	resultInvConsts = vector_t<TypeParam>(2);
	resultInvConsts << 0,
	                   1;
	resultCondition = Condition<TypeParam>(resultInvariant, resultInvConsts);
	EXPECT_EQ(resultCondition, combine(firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// no empty condition
	secondInvariant = matrix_t<TypeParam>(2,2);
	secondInvariant << 1, 1,
	                   1, 2;
	secondInvConsts = vector_t<TypeParam>(2);
	secondInvConsts << 0,
	                   1;
	secondCondition = Condition<TypeParam>(secondInvariant, secondInvConsts);

	resultInvariant = matrix_t<TypeParam>(4, 4);
	resultInvariant << 3, 0, 1, 0,
	                   1, 0, 2, 0,
	                   0, 1, 0, 1,
	                   0, 1, 0, 2;
	resultInvConsts = vector_t<TypeParam>(4);
	resultInvConsts << 0,
	                   1,
	                   0,
	                   1;
	resultCondition = Condition<TypeParam>(resultInvariant, resultInvConsts);
	EXPECT_EQ(resultCondition, combine(firstCondition, secondCondition, haVar, lhsVar, rhsVar)); 






	// only shared variables
	haVar = {"a","b"};
	lhsVar = {"a","b"};
	rhsVar = {"a","b"};

	// two empty conditions
	EXPECT_EQ(Condition<TypeParam>(), combine(Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// one empty condition
	EXPECT_EQ(firstCondition, combine(firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// no empty condition
	resultInvariant = matrix_t<TypeParam>(4, 2);
	resultInvariant << 3, 1,
	                   1, 2,
	                   1, 1,
	                   1, 2;
	resultInvConsts = vector_t<TypeParam>(4);
	resultInvConsts << 0,
	                   1,
	                   0,
	                   1;
	resultCondition = Condition<TypeParam>(resultInvariant, resultInvConsts);
	EXPECT_EQ(resultCondition, combine(firstCondition, secondCondition, haVar, lhsVar, rhsVar)); 






	// shared and non shared variables
	haVar = {"a","b","c"};
	lhsVar = {"a","b"};
	rhsVar = {"b","c"};

	// two empty conditions
	EXPECT_EQ(Condition<TypeParam>(), combine(Condition<TypeParam>(), Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// one empty condition
	resultInvariant = matrix_t<TypeParam>(2, 3);
	resultInvariant << 3, 1, 0,
	                   1, 2, 0;
	resultInvConsts = vector_t<TypeParam>(2);
	resultInvConsts << 0,
	                   1;
	resultCondition = Condition<TypeParam>(resultInvariant, resultInvConsts);
	EXPECT_EQ(resultCondition, combine(firstCondition, Condition<TypeParam>(), haVar, lhsVar, rhsVar)); 

	// no empty condition
	resultInvariant = matrix_t<TypeParam>(4, 3);
	resultInvariant << 3, 1, 0,
	                   1, 2, 0,
	                   0, 1, 1,
	                   0, 1, 2;
	resultInvConsts = vector_t<TypeParam>(4);
	resultInvConsts << 0,
	                   1,
	                   0,
	                   1;
	resultCondition = Condition<TypeParam>(resultInvariant, resultInvConsts);
	EXPECT_EQ(resultCondition, combine(firstCondition, secondCondition, haVar, lhsVar, rhsVar)); 

}

