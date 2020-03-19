#pragma once

namespace hypro {

	//Defines what which constraints are added to the template matrix.
	//Generally, if more contraints are added, then runtime will be slower.
	//If location invariants or guards are often just halfspaces, it makes sense to add them since this would make computations easier.
  	enum TEMPLATE_CONTENT {
  		ONLY_INIT = 0, 		//Only initial constraints will be added
  		INIT_INV, 			//Initial constraints + location invariants
  		INIT_INV_GUARD, 	//Initial constraints + location invariants + guards
  		INIT_INV_GUARD_BAD,	//Initial constraints + location invariants + guards + bad states
  		OCTAGON				//Octagonal set
  	};

	//This is the default setting
	struct TemplatePolyhedronDefault {
		//Determines which constraints should be added to the template matrix.
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV_GUARD;
		//Whether the specialized reachability algorithm from Sankaranarayanan 2008 should be used .
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
		//If the alternative reachability algorithm is used, this determines the order to which a Taylor series approximation is computed.
		static constexpr unsigned DERIVATIVE_ORDER = 5;
		//If the alternative reachability algorithm is used, a monotonicity check is conducted before the expensive root enumeration, if this option is false.
		static constexpr bool DIRECTLY_COMPUTE_ROOTS = false;
		//If the alternative reachability algorithm is used, say whether location invariant strengthening should also be used
		static constexpr bool USE_LOCATION_INVARIANT_STRENGTHENING = false;
	};

	struct TemplatePolyhedronDifferent {
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::ONLY_INIT;
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
	};
}
