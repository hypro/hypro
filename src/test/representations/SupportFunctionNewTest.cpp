/**
 * Tests for new SupportFunctions
 *
 * @author Phillip Tse
 */

#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace hypro;

template <typename Number>
class SupportFunctionNewTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

////// Data Structure Tests

TYPED_TEST( SupportFunctionNewTest, LeafTest ) {
	using N = TypeParam;
	using C = Converter<TypeParam>;
	using S = typename SupportFunctionNew<TypeParam>::Settings;

	Box<TypeParam> box;
	SupportFunctionNew<TypeParam> sf( box );
	EXPECT_TRUE( sf.getRoot()->getType() == SFNEW_TYPE::LEAF );
	EXPECT_EQ( sf.getRoot()->getOriginCount(), unsigned( 0 ) );
	EXPECT_EQ( sf.getRoot()->getChildren().size(), std::size_t( 0 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( *( dynamic_cast<Leaf<N, C, S, Box<TypeParam>>*>( sf.getRoot().get() )->getRepresentation() ), box );

	// Test with HPoly that is a box
	HPolytope<TypeParam> hpoly( matrix_t<TypeParam>::Identity( 2, 2 ) );
	SupportFunctionNew<TypeParam> sfHpoly( hpoly );
	EXPECT_TRUE( sfHpoly.getRoot()->getType() == SFNEW_TYPE::LEAF );
	EXPECT_EQ( sfHpoly.getRoot()->getOriginCount(), unsigned( 0 ) );
	EXPECT_EQ( sfHpoly.getRoot()->getChildren().size(), std::size_t( 0 ) );
	EXPECT_EQ( sfHpoly.getRoot().use_count(), long( 1 ) );
	EXPECT_TRUE( std::get<0>( isBox( hpoly.matrix(), hpoly.vector() ) ) );
	EXPECT_EQ( ( dynamic_cast<Leaf<N, C, S, Box<TypeParam>>*>( sfHpoly.getRoot().get() )->getRepresentation() )->type(),
			   representation_name::box );

	// Test with Halfspace
	Halfspace<TypeParam> hspace( { TypeParam( 0 ), TypeParam( 1 ) }, TypeParam( 1 ) );
	SupportFunctionNew<TypeParam> sfHSpace( hspace );
	EXPECT_TRUE( sfHSpace.getRoot()->getType() == SFNEW_TYPE::LEAF );
	EXPECT_EQ( sfHSpace.getRoot()->getOriginCount(), unsigned( 0 ) );
	EXPECT_EQ( sfHSpace.getRoot()->getChildren().size(), std::size_t( 0 ) );
	EXPECT_EQ( sfHSpace.getRoot().use_count(), long( 1 ) );
	EXPECT_TRUE( std::get<0>( isBox( hspace.matrix(), hspace.vector() ) ) );
	EXPECT_TRUE( std::get<0>( isBox( sfHSpace.matrix(), sfHSpace.vector() ) ) );
	EXPECT_EQ( ( dynamic_cast<Leaf<N, C, S, Halfspace<TypeParam>>*>( sfHSpace.getRoot().get() )->getRepresentation() )
					 ->type(),
			   representation_name::constraint_set );

	// Test with Template polytope
	TemplatePolyhedron<TypeParam> tpoly( matrix_t<TypeParam>::Ones( 2, 2 ), vector_t<TypeParam>::Ones( 2 ) );
	SupportFunctionNew<TypeParam> sfTPoly( tpoly );
	EXPECT_TRUE( sfTPoly.getRoot()->getType() == SFNEW_TYPE::LEAF );
	EXPECT_EQ( sfTPoly.getRoot()->getOriginCount(), unsigned( 0 ) );
	EXPECT_EQ( sfTPoly.getRoot()->getChildren().size(), std::size_t( 0 ) );
	EXPECT_EQ( sfTPoly.getRoot().use_count(), long( 1 ) );
	EXPECT_FALSE( std::get<0>( isBox( tpoly.matrix(), tpoly.vector() ) ) );
	EXPECT_FALSE( std::get<0>( isBox( sfTPoly.matrix(), sfTPoly.vector() ) ) );
	// EXPECT_EQ( ( dynamic_cast<Leaf<N, C, S, TemplatePolyhedron<TypeParam>>*>( sfTPoly.getRoot().get()
	// )->getRepresentation() )
	//				 ->type(),
	//		   representation_name::polytope_t );
}

// Have a box as a leaf. Put a chain of trafoOps above the leaf.
// Check currentExponent, successiveTransformations and parameter values
TYPED_TEST( SupportFunctionNewTest, TrafoOp ) {
	using Setting = typename SupportFunctionNew<TypeParam>::Settings;

	// Make the box
	Point<TypeParam> p( { TypeParam( 0 ), TypeParam( 0 ) } );
	Point<TypeParam> q( { TypeParam( 1 ), TypeParam( 1 ) } );
	Box<TypeParam> box( std::make_pair( p, q ) );

	// The tree with only one leaf containing the box
	SupportFunctionNew<TypeParam> sf( box );
	EXPECT_TRUE( sf.getRoot()->getType() == SFNEW_TYPE::LEAF );
	EXPECT_TRUE( sf.getRoot()->getOriginCount() == unsigned( 0 ) );
	EXPECT_TRUE( sf.getRoot()->getChildren().size() == std::size_t( 0 ) );

	// tMat = 2 * Identity_Matrix , tVec = (1 0 0)
	int dim = 2;
	matrix_t<TypeParam> tMat = matrix_t<TypeParam>::Identity( dim, dim );
	vector_t<TypeParam> tVec = vector_t<TypeParam>::Zero( dim );
	tVec( 0 ) = 1;

	// Directions to evaluate, is the identity matrix
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( dim, dim );

	// Save pointer to parameters for later, checking if it remains the same object
	std::shared_ptr<const LinTrafoParameters<TypeParam, Setting>> trafo0Params = nullptr;

	// sf1
	SupportFunctionNew<TypeParam> sf1 = sf.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf1.getRoot() != nullptr );
	EXPECT_TRUE( sf1.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf1.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf1.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 0 ) );

	// Fill trafo0Params
	trafo0Params =
		  ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf1.getRoot().get() ) )->getParameters();

	// sf2
	SupportFunctionNew<TypeParam> sf2 = sf1.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf2.getRoot() != nullptr );
	EXPECT_TRUE( sf2.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf2.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf2.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 1 ) );

	// Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ( trafo0Params, ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf2.getRoot().get() )
									 ->getParameters() ) );

	// Evaluate
	std::vector<EvaluationResult<TypeParam>> res = sf2.multiEvaluate( directions, true );

	// Check if the supportvalues were right
	// Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 3 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );

	// sf3
	SupportFunctionNew<TypeParam> sf3 = sf2.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf3.getRoot() != nullptr );
	EXPECT_TRUE( sf3.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf3.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf3.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 2 ) );

	// sf4
	SupportFunctionNew<TypeParam> sf4 = sf3.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf4.getRoot() != nullptr );
	EXPECT_TRUE( sf4.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf4.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 4 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf4.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 0 ) );
	// Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ( trafo0Params, ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf4.getRoot().get() )
									 ->getParameters() ) );

	// Evaluate
	res = sf4.multiEvaluate( directions, true );

	// Check if the supportvalues were right
	// Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 5 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );

	// sf5
	SupportFunctionNew<TypeParam> sf5 = sf4.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf5.getRoot() != nullptr );
	EXPECT_TRUE( sf5.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf5.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf5.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 0 ) );

	// sf6
	SupportFunctionNew<TypeParam> sf6 = sf5.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf6.getRoot() != nullptr );
	EXPECT_TRUE( sf6.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf6.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf6.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 1 ) );

	// sf7
	SupportFunctionNew<TypeParam> sf7 = sf6.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf7.getRoot() != nullptr );
	EXPECT_TRUE( sf7.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf7.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf7.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 2 ) );

	// sf8
	SupportFunctionNew<TypeParam> sf8 = sf7.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf8.getRoot() != nullptr );
	EXPECT_TRUE( sf8.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf8.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 4 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf8.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 1 ) );

	// Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ( trafo0Params, ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf8.getRoot().get() )
									 ->getParameters() ) );

	// Evaluate
	res = sf8.multiEvaluate( directions, true );

	// Check if the supportvalues were right
	// Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 9 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );

	// sf9
	SupportFunctionNew<TypeParam> sf9 = sf8.affineTransformation( tMat, tVec );
	EXPECT_TRUE( sf9.getRoot() != nullptr );
	EXPECT_TRUE( sf9.getRoot()->getChildren().size() == std::size_t( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf9.getRoot().get() ) )
					 ->getCurrentExponent(),
			   unsigned( 1 ) );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf9.getRoot().get() ) )
					 ->getSuccessiveTransformations(),
			   std::size_t( 0 ) );

	// Check whether parameter object remained the same (whether both point to the same address)
	EXPECT_EQ( trafo0Params, ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( sf9.getRoot().get() )
									 ->getParameters() ) );

	// Evaluate
	res = sf9.multiEvaluate( directions, true );

	// Check if the supportvalues were right
	// Should be [1 + #trafos , 1] everywhere
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 10 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );

	/*
		int numOfTrafos = 9;
		for(int i = 0; i < numOfTrafos; i++){

			sf = sf.affineTransformation(tMat, tVec);

			EXPECT_TRUE(sf.getRoot() != nullptr);
			EXPECT_TRUE(sf.getRoot()->getChildren().size() == 1);
			EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getCurrentExponent(),
	   1);
			EXPECT_EQ((dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getSuccessiveTransformations(),
	   0); std::cout << "Constructed trafo " << i << std::endl;

			if(i == 0){
				//Save pointer to parameters for later, checking if it remains the same object
				trafo0Params =
	   (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get()))->getParameters();
				std::cout << "saved trafo0Params with address " << trafo0Params << std::endl;
			}

			if((i % 2 == 1) || (i == numOfTrafos)){

				//Check whether parameter object remained the same (whether both point to the same address)
				EXPECT_EQ(trafo0Params,
	   (dynamic_cast<TrafoOp<TypeParam,Converter<TypeParam>,SupportFunctionNewDefault>*>(sf.getRoot().get())->getParameters()));

				//Evaluate
				std::cout << "START EVALUATION FOR " << i << " TRAFOS\n";
				std::vector<EvaluationResult<TypeParam>> res = sf.multiEvaluate(directions,true);
				std::cout << "END EVALUATION\n";

				//Check if the supportvalues were right
				//Should be [1 + #trafos , 1] everywhere
				EXPECT_EQ(res.at(0).supportValue, TypeParam(1 + (i + 1)));
				EXPECT_EQ(res.at(1).supportValue, TypeParam(1));
			}
		}
	*/
}

