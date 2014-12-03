/* 
 * This file holds the utilities for our parser.
 * @file   Utils.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-14
 * @version 2014-05-14
 */

#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include <vector>
#include <queue>

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;

namespace hypro
{
namespace parser
{
    using namespace boost::fusion;
    typedef unsigned locationId;
	
    struct Initial
    {
        unsigned mLocations;
    };
	
	struct Number
	{
		int integerPart;
		unsigned rationalPart;
	};
    
    struct Matrix
    {
        std::string mName;
        std::vector<std::vector<double> > mMatrix;
    };
    
    struct State
    {
        unsigned mName;
        Matrix mFlow;
        Matrix mInvariant;
    };
    
    struct Transition
    {
        int mId;
		unsigned mName;
		unsigned mSource;
		unsigned mTarget;
        Matrix mGuard;
		Matrix mReset;
    };
    
    std::ostream& operator<<(std::ostream& lhs, const Matrix& rhs )
    {
        lhs << rhs.mName << " [";
        for(auto& row : rhs.mMatrix)
        {
            for(auto& value : row)
            {
                lhs << value << " ";
            }
            lhs << "; ";
        }
        lhs << "]";
        return lhs;
    }
	
	std::ostream& operator<<(std::ostream& lhs, const Initial& rhs)
    {
		lhs << "initial( ";
		lhs << rhs.mLocations;
		/*for(auto& state : rhs.mLocations)
		{
			lhs << state << ",";
		}*/
		lhs << ")";
		return lhs;
	}
    
    std::ostream& operator<<(std::ostream& lhs, const State& rhs)
    {
        lhs << "location(" << std::endl <<
				"\t Name = " << rhs.mName << std::endl << 
				"\t Flow = " << rhs.mFlow << std::endl <<
				"\t Inv = " << rhs.mInvariant << std::endl <<
				")";
        return lhs;
    }
    
    std::ostream& operator<<(std::ostream& lhs, const Transition& rhs)
    {
        lhs << "Transition( " << rhs.mId << std::endl << 
				"\t Name = " << rhs.mName << std::endl <<
				"\t Source = " << rhs.mSource << std::endl <<
				"\t Target = " << rhs.mTarget << std::endl <<
				"\t Guard = " << rhs.mGuard << std::endl <<
				"\t Reset = " << rhs.mReset << std::endl <<
				")";
        return lhs;
    }
}
}

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Initial,
    (unsigned, mLocations)
    )
		
BOOST_FUSION_ADAPT_STRUCT(
	hypro::parser::Number,
	(int, integerPart)
	(unsigned, rationalPart)
	)

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Matrix,
    (std::string, mName)
    (std::vector<std::vector<double> >, mMatrix)
    )

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::State,
    (unsigned, mName)
	(hypro::parser::Matrix, mFlow)
    (hypro::parser::Matrix, mInvariant)
    )
        
BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Transition,
    (int, mId)
	(unsigned, mName)
	(unsigned, mSource)
	(unsigned, mTarget)
    (hypro::parser::Matrix, mGuard)
	(hypro::parser::Matrix, mReset)
    )