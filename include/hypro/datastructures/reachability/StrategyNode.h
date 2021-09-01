#pragma once
#include "../../representations/types.h"
#include "../../types.h"
#include "../HybridAutomaton/Visitors.h"

namespace hypro {

struct StrategyParameters {
	mpq_class timeStep = 0;
	AGG_SETTING aggregation = AGG_SETTING::NO_AGG;
	int clustering = -1;
	representation_name representation_type = representation_name::UNDEF;

#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const StrategyParameters& sp ) {
		// ostr << "Representation: " << sp.representation_type;
		ostr << " Timestep: " << sp.timeStep;
		ostr << " Aggregation: " << sp.aggregation;
		ostr << " clustering: " << sp.clustering << std::endl;
#else
	friend std::ostream& operator<<( std::ostream& ostr, const StrategyParameters& /*sp*/ ) {
#endif
		return ostr;
	}
};

namespace detail {

template <typename State>
struct strategyConversionVisitor {
	State& mState;
	std::size_t mSubsetIndex;

	strategyConversionVisitor() = delete;
	strategyConversionVisitor( State& s, std::size_t subset = 0 )
		: mState( s )
		, mSubsetIndex( subset ) {}

	template <typename Node>
	void operator()( Node& ) const {
		TRACE( "hypro.utility", "Expect conversion of state set at pos " << mSubsetIndex << " to type " << typeid( typename Node::representationType ).name() << " and is actually " << mState.getSetType( mSubsetIndex ) );
		// auto tmp = std::visit(::hypro::genericConversionVisitor<typename State::repVariant, typename Node::representationType>(), mState.getSet(mSubsetIndex));
		// auto tmp = std::visit(::hypro::genericConvertAndGetVisitor<typename Node::representationType>(), mState.getSet(mSubsetIndex));
		// TRACE("hypro.utility","Conversion result: " << tmp);
		// mState.setSet(tmp);
		mState.setSet( std::visit( ::hypro::genericConversionVisitor<typename State::repVariant, typename Node::representationType>(), mState.getSet( mSubsetIndex ) ), mSubsetIndex );
		// mState.setSetType(Node::representationType::type(),mSubsetIndex);

		TRACE( "hypro.utility", "Should be of type " << Node::representationType::type() );
		assert( mState.getSetType( mSubsetIndex ) == Node::representationType::type() );
	}
};

struct getParametersVisitor {
	getParametersVisitor() = default;

	template <typename Node>
	const StrategyParameters& operator()( Node& n ) const {
		return n.mParameters;
	}
};

}  // namespace detail

template <typename Representation>
struct StrategyNode {
	typedef Representation representationType;

	StrategyParameters mParameters;

	StrategyNode( mpq_class ts ) {
		mParameters.timeStep = ts;
		mParameters.aggregation = AGG_SETTING::MODEL;
		mParameters.clustering = -1;
		mParameters.representation_type = Representation::type();
	}

	StrategyNode( mpq_class ts, AGG_SETTING agg, int clu ) {
		mParameters.timeStep = ts;
		mParameters.aggregation = agg;
		mParameters.clustering = clu;
		mParameters.representation_type = Representation::type();
	}

	// StrategyNode(const StrategyParameters& param){
	//	mParameters.timeStep = param.timeStep;
	//	mParameters.aggregation = param.aggregation;
	//	mParameters.clustering = param.clustering;
	//	mParameters.representation_type = Representation::type();
	// }
};

}  // namespace hypro
