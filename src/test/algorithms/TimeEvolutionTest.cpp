#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/handlers/timeEvolutionHandlers/singularTimeEvolutionHandler.h>
#include <hypro/representations/GeometricObjectBase.h>

TEST( TimeEvolutionTest, SingularEvolution ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;
	using Vector = hypro::vector_t<Number>;
	using Point = hypro::Point<Number>;

	Vector origin = Vector::Zero( 2 );

	VPoly init{ std::vector{ origin } };

	Vector dynamics1 = Vector::Zero( 2 );
	dynamics1 << Number( 1 ), Number( 1 );
	std::vector<Point> dynamicsVertices{ Point( dynamics1 ) };

	auto unbndTimeEvolution = hypro::singularApplyTimeEvolution( init, dynamicsVertices );

	EXPECT_TRUE( unbndTimeEvolution.vertices().size() == 1 );
	EXPECT_TRUE( unbndTimeEvolution.rays().size() == 1 );
	EXPECT_EQ( origin, unbndTimeEvolution.vertices().front().rawCoordinates() );

	Vector v1 = Vector::Zero( 2 );
	v1 << Number( 0 ), Number( 1 );

	VPoly init2{ { origin, v1 } };

	auto bndTimeEvolution = hypro::singularApplyBoundedTimeEvolution( init2, dynamicsVertices, hypro::tNumber( 10 ) );
	EXPECT_TRUE( bndTimeEvolution.vertices().size() == 4 );
	EXPECT_TRUE( bndTimeEvolution.rays().size() == 0 );

	SUCCEED();
}