TYPED_TEST( SupportFunctionNewTest, ScaleOp ) {
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> sf( box );
	SupportFunctionNew<TypeParam> sfScale = sf.scale( TypeParam( 10 ) );
	EXPECT_TRUE( sfScale.getRoot()->getType() == SFNEW_TYPE::SCALEOP );
	EXPECT_EQ( sfScale.getRoot()->getOriginCount(), unsigned( 1 ) );
	EXPECT_EQ( sfScale.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_EQ( sfScale.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ(
		  ( dynamic_cast<ScaleOp<TypeParam, Converter<TypeParam>, typename SupportFunctionNew<TypeParam>::Settings>*>(
				  sfScale.getRoot().get() )
				  ->getFactor() ),
		  TypeParam( 10 ) );

	// Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfScale.multiEvaluate( directions, true );
	EXPECT_TRUE( res.at( 0 ).supportValue == TypeParam( 10 ) );
	EXPECT_TRUE( res.at( 1 ).supportValue == TypeParam( 10 ) );

	// Evaluate with Halfspace SF
	Halfspace<TypeParam> hspace( { TypeParam( 0 ), TypeParam( 1 ) }, TypeParam( 0.5 ) );
	SupportFunctionNew<TypeParam> sf2( hspace );
	SupportFunctionNew<TypeParam> sfScale2 = sf2.scale( TypeParam( 100 ) );
	std::vector<EvaluationResult<TypeParam>> res2 = sfScale2.multiEvaluate( directions, true );
	EXPECT_EQ( res2.at( 0 ).errorCode, SOLUTION::INFTY );
	EXPECT_EQ( res2.at( 1 ).errorCode, SOLUTION::FEAS );
}

TYPED_TEST( SupportFunctionNewTest, ProjectOp ) {
	// 3d box
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> sf( box );

	// We want to throw out first and third dimension, keep second dimension
	std::vector<std::size_t> dims( { 1 } );
	SupportFunctionNew<TypeParam> sfProject = sf.projectOn( dims );
	EXPECT_TRUE( sfProject.getRoot()->getType() == SFNEW_TYPE::PROJECTOP );
	EXPECT_EQ( sfProject.getRoot()->getOriginCount(), unsigned( 1 ) );
	EXPECT_EQ( sfProject.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_EQ( sfProject.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ(
		  ( dynamic_cast<ProjectOp<TypeParam, Converter<TypeParam>, typename SupportFunctionNew<TypeParam>::Settings>*>(
				  sfProject.getRoot().get() )
				  ->getDimensions()
				  .at( 0 ) ),
		  std::size_t( 1 ) );

	// Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 3, 3 );
	std::vector<EvaluationResult<TypeParam>> res = sfProject.multiEvaluate( directions, true );
	EXPECT_TRUE( res.at( 0 ).supportValue == TypeParam( 0 ) );
	EXPECT_TRUE( res.at( 1 ).supportValue == TypeParam( 1 ) );
	EXPECT_TRUE( res.at( 2 ).supportValue == TypeParam( 0 ) );
}

TYPED_TEST( SupportFunctionNewTest, SumOp ) {
	// 2d box
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> sf( box );

	// Sum has only 2 children
	SupportFunctionNew<TypeParam> sfSum = sf.minkowskiSum( sf );
	EXPECT_TRUE( sfSum.getRoot()->getType() == SFNEW_TYPE::SUMOP );
	EXPECT_EQ( sfSum.getRoot()->getOriginCount(), unsigned( 2 ) );
	EXPECT_EQ( sfSum.getRoot()->getChildren().size(), std::size_t( 2 ) );
	EXPECT_EQ( sfSum.getRoot().use_count(), long( 1 ) );

	// Check with Evaluation value
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfSum.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 2 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 2 ) );

	// Sum2 will have 5 children, which are all sf
	std::vector<SupportFunctionNew<TypeParam>> sfVec( 4, sf );
	SupportFunctionNew<TypeParam> sfSum2 = sf.minkowskiSum( sfVec );
	EXPECT_TRUE( sfSum2.getRoot()->getType() == SFNEW_TYPE::SUMOP );
	EXPECT_EQ( sfSum2.getRoot()->getOriginCount(), unsigned( 2 ) );
	EXPECT_EQ( sfSum2.getRoot()->getChildren().size(), std::size_t( 5 ) );
	EXPECT_EQ( sfSum2.getRoot().use_count(), long( 1 ) );

	// Check with Evaluation value
	res = sfSum2.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 5 ) );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 5 ) );
}

