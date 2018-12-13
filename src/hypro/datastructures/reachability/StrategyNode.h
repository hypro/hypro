#pragma once
#include "../HybridAutomaton/Visitors.h"
#include "../../types.h"
#include "../../representations/types.h"

namespace hypro
{

struct StrategyParameters {
	mpq_class timeStep = 0;
	AGG_SETTING aggregation = AGG_SETTING::NO_AGG;
	int clustering = -1;
	representation_name representation_type = representation_name::UNDEF;
};

namespace detail{
	template<typename State>
	struct strategyConversionVisitor : public boost::static_visitor<> {
		State& mState;
		std::size_t mSubsetIndex;

		strategyConversionVisitor() = delete;
		strategyConversionVisitor(State& s, std::size_t subset=0) : mState(s), mSubsetIndex(subset) {}

		template<typename Node>
		void operator()(Node& ) const {
			mState.setSet(boost::apply_visitor(::hypro::genericConversionVisitor<typename State::repVariant, typename Node::representationType>(), mState.getSet(mSubsetIndex)), mSubsetIndex);
			//mState.setSetType(Node::representationType::type(),mSubsetIndex);
			TRACE("hypro.utility","Expect conversion of state set at pos " << mSubsetIndex << " to type " << typeid(typename Node::representationType).name() << " and is actually " << mState.getSetType(mSubsetIndex));
			TRACE("hypro.utility","Should be of type " << Node::representationType::type());
			assert(mState.getSetType(mSubsetIndex) == Node::representationType::type());
		}
	};

	struct getParametersVisitor : public boost::static_visitor<StrategyParameters> {

		getParametersVisitor() = default;

		template<typename Node>
		const StrategyParameters& operator()(Node& n) const {
			return n.mParameters;
		}
	};
}

template<typename Representation>
struct StrategyNode {
	typedef Representation representationType;

	StrategyParameters mParameters;

	StrategyNode(mpq_class ts)
	{
		mParameters.timeStep = ts;
		mParameters.aggregation = AGG_SETTING::MODEL;
		mParameters.clustering = -1;
		mParameters.representation_type = Representation::type();
	}

	StrategyNode(mpq_class ts, AGG_SETTING agg, int clu)
	{
		mParameters.timeStep = ts;
		mParameters.aggregation = agg;
		mParameters.clustering = clu;
		mParameters.representation_type = Representation::type();
	}
};

} // hypro
