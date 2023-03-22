/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <cassert>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomatonComp.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>

using Number = double;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using Automaton = hypro::HybridAutomatonComp<Number>;
using Location = typename Automaton::LocationType;
using Box = hypro::Box<Number>;
using Condition = hypro::Condition<Number>;

TEST( ParallelCompositionAnalysisTest, Instanciation ) {
	hypro::FixedAnalysisParameters fixedParameters;
	hypro::AnalysisParameters analysisParameters;
	auto cmp = Automaton();

	auto roots = hypro::makeRoots<Box, Automaton>( cmp );

	auto reacher = hypro::reachability::Reach<Box, Automaton>( cmp, fixedParameters, analysisParameters, roots );
	SUCCEED();
}

TEST( ParallelCompositionAnalysisTest, SingleAutomaton ) {
	hypro::FixedAnalysisParameters fixedParameters;
	hypro::AnalysisParameters analysisParameters;
	auto cmp = Automaton();

	auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>( hypro::getTestModelsPath() + "parser/bouncing_ball.model" );
	auto settings = hypro::convert( parsedSettings );
	cmp.addAutomaton( std::move( automaton ) );

	auto roots = hypro::makeRoots<Box, Automaton>( cmp );

	auto reacher = hypro::reachability::Reach<Box, Automaton>( cmp, settings.fixedParameters(), settings.strategy().front(), roots );
	auto result = reacher.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );
}

TEST( ParallelCompositionAnalysisTest, SafetyAutomaton ) {
	hypro::FixedAnalysisParameters fixedParameters;
	hypro::AnalysisParameters analysisParameters;
	auto cmp = Automaton();

	auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>( hypro::getTestModelsPath() + "parser/bouncing_ball.model" );
	auto settings = hypro::convert( parsedSettings );
	cmp.addAutomaton( std::move( automaton ) );

	// create safety automaton
	{
		auto safety = hypro::HybridAutomaton<Number>();
		auto* loc = safety.createLocation( "isSafe?" );
		loc->setFlow( Matrix::Zero( 0, 0 ) );
		// global badStates: x <= 1
		Matrix safetyConstraint = Matrix::Zero( 1, 2 );
		safetyConstraint( 0, 0 ) = 1;
		Vector safetyConstant = Vector::Ones( 1 );
		safety.addGlobalBadStates( { safetyConstraint, safetyConstant } );
		safety.addInitialState( loc, Condition::True() );
		// add to composition
		cmp.addAutomaton( std::move( safety ) );
	}

	auto roots = hypro::makeRoots<Box, Automaton>( cmp );
	/*
auto reacher = hypro::reachability::Reach<Box, Automaton>( cmp, settings.fixedParameters(), settings.strategy().front(), roots );
auto result = reacher.computeForwardReachability();
EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );
// try local bad states
cmp.removeAutomaton( 1 );
{
	auto safety = hypro::HybridAutomaton<Number>();
	auto* loc = safety.createLocation( "isSafe?" );
	loc->setFlow( Matrix::Zero( 0, 0 ) );
	// global badStates: x <= 1
	Matrix safetyConstraint = Matrix::Zero( 1, 2 );
	safetyConstraint( 0, 0 ) = 1;
	Vector safetyConstant = Vector::Ones( 1 );
	safety.addLocalBadStates( loc, { safetyConstraint, safetyConstant } );
	safety.addInitialState( loc, Condition::True() );
	// add to composition
	cmp.addAutomaton( std::move( safety ) );
}
roots.clear();
roots = hypro::makeRoots<Box, Automaton>( cmp );

	auto reacher = hypro::reachability::Reach<Box, Automaton>( cmp, settings.fixedParameters(), settings.strategy().front(), roots );
	auto result = reacher.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );
	// try local bad states
	cmp.removeAutomaton( 1 );
	{
		auto safety = hypro::HybridAutomaton<Number>();
		auto* loc = safety.createLocation( "isSafe?" );
		loc->setFlow( Matrix::Zero( 0, 0 ) );
		// global badStates: x <= 1
		Matrix safetyConstraint = Matrix::Zero( 1, 2 );
		safetyConstraint( 0, 0 ) = 1;
		Vector safetyConstant = Vector::Ones( 1 );
		safety.addLocalBadStates( loc, { safetyConstraint, safetyConstant } );
		safety.addInitialState( loc, Condition::True() );
		// add to composition
		cmp.addAutomaton( std::move( safety ) );
	}
	roots.clear();
	roots = hypro::makeRoots<Box, Automaton>( cmp );

	auto reacher2 = hypro::reachability::Reach<Box, Automaton>( cmp, settings.fixedParameters(), settings.strategy().front(), roots );
	result = reacher2.computeForwardReachability();
	EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );
}
