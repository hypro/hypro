#pragma once

namespace hypro {
	//This is the default setting
	struct SupportFunctionNewDefault {

		//Whether multiple linear transformations in succession should be condensed into one linear transformation
		static constexpr bool USE_LIN_TRANS_REDUCTION = true;
		//If USE_LIN_TRANS_REDUCTION is true, this determines how many linear transformations are condensed. 
		//2^LIN_TRANS_REDUCTION_GROUP_SIZE many linear transformations are condensed.
		static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 2;
		//Whether after a jump, the new segment should be overapproximated by a box (if not active, it will be overapproximated by an octagon)
		static constexpr bool REDUCE_TO_BOX = true;
		
	};

	//This is the default setting
	struct SupportFunctionNewNoReduction {

		//Whether multiple linear transformations in succession should be condensed into one linear transformation
		static constexpr bool USE_LIN_TRANS_REDUCTION = false;
		//If USE_LIN_TRANS_REDUCTION is true, this determines how many linear transformations are condensed. 
		//2^LIN_TRANS_REDUCTION_GROUP_SIZE many linear transformations are condensed.
		static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 1;
		//Whether after a jump, the new segment should be overapproximated by a box (if not active, it will be overapproximated by an octagon)
		static constexpr bool REDUCE_TO_BOX = false;
		
	};
}
