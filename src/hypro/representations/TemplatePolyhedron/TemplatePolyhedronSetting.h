#pragma once

namespace hypro {

	//Defines what which constraints are added to the template matrix.
	//Generally, if more contraints are added, then runtime will be slower.
	//If location invariants or guards are often just halfspaces, it makes sense to add them since this would make computations easier.
  	enum TEMPLATE_CONTENT {
  		ONLY_INIT = 0, 		//Only initial constraints will be added
  		INIT_INV, 			//Initial constraints + location invariants
  		INIT_INV_GUARD, 	//Initial constraints + location invariants + guards
  		OCTAGON				//Octagonal set
  	};

	//This is the default setting
	struct TemplatePolyhedronDefault {
		//Determines which constraints should be added to the template matrix.
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV;
		//Whether the specialized reachability algorithm from Sankaranarayanan 2008 should be used .
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
		//If the alternative reachability algorithm is used, this determines the order to which a Taylor series approximation is computed.
		//static constexpr unsigned DERIVATIVE_ORDER = 4;
	};

	struct TemplatePolyhedronDifferent {
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::ONLY_INIT;
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
	};
}
