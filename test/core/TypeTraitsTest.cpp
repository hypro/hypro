/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomatonComp.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/typetraits.h>

TEST( TypeTraitsTest, LocationType ) {
	EXPECT_TRUE( hypro::is_location_type<hypro::Location<double>>() );
	EXPECT_TRUE( hypro::is_location_type<hypro::ComposedLocation<double>>() );
	EXPECT_TRUE( hypro::is_location_type<hypro::Location<int>>() );
	EXPECT_TRUE( hypro::is_location_type<hypro::ComposedLocation<int>>() );

	EXPECT_FALSE( hypro::is_location_type<int>() );
	EXPECT_FALSE( hypro::is_location_type<double>() );
	EXPECT_FALSE( hypro::is_location_type<std::string>() );
}

TEST( TypeTraitsTest, SmartPointers ) {
	EXPECT_TRUE( hypro::is_shared_ptr<std::shared_ptr<hypro::Location<double>>>() );

	EXPECT_FALSE( hypro::is_shared_ptr<std::unique_ptr<hypro::Location<double>>>() );
	EXPECT_FALSE( hypro::is_shared_ptr<hypro::Location<double>>() );

	EXPECT_TRUE( hypro::is_unique_ptr<std::unique_ptr<hypro::Location<double>>>() );

	EXPECT_FALSE( hypro::is_unique_ptr<std::shared_ptr<hypro::Location<double>>>() );
	EXPECT_FALSE( hypro::is_unique_ptr<hypro::Location<double>>() );
}

TEST( TypeTraitsTest, Numbers ) {
	EXPECT_TRUE( hypro::is_exact<mpq_class> );
	EXPECT_FALSE( hypro::is_exact<float> );
	EXPECT_FALSE( hypro::is_exact<double> );
	EXPECT_FALSE( hypro::is_exact<int> );
}

TEST( TypeTraitsTest, RepresentationNumberType ) {
	{
		bool res = std::is_same_v<double, hypro::rep_number<hypro::Box<double>>>;
		EXPECT_TRUE( res );
	}
	{
		bool res = std::is_same_v<double, hypro::rep_number<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxAllOff>>>;
		EXPECT_TRUE( res );
	}
}