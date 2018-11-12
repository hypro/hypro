#pragma once
#include "../../types.h"
#include "../../representations/types.h"

namespace hypro
{

namespace detail{
	template<typename State>
	struct strategyConversionVisitor : public boost::static_visitor<> {
		State& mState;

		strategyConversionVisitor() = delete;
		strategyConversionVisitor(State& s) : mState(s) {}

		template<typename Node>
		void operator()(Node& ) const {
			mState.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State::repVariant, typename State::NumberType, typename Node::representationType>(), mState.getSet()));
			mState.setSetType(Node::representationType::type());
		}
	};
}

template<typename Representation>
struct StrategyNode {
	typedef Representation representationType;
	mpq_class timeStep;
	AGG_SETTING aggregation = AGG_SETTING::NO_AGG;
	int clustering = -1;

	StrategyNode(mpq_class ts)
		: timeStep(ts)
		, aggregation(AGG_SETTING::MODEL)
		, clustering(-1)
	{
		//TRACE("hydra.datastructures","Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation);
		//std::cout << "Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation << ", clustering " << clustering << std::endl;
	}

	StrategyNode(mpq_class ts, AGG_SETTING agg, int clu)
		: timeStep(ts)
		, aggregation(agg)
		, clustering(clu)
	{
		//std::cout << "Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation << ", clustering " << clustering << std::endl;
	}
};

} // hypro
