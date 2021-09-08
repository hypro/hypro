#include "test/defines.h"
#include "gtest/gtest.h"
#include <carl/interval/Interval.h>
#include <hypro/datastructures/HybridAutomaton/Visitors.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <variant>

using namespace hypro;

TEST( StateVisitorTest, MinkowskiSumSettingsConversion ) {
	using bType1 = BoxT<double, Converter<double>, BoxLinearOptimizationOff>;
	using bType2 = BoxT<double, Converter<double>, BoxIntervalArithmeticOff>;
	using bType3 = BoxT<double, Converter<double>, BoxAllOff>;
	// create two boxes with different settings
	bType1 b1{ carl::Interval<double>( 1, 2 ) };
	bType2 b2{ carl::Interval<double>( 1 ) };
	bType3 b3{ carl::Interval<double>( 1 ) };

	// create variant for conversion
	using boxVariant = std::variant<bType1, bType2>;

	boxVariant bVar1 = b1;
	boxVariant bVar2 = b2;

	auto tmp = std::visit( genericMinkowskiSumVisitor<boxVariant>(), bVar1, bVar2 );

	EXPECT_NO_THROW( { auto a = std::get<bType1>( tmp ); } );
	EXPECT_ANY_THROW( { auto a = std::get<bType2>( tmp ); } );

	auto tmp2 = std::visit( genericInternalConversionVisitor<boxVariant, bType3>( b3 ), bVar1 );

	EXPECT_NO_THROW( { auto a = std::get<bType1>( tmp2 ); } );
	EXPECT_ANY_THROW( { auto a = std::get<bType2>( tmp2 ); } );
}

TEST( StateVisitorTest, ConvertAndGetTest ) {
	using bType1 = BoxT<double, Converter<double>, BoxLinearOptimizationOff>;
	using bType2 = BoxT<double, Converter<double>, BoxIntervalArithmeticOff>;
	// create two boxes with different settings
	bType1 b1{ carl::Interval<double>( 1, 2 ) };

	// create variant for conversion
	using boxVariant = std::variant<bType1>;

	boxVariant bVar1 = b1;

	bType2 tmp = std::visit( genericConvertAndGetVisitor<bType2>(), bVar1 );
}

TEST( StateVisitorTest, SettingTest ) {
	using bType1 = BoxT<double, Converter<double>, BoxLinearOptimizationOff>;
	using bType2 = BoxT<double, Converter<double>, BoxIntervalArithmeticOff>;

	std::variant<bType1> bVar1 = bType1{ carl::Interval<double>( 1, 2 ) };
	// auto tmp = std::visit( genericSettingVisitor(), bVar1);
	auto tmp = std::visit( []( const auto& obj ) { return obj.getSettings(); }, bVar1 );
	EXPECT_TRUE( tmp.HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION == true );
	EXPECT_TRUE( tmp.USE_INTERVAL_ARITHMETIC == true );
	EXPECT_TRUE( tmp.DETECT_BOX == true );

	std::variant<bType2> bVar2 = bType2{ carl::Interval<double>( 1, 2 ) };
	// auto tmp2 = std::visit( genericSettingVisitor(), bVar2);
	auto tmp2 = std::visit( []( const auto& obj ) { return obj.getSettings(); }, bVar2 );
	EXPECT_TRUE( tmp2.HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION == true );
	EXPECT_TRUE( tmp2.USE_INTERVAL_ARITHMETIC == false );
	EXPECT_TRUE( tmp2.DETECT_BOX == true );

	// std::variant<bType1,bType2> bVar3 = bType2{carl::Interval<double>( 1, 2 )};
	// auto blub = std::visit( genericGetVisitor(), bVar3);

	// auto tmp3 = std::visit( genericSettingVisitor(), bVar3);
	// auto lambda =
	// auto tmp3 = std::visit([](decltype(obj) obj) { return obj.getSettings(); }, bVar3);
	// auto tmp3 = settingVisitor<std::variant<bType1,bType2>>(bVar3);

	// EXPECT_TRUE(tmp3.HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION == true);
	// EXPECT_TRUE(tmp3.USE_INTERVAL_ARITHMETIC == false);
	// EXPECT_TRUE(tmp3.DETECT_BOX == true);
}