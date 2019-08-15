#pragma once


/*
    Requirements:
 */

namespace hypro {


/**
 * @brief Container for a flowpipe, i.e. an ordered sequence of state sets (flowpipe segments).
 *
 * @tparam Number Used number type.
 */
template<typename Number>
class Flowpipe
{
private:
    /* data */
public:
    Flowpipe(/* args */);
    ~Flowpipe();
};

} // namespace hypro

#include "Flowpipe.tpp"
