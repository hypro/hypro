#pragma once
#include <carl/numbers/numbers.h>
#include <iostream>
#include <string>

namespace hypro
{

/**
 * @brief      Struct for reachability analysis algorithm settings.
 * @tparam     Number  The used number type.
 */
template <typename Number>
struct ReachabilitySettings {
    Number timeBound; /// The local time horizon.
    int jumpDepth; /// The maximal number of jumps, i.e. the depth of the search tree.
    Number timeStep; /// Time step size.
    std::string fileName; /// Name for the output file (plotting).
    unsigned long pplDenomimator; /// Common denominator for ppl-numbers (only relevant if ppl is used).
    std::vector<std::vector<std::size_t>> plotDimensions; /// A set of dimension pairs to plot.
    bool uniformBloating = false; /// Bloating settings.
    int clustering = -1; /// -1 = off, 0 = all (aggregation), i = maximal number of segments to unify

    /**
     * @brief      Default constructor.
     */
    ReachabilitySettings<Number>() : timeBound(0), jumpDepth(0), timeStep(0), fileName("out"), pplDenomimator(0) {}

    template<typename T>
    ReachabilitySettings<Number>(const ReachabilitySettings<T>& orig)
    	: timeBound(carl::convert<T,Number>(orig.timeBound))
    	, jumpDepth(orig.jumpDepth)
    	, timeStep(carl::convert<T,Number>(orig.timeStep))
    	, fileName(orig.fileName)
    	, pplDenomimator(orig.pplDenomimator)
    	, plotDimensions(orig.plotDimensions)
    	, uniformBloating(orig.uniformBloating)
    	, clustering(orig.clustering)
    {}

    /**
     * @brief      Assignment operator.
     * @param[in]  _rhs  The right hand side.
     * @return     A reference to this object.
     */
    ReachabilitySettings<Number>& operator=(const ReachabilitySettings<Number>& _rhs) = default;

    /**
     * @brief      Equality comparison operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True if both settings are equal, false otherwise.
     */
    friend bool operator==(const ReachabilitySettings<Number>& lhs, const ReachabilitySettings<Number>& rhs) {
    	return (
    		lhs.timeBound == rhs.timeBound &&
    		lhs.jumpDepth == rhs.jumpDepth &&
    		lhs.timeStep == rhs.timeStep &&
    		lhs.fileName== rhs.fileName &&
    		lhs.pplDenomimator == rhs.pplDenomimator &&
    		lhs.plotDimensions == rhs.plotDimensions &&
    		lhs.uniformBloating == rhs.uniformBloating &&
    		lhs.clustering == rhs.clustering
    		);
    }

    /**
     * @brief      Outstream operator.
     * @param      ostr  The outstream.
     * @param[in]  rhs   The right hand side.
     * @return     Reference to the outstream.
     */
    friend std::ostream& operator<<(std::ostream& ostr, const ReachabilitySettings<Number>& rhs)
    {
        ostr << "Local time-horizon: " << carl::toDouble(rhs.timeBound) << std::endl;
        ostr << "Time-step size: " << carl::toDouble(rhs.timeStep) << std::endl;
        ostr << "Jump-depth: " << rhs.jumpDepth << std::endl;
        ostr << "Clustering: " << rhs.clustering << std::endl;
        return ostr;
    }
};

}  // namespace hypro
