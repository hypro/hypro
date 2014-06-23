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
#include <vector>

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;

namespace hypro
{
namespace parser
{
    // TODO temporary datastructures
    
    using namespace boost::fusion;
    
    struct Initial
    {
        std::string mLocation;
        std::string mValuation;
        
        Initial() :
        mLocation(),
        mValuation()
        {}
        
        Initial(std::vector<char> _loc, std::vector<char> _val) :
        mLocation(std::string(_loc.begin(), _loc.end())),
        mValuation(std::string(_val.begin(), _val.end()))
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
        std::string mName;
        /*//Matrix mFlow;
        //Matrix mInvariant;
        
        State() :
        mName()//,
        //mFlow(),
        //mInvariant()
        {
            std::cout << "Construct empty state." << std::endl;
        }
        
        State(std::string _name) ://, Matrix _flow, Matrix _inv) :
        mName(_name)//,
        //mFlow(_flow),
        //mInvariant(_inv)
        {
            std::cout << "Construct filled state." << std::endl;
        }*/
    };
    
    struct Transition
    {
        int mId;
        std::string mType;
        Matrix mMatrix;
    };
    
    std::ostream& operator<<(std::ostream& lhs, const Matrix& rhs )
    {
        lhs << "[";
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
    
    std::ostream& operator<<(std::ostream& lhs, const State& rhs)
    {
        lhs << "location("; //<< rhs.mName << ", Flow: " << rhs.mFlow << ", Invariant: " << rhs.mInvariant << ")";
        return lhs;
    }
    
    std::ostream& operator<<(std::ostream& lhs, const Transition& rhs)
    {
        lhs << "Transition(" << rhs.mId << ")." << rhs.mType << " = " << rhs.mMatrix;
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
    (std::string, mLocation)
    (std::string, mValuation)
    )

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Matrix,
    (std::string, mName)
    (std::vector<std::vector<double> >, mMatrix)
    )

BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::State,
    (std::string, mName)
    //(hypro::parser::Matrix, mFlow)
    //(hypro::parser::Matrix, mInvariant)
    )
        
BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Transition,
    (int, mId)
    (std::string, mType)
    (hypro::parser::Matrix, mMatrix)
    )