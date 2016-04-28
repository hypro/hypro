#pragma once

#include "../../datastructures/hybridAutomata/Transition.h"

namespace hypro {
namespace parser {

namespace qi = boost::spirit::qi;

struct aggregation_ : qi::symbols<char, Aggregation>
{
    aggregation_()
    {
        add
            ("interval"    , Aggregation::boxAgg)
            ("parallelotope"   , Aggregation::parallelotopeAgg)
        ;
    }

} aggregation;

} // namespace parser
} // namespace hypro
