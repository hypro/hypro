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
    
    struct State
    {
        int mId;
        char mType;
        std::vector<std::vector<double> > mMatrix;
        
        State() :
        mId(),
        mType(),
        mMatrix()
        {
            std::cout << "Construct State." << std::endl;
        }
        
        State(const int& _id, const char& _type, const std::vector<std::vector<double> >& _matrix) :
        mId(_id),
        mType(_type),
        mMatrix(_matrix)
        {
            std::cout << "Construct State." << std::endl;
        }
    };
    
    struct Transition
    {
        int mId;
        std::string mType;
        std::vector<std::vector<double> > mMatrix;
    };
    
    std::ostream& operator<<(std::ostream& lhs, const std::vector<std::vector<double> >& rhs )
    {
        lhs << "[";
        for(auto& row : rhs)
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
            std::cout << "ping." << std::endl;

        lhs << "State(" << rhs.mId << ")." << rhs.mType << " = " << rhs.mMatrix;
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
    hypro::parser::State,
    (int, mId)
    (char, mType)
    (std::vector<std::vector<double> >, mMatrix)
    )
        
BOOST_FUSION_ADAPT_STRUCT(
    hypro::parser::Transition,
    (int, mId)
    (std::string, mType)
    (std::vector<std::vector<double> >, mMatrix)
    )