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
    // TODO temporary datastructures
    
    using namespace boost::fusion;
    typedef unsigned locationId;
	
    struct Initial
    {
        unsigned mLocations;
        
        Initial() :
        mLocations()
        {}
        
        Initial(unsigned _loc) :
        mLocations(_loc)
        {}
    };
    
    struct Matrix
    {
        std::string mName;
        std::vector<std::vector<double> > mMatrix;
        
        Matrix() :
        mName(),
        mMatrix()
        {
            std::cout << "Construct empty matrix struct." << std::endl;
        }
        
        Matrix(std::vector<char> _name, std::vector<std::vector<double> > _matrix) :
        mName(std::string(_name.begin(), _name.end())),
        mMatrix(_matrix)
        {
            std::cout << "Construct filled matrix struct." << std::endl;
        }
    };
    
    struct State
    {
        unsigned mName;
        Matrix mFlow;
        Matrix mInvariant;
        
        State() :
        mName(),
        mFlow(),
		mInvariant()
        {
            std::cout << "Construct empty state." << std::endl;
        }
        
        State(unsigned _name) :
        mName(_name),
        mFlow(),
        mInvariant()
        {
            std::cout << "Construct filled state." << std::endl;
        }
		
		State(unsigned _name, Matrix _flow) :
        mName(_name),
        mFlow(_flow),
        mInvariant()
        {
            std::cout << "Construct filled state." << std::endl;
        }
		
		State(unsigned _name, Matrix _flow, Matrix _inv) :
        mName(_name),
        mFlow(_flow),
        mInvariant(_inv)
        {
            std::cout << "Construct filled state." << std::endl;
        }
		
		State(const State& _in) :
		mName(_in.mName),
		mFlow(_in.mFlow),
		mInvariant(_in.mInvariant)
		{}

    };
    
    struct Transition
    {
        int mId;
		unsigned mName;
		unsigned mSource;
		unsigned mTarget;
        Matrix mGuard;
		Matrix mReset;
		
		Transition() :
		mId(-1),
		mName(),
		mSource(),
		mTarget(),
		mGuard(),
		mReset()
		{
			std::cout << "Construct empty transition." << std::endl;
		}
		
		Transition(int _id, unsigned _name, unsigned _source, unsigned _target) :
		mId(_id),
		mName(_name),
		mSource(_source),
		mTarget(_target),
		mGuard(),
		mReset()
		{
			std::cout << "Construct filled transition." << std::endl;
		}
		
		Transition(int _id, unsigned _name, unsigned _source, unsigned _target, Matrix _guard) :
		mId(_id),
		mName(_name),
		mSource(_source),
		mTarget(_target),
		mGuard(_guard),
		mReset()
		{
			std::cout << "Construct filled transition." << std::endl;
		}
		
		Transition(int _id, unsigned _name, unsigned _source, unsigned _target, Matrix _guard, Matrix _reset) :
		mId(_id),
		mName(_name),
		mSource(_source),
		mTarget(_target),
		mGuard(_guard),
		mReset(_reset)
		{
			std::cout << "Construct filled transition." << std::endl;
		}
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
    
    /*
    struct keywords : qi::symbols<std::string, std::string>
    {
        keywords()
        {
            add
                ("states", "STATE")
                ("transitions", "TRANSITION")
            ;
        }
    };
     */
}
}

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Initial,
    (unsigned, mLocations)
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