TYPED_TEST( SupportFunctionNewTest, IntersectOp ) {
	// Two overlapping boxes, the overlapping box is (0,0) to (1,1)
	Box<TypeParam> upRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
											Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> uR( upRight );
	Box<TypeParam> downLeft( std::make_pair( Point<TypeParam>( { TypeParam( -1 ), TypeParam( -1 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> dL( downLeft );

	// Intersect with only two boxes
	SupportFunctionNew<TypeParam> sfIntersect = uR.intersect( dL );
	EXPECT_TRUE( sfIntersect.getRoot()->getType() == SFNEW_TYPE::INTERSECTOP );
	EXPECT_EQ( sfIntersect.getRoot()->getOriginCount(), unsigned( 2 ) );
	EXPECT_EQ( sfIntersect.getRoot()->getChildren().size(), std::size_t( 2 ) );
	EXPECT_EQ( sfIntersect.getRoot().use_count(), long( 1 ) );

	// Evaluate with directions (1,0) and (0,1) - This tests INFTY evaluation results
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfIntersect.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 1 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );

	// Evaluate with directions (1,1) and (-1,-1) - get the overlapping box diagonal length
	matrix_t<TypeParam> directions2( 2, 2 );
	directions2 << 1, 1, -1, -1;
	res = sfIntersect.multiEvaluate( directions2, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 2 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 0 ) );

	// Intersect first two with two other boxes, overlapping region should still be the box (0,0) to (1,1)
	Box<TypeParam> upLeft( std::make_pair( Point<TypeParam>( { TypeParam( -1 ), TypeParam( 0 ) } ),
										   Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> uL( upLeft );
	Box<TypeParam> downRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
											  Point<TypeParam>( { TypeParam( 2 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> dR( downRight );

	// Evaluate with the four boxes with directions (0,1) and (1,0)
	std::vector<SupportFunctionNew<TypeParam>> sfVec{ dL, uL, dR };
	SupportFunctionNew<TypeParam> sfIntersect2 = uR.intersect( sfVec );
	EXPECT_EQ( sfIntersect2.getRoot()->getChildren().size(), std::size_t( 4 ) );
	res = sfIntersect2.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 1 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 1 ) );
}

TYPED_TEST( SupportFunctionNewTest, UnionOp ) {
	// Two overlapping boxes, the overlapping box is (0,0) to (1,1)
	Box<TypeParam> upRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
											Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> uR( upRight );
	Box<TypeParam> downLeft( std::make_pair( Point<TypeParam>( { TypeParam( -1 ), TypeParam( -1 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> dL( downLeft );

	// Intersect with only two boxes
	SupportFunctionNew<TypeParam> sfUnion = uR.unite( dL );
	EXPECT_TRUE( sfUnion.getRoot()->getType() == SFNEW_TYPE::UNIONOP );
	EXPECT_EQ( sfUnion.getRoot()->getOriginCount(), unsigned( 2 ) );
	EXPECT_EQ( sfUnion.getRoot()->getChildren().size(), std::size_t( 2 ) );
	EXPECT_EQ( sfUnion.getRoot().use_count(), long( 1 ) );

	// Evaluate with directions (0,1) and (1,0) - This tests INFTY evaluation results
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfUnion.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 2 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 2 ) );

	// Evaluate with directions (1,1) and (-1,-1) - get the overlapping box
	matrix_t<TypeParam> directions2( 2, 2 );
	directions2 << 1, 1, -1, -1;
	res = sfUnion.multiEvaluate( directions2, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 4 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 2 ) );

	// Intersect first two with two other boxes, overlapping region should still be the box (0,0) to (1,1)
	Box<TypeParam> upLeft( std::make_pair( Point<TypeParam>( { TypeParam( -1 ), TypeParam( 0 ) } ),
										   Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> uL( upLeft );
	Box<TypeParam> downRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
											  Point<TypeParam>( { TypeParam( 2 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> dR( downRight );

	// Evaluate with the four boxes with directions (0,1) and (1,0)
	std::vector<SupportFunctionNew<TypeParam>> sfVec{ dL, uL, dR };
	SupportFunctionNew<TypeParam> sfUnion2 = uR.unite( sfVec );
	EXPECT_EQ( sfUnion2.getRoot()->getChildren().size(), std::size_t( 4 ) );
	res = sfUnion2.multiEvaluate( directions, true );
	EXPECT_EQ( res.at( 0 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 0 ).supportValue, TypeParam( 2 ) );
	EXPECT_EQ( res.at( 1 ).errorCode, hypro::SOLUTION::FEAS );
	EXPECT_EQ( res.at( 1 ).supportValue, TypeParam( 2 ) );
}

TYPED_TEST( SupportFunctionNewTest, IntersectHalfspaceOp ) {
	// Using only support functions that use the LeGuernic hspace intersection method
	using SF = SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewLeGuernic>;

	// THIS WORKS
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SF sf( box );
	Halfspace<TypeParam> hspace( { TypeParam( 1 ), TypeParam( 0 ) }, TypeParam( 1 ) );
	SF sfInterHalfspace = sf.intersectHalfspace( hspace );
	EXPECT_TRUE( sfInterHalfspace.getRoot()->getType() == SFNEW_TYPE::INTERSECTHSPACEOP );
	EXPECT_EQ( sfInterHalfspace.getRoot()->getOriginCount(), unsigned( 1 ) );
	EXPECT_EQ( sfInterHalfspace.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_EQ( sfInterHalfspace.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( ( dynamic_cast<IntersectHalfspaceOp<TypeParam, Converter<TypeParam>, SupportFunctionNewLeGuernic>*>(
					   sfInterHalfspace.getRoot().get() )
					   ->getHalfspace() ),
			   hspace );

	// Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfInterHalfspace.multiEvaluate( directions, true );
	EXPECT_GE( res.at( 0 ).supportValue, TypeParam( 1 ) );
	EXPECT_LT( res.at( 0 ).supportValue, TypeParam( 1.002 ) );
	EXPECT_GE( res.at( 1 ).supportValue, TypeParam( 2 ) );
	EXPECT_LT( res.at( 1 ).supportValue, TypeParam( 2.001 ) );

	// Emptiness
	EXPECT_TRUE( !sfInterHalfspace.empty() );
	Halfspace<TypeParam> hspace2( { TypeParam( 1 ), TypeParam( 1 ) }, TypeParam( -1 ) );
	SF sfEmpty = sfInterHalfspace.intersectHalfspace( hspace2 );
	EXPECT_TRUE( sfEmpty.empty() );

	// Supremum
	// std::cout << "TEST SUPREMUM" << std::endl;
	// EXPECT_TRUE(sfInterHalfspace.supremum() >= TypeParam(2));
	// EXPECT_TRUE(sfInterHalfspace.supremum() <= TypeParam(2.01));
	// Should actually be 2, it is 1 for now since it gives an optimal point, not the supreme one
	EXPECT_TRUE( sfInterHalfspace.supremum() >= TypeParam( 1 ) );
	EXPECT_TRUE( sfInterHalfspace.supremum() <= TypeParam( 1.01 ) );

	// Containment
	Point<TypeParam> completelyInside( { TypeParam( 0.5 ), TypeParam( 0.5 ) } );
	Point<TypeParam> inSFButNotInHSpace( { TypeParam( 1.5 ), TypeParam( 0.5 ) } );
	Point<TypeParam> completelyOutside( { TypeParam( 2.5 ), TypeParam( 0.5 ) } );
	EXPECT_TRUE( sfInterHalfspace.contains( completelyInside ) );
	EXPECT_FALSE( sfInterHalfspace.contains( inSFButNotInHSpace ) );
	EXPECT_FALSE( sfInterHalfspace.contains( completelyOutside ) );
}

TYPED_TEST( SupportFunctionNewTest, Constructors ) {
	// Empty constructor
	SupportFunctionNew<TypeParam> sfEmpty;
	EXPECT_TRUE( sfEmpty.empty() );
	EXPECT_TRUE( sfEmpty.getRoot() == nullptr );

	// First make a small sf
	Box<TypeParam> box1( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
										 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> sf( box1 );
	EXPECT_EQ( sf.getRoot().use_count(), long( 1 ) );

	// Then build a TrafoOp on top
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> sfTrafo = sf.affineTransformation( trafoMat, trafoVec );
	EXPECT_EQ( sfTrafo.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_TRUE( &( *( sfTrafo.getRoot()->getChildren().at( 0 ) ) ) == &( *( sf.getRoot() ) ) );
	EXPECT_EQ( sfTrafo.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 2 ) );

	// Copy constructor - copy sfTrafo. the copy should point to the same object sfTrafo points to
	SupportFunctionNew<TypeParam> sfCopy( sfTrafo );
	EXPECT_TRUE( &( *( sfCopy.getRoot() ) ) == &( *( sfTrafo.getRoot() ) ) );
	EXPECT_EQ( sfCopy.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_EQ( sfTrafo.getRoot()->getChildren().size(), std::size_t( 1 ) );
	EXPECT_TRUE( sfCopy.getRoot()->getChildren().at( 0 ) == sfTrafo.getRoot()->getChildren().at( 0 ) );
	EXPECT_EQ( sfTrafo.getRoot().use_count(), long( 2 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 2 ) );

	// Copy assign - set sfCopy to sf. Both sf and sfCopy will then point to the leaf object.
	sfCopy = sf;
	EXPECT_TRUE( &( *( sfCopy.getRoot() ) ) == &( *( sf.getRoot() ) ) );
	EXPECT_TRUE( sfCopy.getRoot()->getChildren().size() == std::size_t( 0 ) );
	EXPECT_EQ( sfTrafo.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 3 ) );

	// Move constructor -
	SupportFunctionNew<TypeParam> sfMove( std::move( sfCopy ) );
	EXPECT_TRUE( sfCopy.getRoot() == nullptr );
	EXPECT_TRUE( &( *( sfMove.getRoot() ) ) == &( *( sf.getRoot() ) ) );
	EXPECT_TRUE( sfMove.getRoot()->getChildren().size() == std::size_t( 0 ) );
	EXPECT_EQ( sfTrafo.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 3 ) );
	// std::cout << "Address of sf root ptr: " << sf.getRoot() << std::endl;
	// std::cout << "Address of sfTrafo root ptr: " << sfTrafo.getRoot() << std::endl;
	// std::cout << "Address of sfCopy root ptr: " << sfCopy.getRoot() << std::endl;
	// std::cout << "Address of sfMove root ptr: " << sfMove.getRoot() << std::endl;

	// Move assign
	sfMove = std::move( sfTrafo );
	EXPECT_TRUE( sfTrafo.getRoot() == nullptr );
	EXPECT_TRUE( sfMove.getRoot() != nullptr );
	EXPECT_TRUE( &( *( sfMove.getRoot()->getChildren().at( 0 ) ) ) == &( *( sf.getRoot() ) ) );
	EXPECT_EQ( sfMove.getRoot().use_count(), long( 1 ) );
	EXPECT_EQ( sf.getRoot().use_count(), long( 2 ) );

	// Matrix Vector constructor - implicit box
	using Setting = typename SupportFunctionNew<TypeParam>::Settings;
	matrix_t<TypeParam> mat = matrix_t<TypeParam>::Zero( 4, 2 );
	mat << 1, 0, -2, 0, 0, 1, 0, -2;
	vector_t<TypeParam> vec = vector_t<TypeParam>::Ones( 4 );
	SupportFunctionNew<TypeParam> sfMatVec( mat, vec );
	EXPECT_TRUE( sfMatVec.getRoot() != nullptr );
	EXPECT_EQ( sfMatVec.getRoot()->getType(), SFNEW_TYPE::LEAF );
	EXPECT_EQ(
		  ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, Box<TypeParam>>*>( sfMatVec.getRoot().get() )
				  ->getRepresentation()
				  ->type() ),
		  representation_name::box );
	EXPECT_EQ(
		  ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, Box<TypeParam>>*>( sfMatVec.getRoot().get() )
				  ->getRepresentation()
				  ->dimension() ),
		  std::size_t( 2 ) );

	// Matrix Vector constructor - hpoly
	using HPoly = HPolytopeT<TypeParam, hypro::Converter<TypeParam>, HPolytopeOptimizerCaching>;
	matrix_t<TypeParam> mat2 = matrix_t<TypeParam>::Zero( 3, 2 );
	mat2 << 2, -1, 1, 0, -2, 3;
	vector_t<TypeParam> vec2 = vector_t<TypeParam>::Ones( 3 );
	SupportFunctionNew<TypeParam> sfMatVec2( mat2, vec2 );
	EXPECT_TRUE( sfMatVec2.getRoot() != nullptr );
	EXPECT_EQ( sfMatVec2.getRoot()->getType(), SFNEW_TYPE::LEAF );
	EXPECT_EQ( ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, HPoly>*>( sfMatVec2.getRoot().get() )
					   ->getRepresentation()
					   ->type() ),
			   HPoly::type() );
	EXPECT_EQ( ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, HPoly>*>( sfMatVec2.getRoot().get() )
					   ->getRepresentation()
					   ->dimension() ),
			   std::size_t( 2 ) );
	// Settings constructor is below
}

TYPED_TEST( SupportFunctionNewTest, Deletion ) {
	// Non-owning pointers needed to check whether the sf's they are pointing to are actually deleted or not
	std::weak_ptr<SupportFunctionNew<TypeParam>> sf1Copy;
	std::weak_ptr<SupportFunctionNew<TypeParam>> sf2Copy;
	std::weak_ptr<SupportFunctionNew<TypeParam>> sfTrafoCopy;
	std::weak_ptr<SupportFunctionNew<TypeParam>> sfSumCopy;

	{
		// Construct leaf nodes
		Box<TypeParam> box1( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
		Box<TypeParam> box2( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
											 Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
		std::shared_ptr<SupportFunctionNew<TypeParam>> sf1 = std::make_shared<SupportFunctionNew<TypeParam>>( box1 );
		std::shared_ptr<SupportFunctionNew<TypeParam>> sf2 = std::make_shared<SupportFunctionNew<TypeParam>>( box2 );
		sf1Copy = sf1;
		sf2Copy = sf2;
		{
			// Build trafop
			matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Zero( 2, 2 );
			trafoMat( 0, 0 ) = TypeParam( 2 );
			trafoMat( 1, 1 ) = TypeParam( 2 );
			vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero( 2 );

			SupportFunctionNew<TypeParam> sfTrafo = sf1->affineTransformation( trafoMat, trafoVec );
			std::shared_ptr<SupportFunctionNew<TypeParam>> sfTrafoPtr =
				  std::make_shared<SupportFunctionNew<TypeParam>>( sfTrafo );
			sfTrafoCopy = sfTrafoPtr;

			EXPECT_TRUE( sfTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO );
			EXPECT_TRUE( sfTrafo.getRoot()->getChildren().size() == std::size_t( 1 ) );

			{
				// Build SumOp
				SupportFunctionNew<TypeParam> sum = sfTrafo.minkowskiSum( *sf2 );
				std::shared_ptr<SupportFunctionNew<TypeParam>> sumPtr =
					  std::make_shared<SupportFunctionNew<TypeParam>>( sum );
				sfSumCopy = sumPtr;
				EXPECT_TRUE( sum.getRoot()->getType() == SFNEW_TYPE::SUMOP );
				EXPECT_TRUE( sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size() );
			}
			// Since SumOp's scope ended, it will be deleted -> sfSumCopy's use_count == 0;
			EXPECT_TRUE( sfSumCopy.expired() );
			EXPECT_TRUE( !sfTrafoCopy.expired() );
			EXPECT_TRUE( !sf1Copy.expired() );
			EXPECT_TRUE( !sf2Copy.expired() );
		}
		EXPECT_TRUE( sfTrafoCopy.expired() );
		EXPECT_TRUE( !sf1Copy.expired() );
		EXPECT_TRUE( !sf2Copy.expired() );
	}
	EXPECT_TRUE( sf1Copy.expired() );
	EXPECT_TRUE( sf2Copy.expired() );
}

/*
 * Test deletion mechanics. Test cases:
 * 1. Delete supportfunction to leaf (tree stays the same, only sf to leaf vanishes)
 * 2. Delete supportfunction to intermediate node (tree stays the same, only sf to intermediate node vanishes)
 * 3. Delete supportfunction to root (root and its pointer to its children get deleted)
 *
 * NEEDS COPY ASSIGNMENT
 */

TYPED_TEST( SupportFunctionNewTest, IntermediateDeletion ) {
	// Construct leaf nodes
	Box<TypeParam> box1( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
										 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	Box<TypeParam> box2( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										 Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> sf1( box1 );
	SupportFunctionNew<TypeParam> sf2( box2 );

	// Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> sfWithTrafo = sf1.affineTransformation( trafoMat, trafoVec );

	EXPECT_TRUE( sfWithTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO );
	EXPECT_TRUE( sfWithTrafo.getRoot()->getChildren().size() == 1 );

	// Build SumOp
	SupportFunctionNew<TypeParam> sum = sfWithTrafo.minkowskiSum( sf2 );
	EXPECT_TRUE( sum.getRoot()->getType() == SFNEW_TYPE::SUMOP );
	EXPECT_TRUE( sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size() );

	// Vector where all supportFunctions are saved - sf's are saved in deletion order, last one deleted first
	std::vector<SupportFunctionNew<TypeParam>> sfVec;
	sfVec.emplace_back( std::move( sf1 ) );
	sfVec.emplace_back( std::move( sum ) );
	sfVec.emplace_back( std::move( sfWithTrafo ) );
	sfVec.emplace_back( std::move( sf2 ) );
	EXPECT_TRUE( sf1.getRoot() == nullptr );
	EXPECT_TRUE( sum.getRoot() == nullptr );
	EXPECT_TRUE( sfWithTrafo.getRoot() == nullptr );
	EXPECT_TRUE( sf2.getRoot() == nullptr );

	// Evaluate
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sfVec.at( 1 ).multiEvaluate( directions, true );

	// Now delete leaf2
	sfVec.pop_back();
	EXPECT_EQ( sfVec.size(), std::size_t( 3 ) );
	EXPECT_TRUE( sfVec.at( 1 ).getRoot()->getChildren().at( 1 ) != nullptr );
	std::vector<EvaluationResult<TypeParam>> res2 = sfVec.at( 1 ).multiEvaluate( directions, true );
	EXPECT_TRUE( res2.size() == res.size() );
	for ( std::size_t i = 0; i < res2.size(); i++ ) {
		EXPECT_TRUE( res2.at( i ) == res.at( i ) );
	}

	// Now delete a intermediate node
	sfVec.pop_back();
	EXPECT_EQ( sfVec.size(), std::size_t( 2 ) );
	EXPECT_TRUE( sfVec.at( 1 ).getRoot()->getChildren().at( 0 ) != nullptr );
	res2 = sfVec.at( 1 ).multiEvaluate( directions, true );
	EXPECT_TRUE( res2.size() == res.size() );
	for ( std::size_t i = 0; i < res2.size(); i++ ) {
		EXPECT_TRUE( res2.at( i ) == res.at( i ) );
	}

	// Now delete root - this should delete sum, trafo and leaf 2, leaving only leaf1, thus the evaluation result should
	// change
	sfVec.pop_back();
	EXPECT_EQ( sfVec.size(), std::size_t( 1 ) );
	res2 = sfVec.at( 0 ).multiEvaluate( directions, true );
	for ( std::size_t i = 0; i < res2.size(); i++ ) {
		EXPECT_FALSE( res2.at( i ) == res.at( i ) );
	}
}

////// Functionality Tests

TYPED_TEST( SupportFunctionNewTest, Evaluate ) {
	// Construct leaf nodes
	Box<TypeParam> box1( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
										 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	Box<TypeParam> box2( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										 Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );

	// Assemble them to a tree
	SupportFunctionNew<TypeParam> sf( box1 );
	SupportFunctionNew<TypeParam> sf2( box2 );

	// Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> sfWithTrafo = sf.affineTransformation( trafoMat, trafoVec );
	EXPECT_TRUE( sfWithTrafo.getRoot()->getType() == SFNEW_TYPE::TRAFO );
	EXPECT_TRUE( sfWithTrafo.getRoot()->getChildren().size() == std::size_t( 1 ) );

	// Build a sumOp
	SupportFunctionNew<TypeParam> sum = sfWithTrafo.minkowskiSum( sf2 );
	EXPECT_TRUE( sum.getRoot()->getType() == SFNEW_TYPE::SUMOP );
	EXPECT_TRUE( sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size() );

	// Evaluate sumOp
	matrix_t<TypeParam> directions = matrix_t<TypeParam>::Identity( 2, 2 );
	std::vector<EvaluationResult<TypeParam>> res = sum.multiEvaluate( directions, true );

	// Test Evaluation with only one direction
	vector_t<TypeParam> dir = vector_t<TypeParam>::Zero( 2 );
	dir( 0 ) = TypeParam( 1 );
	EvaluationResult<TypeParam> resOnlyOneDir = sum.evaluate( dir, true );
	EXPECT_TRUE( resOnlyOneDir.supportValue == res.at( 0 ).supportValue );

	// Test Evaluation of empty sf
	SupportFunctionNew<TypeParam> sfEmpty;
	res = sfEmpty.multiEvaluate( directions, true );
	EXPECT_TRUE( res == std::vector<EvaluationResult<TypeParam>>() );
	resOnlyOneDir = sfEmpty.evaluate( dir, true );
	EXPECT_TRUE( resOnlyOneDir == EvaluationResult<TypeParam>() );

	// Evaluation of an unfeasible set should always return SOLUTION::INFEAS, through all nodes
}

TYPED_TEST( SupportFunctionNewTest, EvaluateMixedLeaves ) {
	// Construct leaf nodes
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	matrix_t<TypeParam> mat = matrix_t<TypeParam>::Zero( 3, 2 );
	mat << 0, -1, 1, 1, -1, 1;
	vector_t<TypeParam> vec = vector_t<TypeParam>::Ones( 3 );
	HPolytope<TypeParam> hpoly( mat, vec );

	SupportFunctionNew<TypeParam> sfBox( box );
	SupportFunctionNew<TypeParam> sfHPoly( hpoly );
	SupportFunctionNew<TypeParam> inter = sfBox.intersect( sfHPoly );

	std::vector<EvaluationResult<TypeParam>> res = inter.multiEvaluate( mat, true );
	EXPECT_EQ( res.at( 0 ).supportValue, 0 );
	EXPECT_EQ( res.at( 1 ).supportValue, 1 );
	EXPECT_EQ( res.at( 2 ).supportValue, 1 );
}

TYPED_TEST( SupportFunctionNewTest, Emptiness ) {
	// Empty sf
	Box<TypeParam> box1 = Box<TypeParam>::Empty();
	SupportFunctionNew<TypeParam> sf1( box1 );
	EXPECT_TRUE( sf1.empty() );
	// HPolytope<TypeParam> hpoly1 = HPolytope<TypeParam>::Empty();
	HPolytope<TypeParam> hpoly1;
	hpoly1.insert( Halfspace<TypeParam>( { TypeParam( 1 ), TypeParam( 1 ) }, TypeParam( -1 ) ) );
	hpoly1.insert( Halfspace<TypeParam>( { TypeParam( -1 ), TypeParam( -1 ) }, TypeParam( -1 ) ) );
	sf1 = SupportFunctionNew<TypeParam>( hpoly1 );
	EXPECT_TRUE( sf1.empty() );

	// Leaf
	Box<TypeParam> box2( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										 Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> sf2( box2 );
	EXPECT_TRUE( !sf2.empty() );

	// Trafo
	matrix_t<TypeParam> mat = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> trafo = sf1.affineTransformation( mat, vec );
	EXPECT_TRUE( trafo.empty() );
	trafo = sf2.affineTransformation( mat, vec );
	EXPECT_TRUE( !trafo.empty() );
	mat = matrix_t<TypeParam>::Zero( 2, 2 );
	vec = vector_t<TypeParam>::Zero( 2 );
	trafo = sf2.affineTransformation( mat, vec );  // Test with Zero parameters
	EXPECT_TRUE( !trafo.empty() );

	// ProjectOp
	std::vector<std::size_t> dims( { 0 } );
	SupportFunctionNew<TypeParam> proj = sf1.projectOn( dims );
	EXPECT_TRUE( proj.empty() );
	proj = sf2.projectOn( dims );
	EXPECT_TRUE( !proj.empty() );
	std::vector<std::size_t> emptyDims;
	proj = sf2.projectOn( emptyDims );	// Test with empty dims
	EXPECT_TRUE( proj.empty() );

	// ScaleOp
	SupportFunctionNew<TypeParam> scale = sf1.scale( TypeParam( 5 ) );
	EXPECT_TRUE( scale.empty() );
	scale = sf2.scale( TypeParam( 5 ) );
	EXPECT_TRUE( !scale.empty() );
	scale = sf2.scale( TypeParam( 0 ) );  // Test with factor == 0
	EXPECT_TRUE( !scale.empty() );

	// Sum
	SupportFunctionNew<TypeParam> sum = trafo.minkowskiSum( sf2 );
	EXPECT_TRUE( !sum.empty() );
	sum = sf1.minkowskiSum( sf2 );
	EXPECT_TRUE( !sum.empty() );
	sum = proj.minkowskiSum( sf1 );	 // Test with 2 empty sfs
	EXPECT_TRUE( sum.empty() );
	sum = sf2.minkowskiSum( std::vector<SupportFunctionNew<TypeParam>>{ trafo, scale } );  // Test with no empty set
	EXPECT_TRUE( !sum.empty() );
	sum = sf2.minkowskiSum(
		  std::vector<SupportFunctionNew<TypeParam>>{ trafo, scale, proj, sf1 } );	// Test with empty set
	EXPECT_TRUE( !sum.empty() );

	// UnionOp
	SupportFunctionNew<TypeParam> uniteOp = sf2.unite( scale );
	EXPECT_TRUE( !uniteOp.empty() );
	uniteOp = sf2.unite( sf1 );
	EXPECT_TRUE( !uniteOp.empty() );
	uniteOp = proj.unite( sf1 );  // Test with 2 empty sfs
	EXPECT_TRUE( uniteOp.empty() );
	uniteOp = sf2.unite( std::vector<SupportFunctionNew<TypeParam>>{ trafo, scale } );	// Test with no empty set
	EXPECT_TRUE( !uniteOp.empty() );
	uniteOp =
		  sf2.unite( std::vector<SupportFunctionNew<TypeParam>>{ trafo, scale, proj, sf1 } );  // Test with empty set
	EXPECT_TRUE( !uniteOp.empty() );

	// IntersectOp
	SupportFunctionNew<TypeParam> intersectOp = sf2.intersect( scale );
	EXPECT_TRUE( !intersectOp.empty() );
	intersectOp = sf2.intersect( sf1 );
	EXPECT_TRUE( intersectOp.empty() );
	intersectOp = proj.intersect( sf1 );
	EXPECT_TRUE( intersectOp.empty() );
	// intersectOp = sf2.intersect(std::vector<SupportFunctionNew<TypeParam>>({trafo,scale})); //Test with no empty set
	// EXPECT_TRUE(!intersectOp.empty());
	// intersectOp = sf2.intersect(std::vector<SupportFunctionNew<TypeParam>>({trafo,scale,proj,sf1})); //Test with
	// empty set EXPECT_TRUE(intersectOp.empty());
}

TYPED_TEST( SupportFunctionNewTest, Dimension ) {
	// Two overlapping boxes as leaves, the overlapping box is (0,1) to (1,2)
	Box<TypeParam> upRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 1 ) } ),
											Point<TypeParam>( { TypeParam( 2 ), TypeParam( 3 ) } ) ) );
	SupportFunctionNew<TypeParam> uR( upRight );
	Box<TypeParam> downLeft( std::make_pair( Point<TypeParam>( { TypeParam( -2 ), TypeParam( 0 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> dL( downLeft );

	// Dimension of empty SF
	SupportFunctionNew<TypeParam> sf;
	TypeParam dim = sf.dimension();
	EXPECT_EQ( dim, std::size_t( 0 ) );

	// Dimension for Leaf
	dim = uR.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for TrafoOp
	matrix_t<TypeParam> mat = 2 * matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> trafo = uR.affineTransformation( mat, vec );
	dim = trafo.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for ProjectOp
	std::vector<std::size_t> dims( { 0 } );
	SupportFunctionNew<TypeParam> proj = uR.projectOn( dims );
	dim = proj.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for ScaleOp
	SupportFunctionNew<TypeParam> scale = uR.scale( TypeParam( 5 ) );
	dim = scale.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for SumOp
	SupportFunctionNew<TypeParam> sumOp = uR.minkowskiSum( dL );
	dim = sumOp.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for IntersectOp
	SupportFunctionNew<TypeParam> intersectOp = uR.intersect( dL );
	dim = intersectOp.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );

	// Dimension for UnionOp
	SupportFunctionNew<TypeParam> uniteOp = uR.unite( dL );
	dim = uniteOp.dimension();
	EXPECT_EQ( dim, std::size_t( 2 ) );
}

TYPED_TEST( SupportFunctionNewTest, Supremum ) {
	// Two overlapping boxes as leaves, the overlapping box is (0,1) to (1,2)
	Box<TypeParam> upRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 1 ) } ),
											Point<TypeParam>( { TypeParam( 2 ), TypeParam( 3 ) } ) ) );
	SupportFunctionNew<TypeParam> uR( upRight );
	Box<TypeParam> downLeft( std::make_pair( Point<TypeParam>( { TypeParam( -2 ), TypeParam( 0 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> dL( downLeft );

	// Supremum of empty SF
	SupportFunctionNew<TypeParam> sf;
	TypeParam sup = sf.supremum();
	EXPECT_EQ( sup, std::size_t( 0 ) );

	// Supremum for Leaf
	sup = uR.supremum();
	EXPECT_EQ( sup, TypeParam( 3 ) );

	// Supremum for TrafoOp
	matrix_t<TypeParam> mat = 2 * matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> trafo = uR.affineTransformation( mat, vec );
	sup = trafo.supremum();
	EXPECT_EQ( sup, TypeParam( 6 ) );

	// Supremum for ProjectOp
	std::vector<std::size_t> dims( { 0 } );
	SupportFunctionNew<TypeParam> proj = uR.projectOn( dims );
	sup = proj.supremum();
	EXPECT_EQ( sup, TypeParam( 2 ) );

	// Supremum for ScaleOp
	SupportFunctionNew<TypeParam> scale = uR.scale( TypeParam( 5 ) );
	sup = scale.supremum();
	EXPECT_EQ( sup, TypeParam( 15 ) );

	// Supremum for SumOp
	SupportFunctionNew<TypeParam> sumOp = uR.minkowskiSum( dL );
	sup = sumOp.supremum();
	EXPECT_EQ( sup, TypeParam( 5 ) );

	// Supremum for IntersectOp
	SupportFunctionNew<TypeParam> intersectOp = uR.intersect( dL );
	sup = intersectOp.supremum();
	EXPECT_EQ( sup, TypeParam( 2 ) );

	// Supremum for UnionOp
	SupportFunctionNew<TypeParam> uniteOp = uR.unite( dL );
	sup = uniteOp.supremum();
	EXPECT_EQ( sup, TypeParam( 3 ) );
}

TYPED_TEST( SupportFunctionNewTest, StorageSize ) {
	// Empty SF
	try {
		SupportFunctionNew<TypeParam> sf;
	} catch ( const std::runtime_error& e ) {
		FAIL();
	}

	// Size of a tree consisting of n-ary, unary and leaves
	// Construct leaf nodes
	Box<TypeParam> box1( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( -1 ) } ),
										 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	Box<TypeParam> box2( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										 Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> sf1( box1 );
	SupportFunctionNew<TypeParam> sf2( box2 );

	// Build trafop
	matrix_t<TypeParam> trafoMat = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> trafoVec = vector_t<TypeParam>::Zero( 2 );
	SupportFunctionNew<TypeParam> sfWithTrafo = sf1.affineTransformation( trafoMat, trafoVec );

	// Build SumOp
	SupportFunctionNew<TypeParam> sum = sfWithTrafo.minkowskiSum( sf2 );
	EXPECT_TRUE( sum.getRoot()->getType() == SFNEW_TYPE::SUMOP );
	EXPECT_TRUE( sum.getRoot()->getOriginCount() == sum.getRoot()->getChildren().size() );

	try {
		std::cout << "Size of sf1: " << sf1.size() << std::endl;
		std::cout << "Size of sf2: " << sf2.size() << std::endl;
		std::cout << "Size of sfWithTrafo: " << sfWithTrafo.size() << std::endl;
		std::cout << "Size of sum: " << sum.size() << std::endl;
	} catch ( const std::runtime_error& e ) {
		FAIL();
	}

	SUCCEED();
}

TYPED_TEST( SupportFunctionNewTest, Containment ) {
	// Two overlapping boxes as leaves, the overlapping box is (0,1) to (1,2)
	Box<TypeParam> upRight( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 1 ) } ),
											Point<TypeParam>( { TypeParam( 2 ), TypeParam( 3 ) } ) ) );
	SupportFunctionNew<TypeParam> uR( upRight );
	Box<TypeParam> downLeft( std::make_pair( Point<TypeParam>( { TypeParam( -2 ), TypeParam( 0 ) } ),
											 Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> dL( downLeft );

	// Points to test for containment
	Point<TypeParam> inUR{ TypeParam( 2 ), TypeParam( 2 ) };
	Point<TypeParam> inDL{ TypeParam( -1 ), TypeParam( 0 ) };
	Point<TypeParam> inBoth{ TypeParam( 0 ), TypeParam( 1 ) };

	// Contains of empty SF
	SupportFunctionNew<TypeParam> sf;
	bool resUR = sf.contains( inUR );
	bool resDL = sf.contains( inDL );
	bool resBoth = sf.contains( inBoth );
	EXPECT_FALSE( resUR );
	EXPECT_FALSE( resDL );
	EXPECT_FALSE( resBoth );

	// Contains for Leaf
	resUR = uR.contains( inUR );
	resDL = uR.contains( inDL );
	resBoth = uR.contains( inBoth );
	EXPECT_TRUE( resUR );
	EXPECT_FALSE( resDL );
	EXPECT_TRUE( resBoth );

	// Contains for TrafoOp
	matrix_t<TypeParam> mat = 2 * matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 2 );
	// trafo scales the boxes by 2, so uR = box made of [(0.2),(2,4)]
	SupportFunctionNew<TypeParam> trafo = uR.affineTransformation( mat, vec );
	// To not get confused with the spaces, we double the points to test also, and let them get halved within the
	// contains function
	inUR *= 2;
	inDL *= 2;
	inBoth *= 2;
	resUR = trafo.contains( inUR );
	resDL = trafo.contains( inDL );
	resBoth = trafo.contains( inBoth );
	EXPECT_TRUE( resUR );
	EXPECT_FALSE( resDL );
	EXPECT_TRUE( resBoth );
	inUR /= 2;
	inDL /= 2;
	inBoth /= 2;

	// Contains for ProjectOp
	// std::vector<std::size_t> dims({0});
	// SupportFunctionNew<TypeParam> proj = uR.projectOn(dims);
	// No testing since not correct

	// Contains for ScaleOp
	SupportFunctionNew<TypeParam> scale = uR.scale( TypeParam( 5 ) );
	// To not get confused with the spaces, we multiply the points to test also by 5, and let them get resized within
	// the contains function
	inUR *= 5;
	inDL *= 5;
	inBoth *= 5;
	resUR = scale.contains( inUR );
	resDL = scale.contains( inDL );
	resBoth = scale.contains( inBoth );
	EXPECT_TRUE( resUR );
	EXPECT_FALSE( resDL );
	EXPECT_TRUE( resBoth );
	inUR /= 5;
	inDL /= 5;
	inBoth /= 5;

	// Contains for SumOp
	SupportFunctionNew<TypeParam> sumOp = uR.minkowskiSum( dL );
	resUR = sumOp.contains( inUR );
	resDL = sumOp.contains( inDL );
	resBoth = sumOp.contains( inBoth );
	EXPECT_TRUE( resUR );
	EXPECT_TRUE( resDL );
	EXPECT_TRUE( resBoth );

	// Contains for IntersectOp
	SupportFunctionNew<TypeParam> intersectOp = uR.intersect( dL );
	resUR = intersectOp.contains( inUR );
	resDL = intersectOp.contains( inDL );
	resBoth = intersectOp.contains( inBoth );
	EXPECT_FALSE( resUR );
	EXPECT_FALSE( resDL );
	EXPECT_TRUE( resBoth );

	// Contains for UnionOp
	SupportFunctionNew<TypeParam> uniteOp = uR.unite( dL );
	resUR = uniteOp.contains( inUR );
	resDL = uniteOp.contains( inDL );
	resBoth = uniteOp.contains( inBoth );
	EXPECT_TRUE( resUR );
	EXPECT_TRUE( resDL );
	EXPECT_TRUE( resBoth );

	// Contains for SupportFunctions
	EXPECT_FALSE( uR.contains( dL ) );
	Box<TypeParam> overlapBox( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 1 ) } ),
											   Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> overlapSF( overlapBox );
	EXPECT_TRUE( uR.contains( overlapSF ) );
}

TYPED_TEST( SupportFunctionNewTest, IntersectAndSatisfiesHalfspace ) {
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0.1 ), TypeParam( 0.1 ) } ),
										Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SupportFunctionNew<TypeParam> sf1( box );

	// Halfspaces to test - belowBox does not contain the box, within box partially, aboveBox fully
	Halfspace<TypeParam> belowBox( { TypeParam( 0 ), TypeParam( 1 ) }, TypeParam( 0 ) );
	Halfspace<TypeParam> withinBox( { TypeParam( 0 ), TypeParam( 1 ) }, TypeParam( 1 ) );
	Halfspace<TypeParam> aboveBox( { TypeParam( 0 ), TypeParam( 1 ) }, TypeParam( 2 ) );

	// Test with undefined sf
	SupportFunctionNew<TypeParam> sfUndef;
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> emptySatisfy = sfUndef.satisfiesHalfspace( belowBox );
	EXPECT_EQ( emptySatisfy.first, hypro::CONTAINMENT::BOT );
	EXPECT_TRUE( emptySatisfy.second.empty() );
	EXPECT_EQ( emptySatisfy.second, sfUndef );

	// Test with unsatisfiable box
	HPolytope<TypeParam> hpoly;
	hpoly.insert( Halfspace<TypeParam>( { TypeParam( 1 ), TypeParam( 0 ) }, TypeParam( -1 ) ) );
	hpoly.insert( Halfspace<TypeParam>( { TypeParam( -1 ), TypeParam( 0 ) }, TypeParam( -1 ) ) );
	SupportFunctionNew<TypeParam> sfUnsat( hpoly );
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> unsatSatisfy = sfUnsat.satisfiesHalfspace( belowBox );
	EXPECT_EQ( unsatSatisfy.first, hypro::CONTAINMENT::NO );
	EXPECT_EQ( unsatSatisfy.second, sfUnsat );

	// Test with belowBox
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> belowSatisfy = sf1.satisfiesHalfspace( belowBox );
	EXPECT_TRUE( belowSatisfy.first == hypro::CONTAINMENT::NO );
	EXPECT_TRUE( belowSatisfy.second.empty() );

	// Test with withinBox
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> withinSatisfy = sf1.satisfiesHalfspace( withinBox );
	EXPECT_TRUE( withinSatisfy.first == hypro::CONTAINMENT::PARTIAL );
	EXPECT_TRUE( !withinSatisfy.second.empty() );
	Box<TypeParam> boxWithin( std::make_pair( Point<TypeParam>( { TypeParam( 0.1 ), TypeParam( 0.1 ) } ),
											  Point<TypeParam>( { TypeParam( 2 ), TypeParam( 1 ) } ) ) );
	SupportFunctionNew<TypeParam> sfWithin( boxWithin );
	EXPECT_TRUE( withinSatisfy.second.contains( sfWithin ) );
	// EXPECT_TRUE(sfWithin.contains(withinSatisfy.second)); //DOES NOT WORK, SINCE WE OVERAPPROXIMATE

	// Test with aboveBox
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> aboveSatisfy = sf1.satisfiesHalfspace( aboveBox );
	EXPECT_TRUE( aboveSatisfy.first == hypro::CONTAINMENT::FULL );
	EXPECT_TRUE( !aboveSatisfy.second.empty() );
	EXPECT_TRUE( aboveSatisfy.second == sf1 );

	// Now test intersectHalfspaces and satisfyHalfspaces: Setup is a triangle that is shifted from right to left along
	// the x-axis At first, the offset vector is such that the triangle and box do not overlap, so no intersection Then
	// the triangle overlaps half the box, so partial intersection Then the triangle contains the whole box, so full
	// intersection
	matrix_t<TypeParam> triangleMat = matrix_t<TypeParam>( 3, 2 );
	triangleMat( 0, 0 ) = TypeParam( -1 );
	triangleMat( 0, 1 ) = TypeParam( 1 );
	triangleMat( 1, 0 ) = TypeParam( 1 );
	triangleMat( 1, 1 ) = TypeParam( 1 );
	triangleMat( 2, 0 ) = TypeParam( 0 );
	triangleMat( 2, 1 ) = TypeParam( -1 );
	vector_t<TypeParam> triangleVec1 = vector_t<TypeParam>( 3 );
	vector_t<TypeParam> triangleVec2 = vector_t<TypeParam>( 3 );
	vector_t<TypeParam> triangleVec3 = vector_t<TypeParam>( 3 );
	triangleVec1 << TypeParam( -3 ), TypeParam( 9 ), TypeParam( 0 );
	triangleVec2 << TypeParam( 0 ), TypeParam( 6 ), TypeParam( 0 );
	triangleVec3 << TypeParam( 2 ), TypeParam( 4 ), TypeParam( 0 );

	// Unsat box and triangle do not overlap
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> justNo =
		  sfUnsat.satisfiesHalfspaces( triangleMat, triangleVec1 );
	EXPECT_EQ( justNo.first, hypro::CONTAINMENT::NO );
	EXPECT_TRUE( justNo.second.empty() );

	// Box and triangle do not overlap
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> noOverlap =
		  sf1.satisfiesHalfspaces( triangleMat, triangleVec1 );
	EXPECT_TRUE( noOverlap.first == hypro::CONTAINMENT::NO );
	EXPECT_TRUE( noOverlap.second.empty() );

	// Box and triangle overlap partially
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> partialOverlap =
		  sf1.satisfiesHalfspaces( triangleMat, triangleVec2 );
	EXPECT_EQ( partialOverlap.first, hypro::CONTAINMENT::PARTIAL );
	EXPECT_TRUE( !partialOverlap.second.empty() );

	// Triangle contains box fully
	std::pair<CONTAINMENT, SupportFunctionNew<TypeParam>> fullOverlap =
		  sf1.satisfiesHalfspaces( triangleMat, triangleVec3 );
	EXPECT_EQ( fullOverlap.first, hypro::CONTAINMENT::FULL );
	EXPECT_TRUE( !fullOverlap.second.empty() );
	EXPECT_TRUE( fullOverlap.second == sf1 );
}

/* CollectProjections Test Setup:
 *
 *	   	  intersect
 *	  /		 |			\
 *	 |		 |	 		sum
 *	 |		 |		/			\
 *	 |		 |		|		  union
 *	 |		 |		|		 /		\
 *	Proj4  Proj3  Proj2   Proj1	 	 |
 *   |		 |		 |		 |		 |
 *	sf 	 	sf		sf  	sf  	sf
 */

TYPED_TEST( SupportFunctionNewTest, CollectProjections ) {
	// Make a 5-dim box
	Point<TypeParam> p1{ TypeParam( 0 ), TypeParam( 1 ), TypeParam( 2 ), TypeParam( 3 ), TypeParam( 4 ) };
	Point<TypeParam> p2{ TypeParam( -2 ), TypeParam( -1 ), TypeParam( 0 ), TypeParam( 1 ), TypeParam( 2 ) };
	Box<TypeParam> box( std::vector<Point<TypeParam>>( { p1, p2 } ) );
	SupportFunctionNew<TypeParam> sf( box );

	// Proj1 - projects away dimension 5
	std::vector<std::size_t> proj1Dims( { 0, 1, 2, 3 } );
	SupportFunctionNew<TypeParam> proj1 = sf.projectOn( proj1Dims );
	// the 5th dimension is only projected away in other functions like collectProjections; the original dimension is
	// still callable via dimension()
	EXPECT_EQ( proj1.dimension(), std::size_t( 5 ) );
	EXPECT_EQ( proj1.collectProjections(), proj1Dims );

	// Union - should leave out dimension 5 as it is not in both proj1 and sf
	SupportFunctionNew<TypeParam> unio = proj1.unite( sf );
	EXPECT_EQ( unio.collectProjections(), proj1Dims );

	// Proj2 - projects away dimension 2 and 3
	std::vector<std::size_t> proj2Dims( { 0, 3, 4 } );
	SupportFunctionNew<TypeParam> proj2 = sf.projectOn( proj2Dims );
	EXPECT_EQ(
		  proj2.dimension(),
		  std::size_t( 5 ) );  // the 5th dimension is only projected away in other functions like collectProjections
	EXPECT_EQ( proj2.collectProjections(), proj2Dims );

	// Sum - Should return intersection of proj1Dims and proj2Dims
	SupportFunctionNew<TypeParam> sum = proj2.minkowskiSum( unio );
	EXPECT_EQ( sum.collectProjections(), std::vector<std::size_t>( { 0, 3 } ) );

	// Proj3 - projects away dimension 1
	std::vector<std::size_t> proj3Dims( { 1, 2, 3, 4 } );
	SupportFunctionNew<TypeParam> proj3 = sf.projectOn( proj3Dims );
	EXPECT_EQ( proj3Dims, proj3.collectProjections() );

	// Proj4 - projects away dimension 4
	std::vector<std::size_t> proj4Dims( { 0, 1, 2, 4 } );
	SupportFunctionNew<TypeParam> proj4 = sf.projectOn( proj4Dims );
	EXPECT_EQ( proj4Dims, proj4.collectProjections() );

	// Intersect - no dimension should be left
	std::vector<SupportFunctionNew<TypeParam>> children( { proj3, sum } );
	SupportFunctionNew<TypeParam> inter = proj4.intersect( children );
	EXPECT_EQ( inter.collectProjections(), std::vector<std::size_t>() );
}

TYPED_TEST( SupportFunctionNewTest, Vertices ) {
	// 3d box
	Point<TypeParam> p1 = Point<TypeParam>( { TypeParam( 0 ), TypeParam( -4 ), TypeParam( -22 ) } );
	Point<TypeParam> p2 = Point<TypeParam>( { TypeParam( 3 ), TypeParam( 6.789 ), TypeParam( -3.1415 ) } );
	Box<TypeParam> box( std::make_pair( p1, p2 ) );
	SupportFunctionNew<TypeParam> sf( box );
	std::vector<Point<TypeParam>> points = sf.vertices();
	// Results commented out because the values are actually right, but suffer from numerical instabilities
	// auto it = points.begin();
	// EXPECT_TRUE(*(std::find(points.begin(), points.end(), *it)) == p1);
	// EXPECT_TRUE(*(std::find(points.begin(), points.end(), *it)) == p2);
	SUCCEED();
}

TYPED_TEST( SupportFunctionNewTest, SettingsConversion ) {
	Point<TypeParam> p1 = Point<TypeParam>( { TypeParam( 0 ), TypeParam( -4 ), TypeParam( -22 ) } );
	Point<TypeParam> p2 = Point<TypeParam>( { TypeParam( 3 ), TypeParam( 6.789 ), TypeParam( -3.1415 ) } );
	Box<TypeParam> box( std::make_pair( p1, p2 ) );
	SupportFunctionNew<TypeParam> sf( box );

	// Leaf
	using Setting = typename SupportFunctionNew<TypeParam>::Settings;
	SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> sf2( sf );
	EXPECT_EQ( *( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, Box<TypeParam>>*>( sf.getRoot().get() )
						->getRepresentation() ),
			   *( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction, Box<TypeParam>>*>(
						sf2.getRoot().get() )
						->getRepresentation() ) );
	EXPECT_EQ( ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, Setting, Box<TypeParam>>*>( sf.getRoot().get() )
					   ->isRedundant() ),
			   ( dynamic_cast<Leaf<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction, Box<TypeParam>>*>(
					   sf2.getRoot().get() )
					   ->isRedundant() ) );
	EXPECT_EQ( sf2.dimension(), sf.dimension() );

	// TrafoOp
	matrix_t<TypeParam> mat = 2 * matrix_t<TypeParam>::Identity( 3, 3 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 3 );
	SupportFunctionNew<TypeParam> trafo = sf.affineTransformation( mat, vec );

	SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> trafo2( trafo );
	TrafoOp<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction>* trafo2Node =
		  dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction>*>(
				trafo2.getRoot().get() );
	EXPECT_EQ( ( dynamic_cast<TrafoOp<TypeParam, Converter<TypeParam>, Setting>*>( trafo.getRoot().get() )
					   ->getParameters()
					   ->power ),
			   unsigned( 2 ) );
	EXPECT_TRUE( ( trafo2Node != nullptr ) );
	EXPECT_TRUE( ( trafo2Node->getParameters() != nullptr ) );
	EXPECT_EQ( ( trafo2Node->getParameters()->power ), unsigned( 1 ) );
	EXPECT_EQ( trafo2.dimension(), sf.dimension() );

	try {
		// ProjectOp
		std::vector<std::size_t> dims( { 0 } );
		SupportFunctionNew<TypeParam> proj = sf.projectOn( dims );
		SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> proj2( proj );
		EXPECT_EQ( ( dynamic_cast<ProjectOp<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction>*>(
						   proj2.getRoot().get() )
						   ->getDimensions()
						   .size() ),
				   std::size_t( 1 ) );

		// ScaleOp
		SupportFunctionNew<TypeParam> scale = sf.scale( TypeParam( 5 ) );
		SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> scale2( scale );
		EXPECT_EQ( ( dynamic_cast<ScaleOp<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction>*>(
						   scale2.getRoot().get() )
						   ->getFactor() ),
				   TypeParam( 5 ) );

		// SumOp
		SupportFunctionNew<TypeParam> sumOp = sf.minkowskiSum( scale );
		SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> sum2( sumOp );
		EXPECT_EQ( sum2.getRoot()->getChildren().size(), std::size_t( 2 ) );
		EXPECT_EQ( sum2.dimension(), sf.dimension() );

		// IntersectOp
		SupportFunctionNew<TypeParam> intersectOp = sf.intersect( scale );
		SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> inter2( intersectOp );
		EXPECT_EQ( inter2.getRoot()->getChildren().size(), std::size_t( 2 ) );
		EXPECT_EQ( inter2.dimension(), sf.dimension() );

		// UnionOp
		std::vector<SupportFunctionNew<TypeParam>> vec = { proj, scale, sumOp };
		SupportFunctionNew<TypeParam> uniteOp = sf.unite( vec );
		SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewNoReduction> unite2( uniteOp );
		EXPECT_EQ( unite2.getRoot()->getChildren().size(), std::size_t( 4 ) );
		EXPECT_EQ( unite2.dimension(), sf.dimension() );

	} catch ( std::runtime_error& e ) {
		FAIL();
	}
}

TYPED_TEST( SupportFunctionNewTest, MatrixVector ) {
	// Empty SF
	SupportFunctionNew<TypeParam> sfEmpty;
	EXPECT_EQ( sfEmpty.matrix(), matrix_t<TypeParam>::Zero( 0, 0 ) );
	EXPECT_EQ( sfEmpty.vector(), vector_t<TypeParam>::Zero( 0 ) );

	// Make a box
	Point<TypeParam> p1{ TypeParam( -1 ), TypeParam( -1 ) };
	Point<TypeParam> p2{ TypeParam( 1 ), TypeParam( 1 ) };
	Box<TypeParam> box( std::make_pair( p1, p2 ) );
	SupportFunctionNew<TypeParam> sf( box );
	matrix_t<TypeParam> expectedResMat = matrix_t<TypeParam>::Zero( 8, 2 );
	vector_t<TypeParam> expectedResVec = vector_t<TypeParam>::Zero( 8 );
	expectedResMat << 1, 0, -1, 0, 0, 1, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1;
	expectedResVec << 1, 1, 1, 1, 2, 2, 2, 2;
	EXPECT_EQ( sf.matrix(), expectedResMat );
	EXPECT_EQ( sf.vector(), expectedResVec );

	// Halfspace
	// Halfspace<TypeParam> hspace ({TypeParam(0),TypeParam(1)}, TypeParam(0));
	// SupportFunctionNew<TypeParam> sfHspace(hspace);
}

TYPED_TEST( SupportFunctionNewTest, Reduction ) {
	// TODO: Reactivate Test when emptiness caching implemented
	// Empty SF
	// SupportFunctionNew<TypeParam> sfEmpty;
	// sfEmpty.reduceRepresentation();
	// EXPECT_TRUE(sfEmpty.getRoot() == nullptr);
	// EXPECT_TRUE(sfEmpty.isTemplateSet());

	// Halfspace

	// Some SF
	Point<TypeParam> p1{ TypeParam( -1 ), TypeParam( -1 ) };
	Point<TypeParam> p2{ TypeParam( 1 ), TypeParam( 1 ) };
	Box<TypeParam> box( std::make_pair( p1, p2 ) );
	SupportFunctionNew<TypeParam> sf( box );
	sf.reduceRepresentation();
	EXPECT_TRUE( sf.isTemplateSet() );
}

//////////////////////// INTEGRATION TESTS //////////////////////////

TYPED_TEST( SupportFunctionNewTest, TrafoOpOverIntersectHalfspaceOp ) {
	// Using only support functions that use the LeGuernic hspace intersection method
	using SF = SupportFunctionNewT<TypeParam, Converter<TypeParam>, SupportFunctionNewLeGuernic>;

	// Create sf: First {(0,0),(2,2)} then {(0,0),(1,2)} via intersectHalfspace then {(1,1),(3,5)} via
	// affineTransformation
	Box<TypeParam> box( std::make_pair( Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } ),
										Point<TypeParam>( { TypeParam( 2 ), TypeParam( 2 ) } ) ) );
	SF sf( box );
	Halfspace<TypeParam> hspace( { TypeParam( 1 ), TypeParam( 0 ) }, TypeParam( 1 ) );
	SF sfInterHalfspace = sf.intersectHalfspace( hspace );
	matrix_t<TypeParam> mat = 2 * matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Ones( 2 );
	SF sfTrans = sfInterHalfspace.affineTransformation( mat, vec );
	EXPECT_TRUE( !sfTrans.empty() );

	// Test evaluation over that
	vector_t<TypeParam> controlOptimumValue = vector_t<TypeParam>::Zero( 2 );
	// controlOptimumValue(0) = 5;
	auto res = sfTrans.evaluate( vec, false );
	EXPECT_LE( TypeParam( 8 ), res.supportValue );
	EXPECT_LE( res.supportValue, TypeParam( 8.002 ) );
	EXPECT_EQ( res.optimumValue, controlOptimumValue );
	EXPECT_EQ( res.errorCode, SOLUTION::FEAS );
}

/*
 * A temporary test that counts the evaluation calls if le guernic hspace intersection is used on multiple
 * NOTE: This test can only be used if the HYPRO_STATISTICS option has been enabled
 */
/*
#ifdef HYPRO_STATISTICS
TYPED_TEST(SupportFunctionNewTest, EvaluationCount){

	//Using only support functions that use the LeGuernic hspace intersection method
	using SF = SupportFunctionNewT<TypeParam,Converter<TypeParam>,SupportFunctionNewLeGuernic>;

	Point<TypeParam> p1 {TypeParam(0), TypeParam(0)};
	Point<TypeParam> p2 {TypeParam(2), TypeParam(2)};
	Box<TypeParam> box(std::make_pair(p1,p2));
	SF sf(box);
	RESET_STATS();
	vector_t<TypeParam> dir = vector_t<TypeParam>::Ones(2);

	//One intersection - one direction
	std::cout << "===== EVALUATION COUNT: One intersection X - one direction:" << std::endl;
	Halfspace<TypeParam> hspaceX({TypeParam(1),TypeParam(0)},TypeParam(1.5));
	SF sfOneHspaceX = sf.intersectHalfspace(hspaceX);
	auto res = sfOneHspaceX.evaluate(dir,true);
	PRINT_STATS();
	RESET_STATS();

	std::cout << "===== EVALUATION COUNT: One intersection Y - one direction:" << std::endl;
	Halfspace<TypeParam> hspaceY({TypeParam(0),TypeParam(1)},TypeParam(1.5));
	SF sfOneHspaceY = sf.intersectHalfspace(hspaceY);
	res = sfOneHspaceY.evaluate(dir,true);
	PRINT_STATS();
	RESET_STATS();

	std::cout << "===== EVALUATION COUNT: One intersection X and Y - one direction:" << std::endl;
	Halfspace<TypeParam> hspaceXY({TypeParam(1),TypeParam(1)},TypeParam(1));
	SF sfOneHspaceXY = sf.intersectHalfspace(hspaceXY);
	res = sfOneHspaceXY.evaluate(dir,true);
	PRINT_STATS();
	RESET_STATS();

	//Two intersections - one direction
	std::cout << "===== EVALUATION COUNT: Two intersections X then Y - one direction:" << std::endl;
	SF sfTwoHspace = sfOneHspaceX.intersectHalfspace(hspaceY);
	res = sfTwoHspace.evaluate(dir,true);
	PRINT_STATS();
	RESET_STATS();

	//Three intersections - one direction
	std::cout << "===== EVALUATION COUNT: Three intersections X then Y then X and Y - one direction:" << std::endl;
	SF sfThreeHspace = sfTwoHspace.intersectHalfspace(hspaceXY);
	res = sfThreeHspace.evaluate(dir,true);
	PRINT_STATS();
	RESET_STATS();
}
#endif
*/
