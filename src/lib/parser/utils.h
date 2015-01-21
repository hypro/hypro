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
	
	template<typename Number>
    struct Initial
    {
        unsigned mLocations;
		Number mNumber;
    };
	
	
    template<typename Number>
    struct Matrix
    {
        std::string mName;
        std::vector<std::vector<Number> > mMatrix;
    };
    
	template<typename Number>
    struct State
    {
        unsigned mName;
        Matrix<Number> mFlow;
        Matrix<Number> mInvariant;
    };
    
	template<typename Number>
    struct Transition
    {
        int mId;
		unsigned mName;
		unsigned mSource;
		unsigned mTarget;
        Matrix<Number> mGuard;
		Matrix<Number> mReset;
    };
    
	template<typename Number>
    std::ostream& operator<<(std::ostream& lhs, const Matrix<Number>& rhs )
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
	
	template<typename Number>
	std::ostream& operator<<(std::ostream& lhs, const Initial<Number>& rhs)
    {
		lhs << "initial( ";
		lhs << rhs.mLocations;
		lhs << " Number: " << rhs.mNumber;
		//lhs << " Type: " << typeid(rhs.mNumber).name();
		lhs << ")";
		return lhs;
	}
    
	template<typename Number>
    std::ostream& operator<<(std::ostream& lhs, const State<Number>& rhs)
    {
        lhs << "location(" << std::endl <<
				"\t Name = " << rhs.mName << std::endl << 
				"\t Flow = " << rhs.mFlow << std::endl <<
				"\t Inv = " << rhs.mInvariant << std::endl <<
				")";
        return lhs;
    }
    
	template<typename Number>
    std::ostream& operator<<(std::ostream& lhs, const Transition<Number>& rhs)
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

BOOST_FUSION_ADAPT_TPL_STRUCT(
	(Number),
    (hypro::parser::Initial) (Number),
    (unsigned, mLocations)
	(Number, mNumber)
    )

BOOST_FUSION_ADAPT_TPL_STRUCT(
	(Number),
    (hypro::parser::Matrix) (Number),
    (std::string, mName)
    (std::vector<std::vector<Number> >, mMatrix)
    )

BOOST_FUSION_ADAPT_TPL_STRUCT(
	(Number),
    (hypro::parser::State) (Number),
    (unsigned, mName)
	(hypro::parser::Matrix<Number>, mFlow)
    (hypro::parser::Matrix<Number>, mInvariant)
    )
        
BOOST_FUSION_ADAPT_TPL_STRUCT(
	(Number),
    (hypro::parser::Transition) (Number),
    (int, mId)
	(unsigned, mName)
	(unsigned, mSource)
	(unsigned, mTarget)
    (hypro::parser::Matrix<Number>, mGuard)
	(hypro::parser::Matrix<Number>, mReset)
    )