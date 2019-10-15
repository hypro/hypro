#pragma once

namespace hypro {

	//Defines what which constraints are added to the template matrix.
	//Generally, if more contraints are added, then runtime will be slower.
	//If location invariants or guards are often just halfspaces, it makes sense to add them since this would make computations easier.
  	enum TEMPLATE_CONTENT {
  		ONLY_INIT = 0, 		//Only initial constraints will be added
  		INIT_INV, 			//Initial constraints + location invariants
  		INIT_INV_GUARD, 	//Initial constraints + location invariants + guards, makes sense in models where guard is satisfied initially
  		OCTAGON				//Octagonal set
  	};

	//This is the default setting
	struct TemplatePolyhedronDefault {
		//Determines which constraints should be added to the template matrix.
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::ONLY_INIT;
		//Whether the specialized reachability algorithm from Sankaranarayanan 2008 should be used .
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = true;
		//If the alternative reachability algorithm is used, this determines the order to which a Taylor series approximation is computed.
		static constexpr unsigned DERIVATIVE_ORDER = 5;
		//If the alternative reachability algorithm is used, a monotonicity check is conducted before the expensive root enumeration, if this option is false.
		static constexpr bool DIRECTLY_COMPUTE_ROOTS = false;
	};

	struct TemplatePolyhedronDifferent {
		static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::ONLY_INIT;
		static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
	};
}
