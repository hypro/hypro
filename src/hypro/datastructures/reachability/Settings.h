#pragma once
#include "../../types.h"

#include <carl/numbers/numbers.h>
#include <iosfwd>
#include <string>

namespace hypro {

/**
 * @brief      Struct for reachability analysis algorithm settings.
 */
struct ReachabilitySettings {
	tNumber timeBound;									   /// The local time horizon.
	int jumpDepth;										   /// The maximal number of jumps, i.e. the depth of the search tree.
	tNumber timeStep;									   /// Time step size.
	std::string fileName;								   /// Name for the output file (plotting).
	unsigned long pplDenomimator;						   /// Common denominator for ppl-numbers (only relevant if ppl is used).
	std::vector<std::vector<std::size_t>> plotDimensions;  /// A set of dimension pairs to plot.
	bool uniformBloating = false;						   /// Bloating settings.
	int clustering = -1;								   /// -1 = off, 0 = all (aggregation), i = maximal number of segments to unify
	bool useInvariantTimingInformation = true;
	bool useGuardTimingInformation = true;
	bool useBadStateTimingInformation = true;

	/**
     * @brief      Default constructor.
     */
	ReachabilitySettings()
		: timeBound( 0 )
		, jumpDepth( 0 )
		, timeStep( 0 )
		, fileName( "out" )
		, pplDenomimator( 0 ) {
		plotDimensions.push_back( std::vector<std::size_t>() );
		plotDimensions[0].push_back( 0 );
		plotDimensions[0].push_back( 1 );
	}

	ReachabilitySettings( const ReachabilitySettings& orig ) = default;

	/**
     * @brief      Assignment operator.
     * @param[in]  _rhs  The right hand side.
     * @return     A reference to this object.
     */
	ReachabilitySettings& operator=( const ReachabilitySettings& _rhs ) = default;

	/**
     * @brief      Equality comparison operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True if both settings are equal, false otherwise.
     */
	friend bool operator==( const ReachabilitySettings& lhs, const ReachabilitySettings& rhs ) {
		return (
			  lhs.timeBound == rhs.timeBound &&
			  lhs.jumpDepth == rhs.jumpDepth &&
			  lhs.timeStep == rhs.timeStep &&
			  lhs.fileName == rhs.fileName &&
			  lhs.pplDenomimator == rhs.pplDenomimator &&
			  lhs.plotDimensions == rhs.plotDimensions &&
			  lhs.uniformBloating == rhs.uniformBloating &&
			  lhs.clustering == rhs.clustering &&
			  lhs.useBadStateTimingInformation == rhs.useBadStateTimingInformation &&
			  lhs.useGuardTimingInformation == rhs.useGuardTimingInformation &&
			  lhs.useInvariantTimingInformation == rhs.useInvariantTimingInformation );
	}

	/**
     * @brief      Outstream operator.
     * @param      ostr  The outstream.
     * @param[in]  rhs   The right hand side.
     * @return     Reference to the outstream.
     */
	friend std::ostream& operator<<( std::ostream& ostr, const ReachabilitySettings& rhs ) {
		ostr << "Local time-horizon: " << carl::toDouble( rhs.timeBound ) << std::endl;
		ostr << "Time-step size: " << carl::toDouble( rhs.timeStep ) << std::endl;
		ostr << "Jump-depth: " << rhs.jumpDepth << std::endl;
		ostr << "Clustering: " << rhs.clustering << std::endl;
		return ostr;
	}
};

}  // namespace hypro
