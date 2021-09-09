#include "../../hypro/datastructures/reachability/Strategy.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"

namespace {

using namespace hypro;

TEST( StrategyTest, Constructor ) {
	using namespace hypro;
	Strategy<State_t<double>> strat;

	strat.emplace_back( StrategyNode<Box<double>>{ mpq_class( 1 ) } );

	EXPECT_EQ( strat.size(), std::size_t( 1 ) );

	Strategy<State_t<double>> strat2;
	strat2 = { StrategyNode<Box<double>>( mpq_class( 1 ) ), StrategyNode<SupportFunction<double>>( mpq_class( 1 ) ),
			   StrategyNode<Zonotope<double>>( mpq_class( 1 ) ) };

	EXPECT_EQ( strat2.size(), std::size_t( 3 ) );
}

TEST( StrategyTest, Conversion ) {
	using namespace hypro;

	Strategy<State_t<double>> strat;

	strat.emplace_back( StrategyNode<Box<double>>{ mpq_class( 1 ) } );
	strat.emplace_back( StrategyNode<SupportFunction<double>>{ mpq_class( 1 ) } );

	Box<double> b;
	b.insert( carl::Interval<double>( 1, 2 ) );

	State_t<double> s;
	s.setSet( b );

	auto tmp = strat[1];

	std::visit( detail::strategyConversionVisitor<State_t<double>>( s ), strat[1] );

	EXPECT_NO_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<Box<double>>( s.getSet() ) );

	EXPECT_EQ( std::get<SupportFunction<double>>( s.getSet() ).type(), representation_name::support_function );
	EXPECT_EQ( s.getSetType(), representation_name::support_function );

	// using conversion function

	strat.advanceToLevel( s, 0 );
	EXPECT_ANY_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_NO_THROW( std::get<Box<double>>( s.getSet() ) );
	EXPECT_EQ( s.getSetType(), representation_name::box );

	strat.advanceToLevel( s, 1 );
	EXPECT_NO_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<Box<double>>( s.getSet() ) );
	EXPECT_EQ( s.getSetType(), representation_name::support_function );
}
}  // namespace
