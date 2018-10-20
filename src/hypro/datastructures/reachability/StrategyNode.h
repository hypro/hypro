#pragma once
#include "../../types.h"
#include "../../representations/types.h"

namespace hypro
{

struct StrategyNode {
	mpq_class timeStep;
	representation_name representation;
	AGG_SETTING aggregation = AGG_SETTING::NO_AGG;
	int clustering = -1;

	StrategyNode(mpq_class ts, representation_name rep)
		: timeStep(ts)
		, representation(rep)
		, aggregation(AGG_SETTING::MODEL)
		, clustering(-1)
	{
		//TRACE("hydra.datastructures","Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation);
		//std::cout << "Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation << ", clustering " << clustering << std::endl;
	}

	StrategyNode(mpq_class ts, representation_name rep, AGG_SETTING agg, int clu)
		: timeStep(ts)
		, representation(rep)
		, aggregation(agg)
		, clustering(clu)
	{
		//std::cout << "Create strategy node with timestep " << ts << ", representation: " << rep << ", aggregation: " << aggregation << ", clustering " << clustering << std::endl;
	}
};

} // hypro
