#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/datastructures/HybridAutomaton/Visitors.h"
#include "../../hypro/representations/GeometricObject.h"
#include <carl/interval/Interval.h>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>

using namespace hypro;

TEST(StateVisitorTest, MinkowskiSumSettingsConversion)
{
    using bType1 = BoxT<double,Converter<double>,BoxLinearOptimizationOff>;
    using bType2 = BoxT<double,Converter<double>,BoxIntervalArithmeticOff>;
    // create two boxes with different settings
    bType1 b1{carl::Interval<double>(1,2)};
    bType2 b2{carl::Interval<double>(1)};

    // create variant for conversion
    using boxVariant = boost::variant<bType1, bType2>;

    boxVariant bVar1 = b1;
    boxVariant bVar2 = b2;

    auto tmp = boost::apply_visitor( genericMinkowskiSumVisitor<boxVariant>() , bVar1, bVar2);

    EXPECT_NO_THROW({auto a = boost::get<bType1>(tmp);});
    EXPECT_ANY_THROW({auto a = boost::get<bType2>(tmp);});
}
