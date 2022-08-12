#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <thread>

using namespace hypro;

void run( State_t<double> st ) {
	matrix_t<double> dir = matrix_t<double>::Zero( 1, 2 );
	vector_t<double> consts = vector_t<double>::Zero( 1 );
	dir << 1, 0;
	consts << 1;

	st.satisfiesHalfspaces( dir, consts );

	SupportFunction<double> tmp = std::get<SupportFunction<double>>( st.getSet() );
	tmp.cleanUp();
	st.setSet( tmp );
}

TEST( StateTest, Constructor ) {
	// Todo
}

TEST( StateTest, CleanUp ) {
	matrix_t<double> constraints;
	matrix_t<double> constants;
	constraints = matrix_t<double>::Zero( 3, 2 );

	constraints( 0, 0 ) = double( 2 );
	constraints( 0, 1 ) = double( 4 );
	constraints( 1, 0 ) = double( 1 );
	constraints( 1, 1 ) = double( -2 );
	constraints( 2, 0 ) = double( -4 );
	constraints( 2, 1 ) = double( 1 );

	constants = matrix_t<double>( 3, 1 );
	constants( 0, 0 ) = double( 20 );
	constants( 1, 0 ) = double( 5 );
	constants( 2, 0 ) = double( 17 );

	State_t<double> st;
	SupportFunction<double> psf1 = SupportFunction<double>( constraints, constants );

	st.setSet( psf1 );

	std::thread* t = new std::thread( run, st );

	t->join();

	delete t;
}

TEST( StateTest, Conversion ) {
	using namespace hypro;
	hypro::Box<double> b;
	b.insert( carl::Interval<double>( 1, 2 ) );

	State_t<double> s;
	s.setSet( b );

	s.setSetDirect( std::visit(
		  genericConversionVisitor<typename State_t<double>::repVariant, SupportFunction<double>>(), s.getSet() ) );
	s.setSetType( representation_name::support_function );

	EXPECT_NO_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<hypro::Box<double>>( s.getSet() ) );

	s.setSet( std::visit( genericConversionVisitor<typename State_t<double>::repVariant, HPolytope<double>>(),
						  s.getSet() ) );

	EXPECT_NO_THROW( std::get<hypro::HPolytope<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<hypro::Box<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_EQ( representation_name::polytope_h, s.type() );

	s.setAndConvertType<SupportFunction<double>>();
	EXPECT_ANY_THROW( std::get<hypro::HPolytope<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<hypro::Box<double>>( s.getSet() ) );
	EXPECT_NO_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_EQ( representation_name::support_function, s.type() );

	s.setAndConvertType<State_t<double>::nth_representation<0>>();
	EXPECT_ANY_THROW( std::get<hypro::HPolytope<double>>( s.getSet() ) );
	EXPECT_NO_THROW( std::get<hypro::Box<double>>( s.getSet() ) );
	EXPECT_ANY_THROW( std::get<SupportFunction<double>>( s.getSet() ) );
	EXPECT_EQ( representation_name::box, s.type() );
}

TEST( StateTest, letTimePassZeroFlow ) {
	using N = mpq_class;
	using State = State<N, Box<N>>;

	std::vector<carl::Interval<N>> intervals;
	intervals.emplace_back( carl::Interval<N>{ 1, 2 } );
	intervals.emplace_back( carl::Interval<N>{ 0, 1 } );
	Box<N> b{ intervals };

	State s0{ b };

	matrix_t<N> dynamics = matrix_t<N>::Zero( 2, 2 );

	State s1 = s0.partiallyComputeAndApplyLinearTimeStep( dynamics, tNumber( 1 ) );

	EXPECT_EQ( std::get<Box<N>>( s1.getSet() ), b );
}

TEST( StateTest, letTimePassLinearFlow ) {
	using N = mpq_class;
	using State = State<N, Box<N>>;

	std::vector<carl::Interval<N>> intervals;
	intervals.emplace_back( carl::Interval<N>{ 1, 2 } );
	intervals.emplace_back( carl::Interval<N>{ 0, 1 } );
	Box<N> b{ intervals };

	State s0{ b };

	matrix_t<N> dynamics = matrix_t<N>::Zero( 2, 2 );
	dynamics << 1, 0, 0, 1;

	State s1 = s0.partiallyComputeAndApplyLinearTimeStep( dynamics, tNumber( 1 ) );

	std::cout << s1 << std::endl;

	auto resultIntervals = std::get<Box<N>>( s1.getSet() ).intervals();

	EXPECT_EQ( resultIntervals.at( 0 ).lower(), N( 6121026514868073 ) / N( 2251799813685248 ) );
	EXPECT_EQ( resultIntervals.at( 0 ).upper(), N( 6121026514868073 ) / N( 1125899906842624 ) );
	EXPECT_EQ( resultIntervals.at( 1 ).lower(), N( 0 ) );
	EXPECT_EQ( resultIntervals.at( 1 ).upper(), N( 6121026514868073 ) / N( 2251799813685248 ) );
}
