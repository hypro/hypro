#pragma once
#include "../../types.h"
#include "../../representations/types.h"

namespace hypro
{

namespace detail{
	template<typename T>
	struct strategyConversionVisitor : public boost::static_visitor<> {

		template<typename CurrentSNode, typename NewSNode, S>
		void operator()(const CurrentSNode& sNode, const NewSNode& newSNode, S& state){
			state.setSetDirect(boost::apply_visitor(genericConversionVisitor<>(), state.getSet()));
			// TODO: SET TYPE
			//state.setSetType(newSNode::representationType)
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
