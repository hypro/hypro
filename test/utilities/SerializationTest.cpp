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
	using IV = std::vector<Interval>;
	using Box = hypro::Box<double>;
	using Point = hypro::Point<double>;
	using Tree = hypro::Hyperoctree<double>;
	std::stringstream ss;

	Box container{ IV{ Interval{ 0, 1 }, Interval{ 0, 1 } } };
	// hyperoctree with 2 splits, maxdepth 2 and the container
	Tree in{ 2, 2, container };
	Tree out{ 1, 1, Box{} };

	auto b1 = Box{ IV{ Interval{ 0.1, 0.6 }, Interval{ 0.1, 0.3 } } };
	auto b2 = Box{ IV{ Interval{ 0.5, 0.75 }, Interval{ 0.5, 1.0 } } };
	auto origin = Point{ { 0, 0 } };
	auto p1 = Point{ { 0.5, 0.2 } };
	auto p2 = Point{ { 0.7, 0.7 } };

	in.add( b1 );
	in.add( b2 );
	EXPECT_TRUE( in.contains( b1 ) );
	EXPECT_TRUE( in.contains( b2 ) );
	EXPECT_TRUE( in.contains( p1 ) );
	EXPECT_TRUE( in.contains( p2 ) );
	EXPECT_FALSE( in.contains( origin ) );

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
		EXPECT_TRUE( out.contains( b1 ) );
		EXPECT_TRUE( out.contains( b2 ) );
		EXPECT_TRUE( out.contains( p1 ) );
		EXPECT_TRUE( out.contains( p2 ) );
		EXPECT_FALSE( out.contains( origin ) );
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
		EXPECT_TRUE( out.contains( b1 ) );
		EXPECT_TRUE( out.contains( b2 ) );
		EXPECT_TRUE( out.contains( p1 ) );
		EXPECT_TRUE( out.contains( p2 ) );
		EXPECT_TRUE( !out.getContainer().empty() );
		EXPECT_FALSE( out.contains( origin ) );
		auto intermediate_child_it = std::find_if( std::begin( out.getChildren() ), std::end( out.getChildren() ), []( const Tree& child ) { return child.getContainer() == Box{ IV{ Interval{ 0.5, 1.0 }, Interval{ 0.5, 1.0 } } }; } );
		auto child1_it = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Tree& child ) { return child.getContainer() == Box{ IV{ Interval{ 0.5, 0.75 }, Interval{ 0.5, 0.75 } } }; } );
		auto child2_it = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Tree& child ) { return child.getContainer() == Box{ IV{ Interval{ 0.5, 0.75 }, Interval{ 0.75, 1.0 } } }; } );
		auto child3_it = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Tree& child ) { return child.getContainer() == Box{ IV{ Interval{ 0.75, 1.0 }, Interval{ 0.5, 0.75 } } }; } );
		auto child4_it = std::find_if( std::begin( intermediate_child_it->getChildren() ), std::end( intermediate_child_it->getChildren() ), []( const Tree& child ) { return child.getContainer() == Box{ IV{ Interval{ 0.75, 1.0 }, Interval{ 0.75, 1.0 } } }; } );
		ASSERT_TRUE( intermediate_child_it != std::end( out.getChildren() ) );
		ASSERT_TRUE( child1_it != std::end( intermediate_child_it->getChildren() ) );
		ASSERT_TRUE( child2_it != std::end( intermediate_child_it->getChildren() ) );
		ASSERT_TRUE( child3_it != std::end( intermediate_child_it->getChildren() ) );
		ASSERT_TRUE( child4_it != std::end( intermediate_child_it->getChildren() ) );
		EXPECT_FALSE( intermediate_child_it->isCovered() );
		EXPECT_TRUE( child1_it->isCovered() );
		EXPECT_TRUE( child2_it->isCovered() );
		EXPECT_FALSE( child3_it->isCovered() );
		EXPECT_FALSE( child4_it->isCovered() );
	}
}
