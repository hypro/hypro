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
    };
    
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