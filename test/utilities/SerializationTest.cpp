/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 17.02.22.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <carl/numbers/numbers.h>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/serialization/serialization.h>
#include <sstream>

TEST( runUtilityTests, RationalNumbersSerialization ) {
	std::stringstream ss;
	mpq_class a{ 1, 3 };
	{
		cereal::BinaryOutputArchive oarchive( ss );	 // Create an output archive

		oarchive( a );	// Write the data to the archive
	}
	{
		cereal::BinaryInputArchive iarchive( ss );	// Create an input archive
		mpq_class b;
		iarchive( b );
		EXPECT_EQ( a, b );
	}
}

TEST( runUtilityTests, IntervalSerialization ) {
	using Interval = carl::Interval<double>;
	using RationalInterval = carl::Interval<mpq_class>;
	std::stringstream ss;
	Interval i1, i2;
	RationalInterval i3, i4;

	{
		cereal::BinaryOutputArchive oarchive( ss );	 // Create an output archive
		i1 = Interval{ 1, 2 };
		i3 = RationalInterval{ 1, 2 };

		oarchive( i1 );	 // Write the data to the archive
		oarchive( i3 );	 // Write the data to the archive
	}
	{
		cereal::BinaryInputArchive iarchive( ss );	// Create an input archive

		iarchive( i2 );	 // Read the data from the archive
		iarchive( i4 );	 // Read the data from the archive
	}
	EXPECT_EQ( i1, i2 );
	EXPECT_EQ( i3, i4 );
}

TEST( runUtilityTests, BoxSerialization ) {
	using Interval = carl::Interval<double>;
	using Box = hypro::Box<double>;
	std::stringstream ss;

	Box in{ std::vector<Interval>{ Interval{ 1, 2 }, Interval{ 2, 3 } } };
	Box out;

	{
		cereal::BinaryOutputArchive oarchive( ss );	 // Create an output archive

		oarchive( in );	 // Write the data to the archive
	}
	{
		cereal::BinaryInputArchive iarchive( ss );	// Create an input archive
		iarchive( out );							// Read the data from the archive
	}
	EXPECT_EQ( in, out );
}

TEST( runUtilityTests, EmptyHyperoctreeSerialization ) {
	using Tree = hypro::Hyperoctree<double>;
	std::stringstream ss;

	Tree in, out;

	{
		cereal::BinaryOutputArchive oarchive( ss );	 // Create an output archive
		oarchive( in );								 // Write the data to the archive
	}
	{
		cereal::BinaryInputArchive iarchive( ss );	// Create an input archive
		iarchive( out );							// Read the data from the archive
	}
	EXPECT_EQ( in, out );
}

TEST( runUtilityTests, HyperoctreeSerialization ) {
	using Interval = carl::Interval<double>;
	using Box = hypro::Box<double>;
	using Tree = hypro::Hyperoctree<double>;
	std::stringstream ss;

	Box container{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } };
	// hyperoctree with 2 splits, maxdepth 2 and the container
	Tree in{ 2, 2, container };
	Tree out{ 1, 1, Box{} };

	in.add( Box{ std::vector<Interval>{ Interval{ 0.1, 0.6 }, Interval{ 0.1, 0.3 } } } );
	in.add( Box{ std::vector<Interval>{ Interval{ 0.5, 0.75 }, Interval{ 0.5, 1.0 } } } );

	{
		{
			cereal::BinaryOutputArchive oarchive( ss );	 // Create an output archive
			oarchive( in );								 // Write the data to the archive
		}
		{
			cereal::BinaryInputArchive iarchive( ss );	// Create an input archive
			iarchive( out );							// Read the data from the archive
		}
		EXPECT_EQ( in, out );
	}
	{
		out = Tree{};
		{
			std::ofstream fs{ "serialization", std::ios::binary };
			cereal::BinaryOutputArchive oarchive( fs );	 // Create an output archive
			oarchive( in );								 // Write the data to the archive
		}
		{
			std::ifstream fs{ "serialization", std::ios::binary };
			cereal::BinaryInputArchive iarchive( fs );	// Create an input archive
			iarchive( out );							// Read the data from the archive
		}
		EXPECT_EQ( in, out );
	}
}
