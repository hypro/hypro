#include "../../hypro/representations/GeometricObjectBase.h"
#include "../defines.h"
#include "gtest/gtest.h"

using namespace hypro;

template <typename Number>
class DifferenceBoundsTest : public ::testing::Test {
  protected:
	matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry> mat;
	matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry> mat2;
	virtual void SetUp() {
		mat = matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry>( 3,
																												  3 );
		mat << typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
			  Number( 0 ),
			  DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( -4 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( -4 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 9 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 11 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 2 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ );

		mat2 = matrix_t<typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry>( 3,
																												   3 );
		mat2 << typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
			  Number( 0 ),
			  DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( -4 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( -4 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 9 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 10 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 1 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ ),
			  typename DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::DBMEntry(
					Number( 0 ),
					DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::SMALLER_EQ );
	}

	virtual void TearDown() {}
};

TYPED_TEST( DifferenceBoundsTest, DBMEntryComparison ) {
	typename DifferenceBounds<TypeParam>::DBMEntry infty( TypeParam( 0 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY );

	typename DifferenceBounds<TypeParam>::DBMEntry smaller1( TypeParam( 1 ),
															 DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER );
	typename DifferenceBounds<TypeParam>::DBMEntry smaller2( TypeParam( 2 ),
															 DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER );

	typename DifferenceBounds<TypeParam>::DBMEntry smallerEq1( TypeParam( 1 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );
	typename DifferenceBounds<TypeParam>::DBMEntry smallerEq2( TypeParam( 2 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	EXPECT_FALSE( infty < infty );
	EXPECT_TRUE( smaller1 < infty );
	EXPECT_FALSE( infty < smaller1 );
	EXPECT_TRUE( smallerEq1 < infty );
	EXPECT_FALSE( infty < smallerEq1 );

	EXPECT_TRUE( smaller1 < smaller2 );
	EXPECT_FALSE( smaller2 < smaller1 );

	EXPECT_TRUE( smaller1 < smallerEq1 );
	EXPECT_FALSE( smallerEq1 < smaller1 );
	EXPECT_TRUE( smaller1 < smallerEq2 );
	EXPECT_FALSE( smallerEq2 < smaller1 );

	EXPECT_FALSE( smallerEq2 < smallerEq1 );
	EXPECT_TRUE( smallerEq1 < smallerEq2 );
	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, DBMEntryPlus ) {
	typename DifferenceBounds<TypeParam>::DBMEntry infty( TypeParam( 0 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY );

	typename DifferenceBounds<TypeParam>::DBMEntry smaller1( TypeParam( 1 ),
															 DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER );
	typename DifferenceBounds<TypeParam>::DBMEntry smaller2( TypeParam( 2 ),
															 DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER );

	typename DifferenceBounds<TypeParam>::DBMEntry smallerEq1( TypeParam( 1 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );
	typename DifferenceBounds<TypeParam>::DBMEntry smallerEq2( TypeParam( 2 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	EXPECT_EQ( ( infty + infty ), typename DifferenceBounds<TypeParam>::DBMEntry(
										TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( ( smaller1 + infty ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( ( infty + smaller1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( ( smallerEq1 + infty ), typename DifferenceBounds<TypeParam>::DBMEntry(
											 TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( ( infty + smallerEq1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
											 TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );

	EXPECT_EQ( ( smaller1 + smaller2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
											  TypeParam( 3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( ( smaller2 + smaller1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
											  TypeParam( 3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );

	EXPECT_EQ( ( smaller1 + smallerEq1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
												TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( ( smallerEq1 + smaller1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
												TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( ( smaller1 + smallerEq2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
												TypeParam( 3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( ( smallerEq2 + smaller1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
												TypeParam( 3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );

	EXPECT_EQ( ( smallerEq2 + smallerEq1 ),
			   typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( ( smallerEq1 + smallerEq2 ),
			   typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Vertices ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	//( 4[0] , 4[1]), ( 4[0] , 6[1]), ( 9[0] , 9[1]), ( 9[0] , 11[1])/
	std::vector<Point<TypeParam>> vertices = dbm.vertices();
	ASSERT_EQ( vertices.size(), std::size_t( 4 ) );

	std::vector<TypeParam> coord0;
	coord0.push_back( TypeParam( 4 ) );
	coord0.push_back( TypeParam( 4 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<TypeParam>( coord0 ) ) != vertices.end() );

	std::vector<TypeParam> coord1;
	coord1.push_back( TypeParam( 4 ) );
	coord1.push_back( TypeParam( 6 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<TypeParam>( coord1 ) ) != vertices.end() );

	std::vector<TypeParam> coord2;
	coord2.push_back( TypeParam( 9 ) );
	coord2.push_back( TypeParam( 9 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<TypeParam>( coord2 ) ) != vertices.end() );

	std::vector<TypeParam> coord3;
	coord3.push_back( TypeParam( 9 ) );
	coord3.push_back( TypeParam( 11 ) );
	EXPECT_TRUE( std::find( vertices.begin(), vertices.end(), Point<TypeParam>( coord3 ) ) != vertices.end() );
}

TYPED_TEST( DifferenceBoundsTest, Elapse ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.elapse();
	//( 0, <= )( -4, <= )( -4, <= )
	//( 0, inf )( 0, <= )( 0, <= )
	//( 0, inf )( 2, <= )( 0, <= )
	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Rewind ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.rewind();
	//( 0, <= )( 0, <= )( 0, <= )
	//( 9, <= )( 0, <= )( 0, <= )
	//( 11, <= )( 2, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Free ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.free( 2 );  // free y
	// ( 0, <= )( -4, <= )( 0, <= )
	// ( 9, <= )( 0, <= )( 9, <= )
	// ( 0, inf )( 0, inf )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Reset ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.reset( 1, TypeParam( 0 ) );  // reset x to 0
	//( 0, <= )( 0, <= )( -4, <= )
	//( 0, <= )( 0, <= )( -4, <= )
	//( 11, <= )( 11, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Copy ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.copy( 1, 2 );	 // copy x to y
	//( 0, <= )( -4, <= )( -4, <= )
	//( 9, <= )( 0, <= )( 0, <= )
	//( 9, <= )( 0, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Shift ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res = dbm.shift( 1, 5.0 );	// shift x 5 to the right
	//( 0, <= )( -9, <= )( -4, <= )
	//( 14, <= )( 0, <= )( 5, <= )
	//( 11, <= )( -3, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 14 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 5 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Empty ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	// std::cout << "DBM: " << std::endl << dbm << std::endl;

	EXPECT_FALSE( dbm.empty() );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Contains ) {
	DifferenceBounds<TypeParam> dbm1 = DifferenceBounds<TypeParam>();
	dbm1.setDBM( this->mat );
	dbm1.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> dbm2 = DifferenceBounds<TypeParam>();
	dbm2.setDBM( this->mat2 );
	dbm2.setTimeHorizon( TypeParam( 20 ) );

	EXPECT_TRUE( dbm1.contains( dbm2 ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, IntersectConstraint ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> res =
		  dbm.intersectConstraint( 1, 0,
								   typename DifferenceBounds<TypeParam>::DBMEntry(
										 TypeParam( 8 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	//( 0, <= )( -4, <= )( -4, <= )
	//( 8, <= )( 0, <= )( 0, <= )
	//( 10, <= )( 2, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 8 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 10 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ContainsPoint ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	vector_t<TypeParam> coordinates( 2 );
	coordinates << TypeParam( 5 ), TypeParam( 5 );
	Point<TypeParam> point = Point<TypeParam>( coordinates );

	EXPECT_TRUE( dbm.contains( point ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, IntersectDBM ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> dbm2 = DifferenceBounds<TypeParam>();
	dbm2.setDBM( this->mat );
	dbm2.setTimeHorizon( TypeParam( 20 ) );
	dbm2 = dbm2.shift( 1, TypeParam( 1 ) );
	dbm2 = dbm2.shift( 2, TypeParam( -1 ) );

	DifferenceBounds<TypeParam> res = dbm.intersect( dbm2 );
	//( 0, <= )( -5, <= )( -5, <= )
	//( 9, <= )( 0, <= )( 0, <= )
	//( 9, <= )( 0, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -5 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -5 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 9 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, Unite ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	DifferenceBounds<TypeParam> dbm2 = DifferenceBounds<TypeParam>();
	dbm2.setDBM( this->mat );
	dbm2.setTimeHorizon( TypeParam( 20 ) );
	dbm2 = dbm2.shift( 1, TypeParam( 1 ) );
	dbm2 = dbm2.shift( 2, TypeParam( -1 ) );

	DifferenceBounds<TypeParam> res = dbm.unite( dbm2 );
	//( 0, <= )( -4, <= )( -3, <= )
	//( 10, <= )( 0, <= )( 2, <= )
	//( 11, <= )( 2, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 10 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ConversionHPolyToDBM ) {
	std::vector<Point<TypeParam>> vec;
	std::vector<TypeParam> coord1;
	coord1.push_back( TypeParam( 1 ) );
	coord1.push_back( TypeParam( 4 ) );

	std::vector<TypeParam> coord2;
	coord2.push_back( TypeParam( 5 ) );
	coord2.push_back( TypeParam( 4 ) );

	std::vector<TypeParam> coord3;
	coord3.push_back( TypeParam( 3 ) );
	coord3.push_back( TypeParam( 5 ) );

	std::vector<TypeParam> coord4;
	coord4.push_back( TypeParam( 3 ) );
	coord4.push_back( TypeParam( 3 ) );

	vec.push_back( Point<TypeParam>( coord1 ) );
	vec.push_back( Point<TypeParam>( coord2 ) );
	vec.push_back( Point<TypeParam>( coord3 ) );
	vec.push_back( Point<TypeParam>( coord4 ) );

	HPolytope<TypeParam> testHPolytope = HPolytope<TypeParam>( vec );

	DifferenceBounds<TypeParam> res = Converter<TypeParam>::toDifferenceBounds( testHPolytope );
	//( 0, <= )( -1, <= )( -3, <= )
	//( 5, <= )( 0, <= )( 1, <= )
	//( 5, <= )( 3, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -1 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 5 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 1 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 5 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ExtraM ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> MBounds( 3 );	//+1 for 0 clock
	/*
	 * MBounds(x_0)=0
	 * MBounds(x_1)=3
	 * MBounds(x_2)=13
	 */
	MBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 13 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	DifferenceBounds<TypeParam> res = dbm.extraM( MBounds );
	//( 0, <= )( -3, < )( -4, <= )
	//( 0, inf )( 0, <= )( 0, <= )
	//( 11, <= )( 2, <= )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 2 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ExtraMPlus ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> MBounds( 3 );	//+1 for 0 clock
	/*
	 * MBounds(x_0)=0
	 * MBounds(x_1)=3
	 * MBounds(x_2)=13
	 */
	MBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 13 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	DifferenceBounds<TypeParam> res = dbm.extraMPlus( MBounds );
	//( 0, <= )( -3, < )( -4, <= )
	//( 0, inf )( 0, <= )( 0, inf )
	//( 11, <= )( 0, inf )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 11 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ExtraLU ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> LBounds( 3 );	//+1 for 0 clock
	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> UBounds( 3 );	//+1 for 0 clock

	LBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 1 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	UBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 13 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	DifferenceBounds<TypeParam> res = dbm.extraLU( LBounds, UBounds );
	//( 0, <= )( -3, < )( -4, <= )
	//( 0, inf )( 0, <= )( 0, <= )
	//( 0, inf )( 0, inf )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}

TYPED_TEST( DifferenceBoundsTest, ExtraLUPlus ) {
	DifferenceBounds<TypeParam> dbm = DifferenceBounds<TypeParam>();
	dbm.setDBM( this->mat );
	dbm.setTimeHorizon( TypeParam( 20 ) );

	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> LBounds( 3 );	//+1 for 0 clock
	vector_t<typename DifferenceBounds<TypeParam>::DBMEntry> UBounds( 3 );	//+1 for 0 clock

	LBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 1 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	UBounds << typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 0 ),
															   DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 3 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ),
		  typename DifferenceBounds<TypeParam>::DBMEntry( TypeParam( 13 ),
														  DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ );

	DifferenceBounds<TypeParam> res = dbm.extraLUPlus( LBounds, UBounds );
	//( 0, <= )( -3, < )( -4, <= )
	//( 0, inf )( 0, <= )( 0, inf )
	//( 0, inf )( 0, inf )( 0, <= )

	EXPECT_EQ( res.getDBM()( 0, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 0, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -3 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER ) );
	EXPECT_EQ( res.getDBM()( 0, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( -4 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	EXPECT_EQ( res.getDBM()( 1, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 1, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );
	EXPECT_EQ( res.getDBM()( 1, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );

	EXPECT_EQ( res.getDBM()( 2, 0 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 1 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::INFTY ) );
	EXPECT_EQ( res.getDBM()( 2, 2 ), typename DifferenceBounds<TypeParam>::DBMEntry(
										   TypeParam( 0 ), DifferenceBounds<TypeParam>::BOUND_TYPE::SMALLER_EQ ) );

	SUCCEED();
}
