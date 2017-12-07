#pragma once

namespace hypro {

	//General struct for support_functions
	struct SupportFunctionSetting {
		static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
	};

	//SupportFunctionContent
	struct SupportFunctionContentSetting {
		static constexpr bool USE_LIN_TRANS_REDUCTION = true;
	};

	//BoxSupportFunctions 
	struct BoxSupportFunctionSetting : SupportFunctionSetting {		
    	static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;     
	};

	//NonLineaerOmegaOSupportFunction
	struct NonLineaerOmegaOSupportFunctionSetting : SupportFunctionSetting {
		static constexpr bool BOXOPERATOR_VERBOSE = false;
		static constexpr bool CALCEPSILON_VERBOSE = false;
		static constexpr bool CALCVALUES_VERBOSE = false;
		static constexpr bool TEST_ = false;
	};

	//PolytopeSupportFunctions
	struct PolytopeSupportFunctionSetting : SupportFunctionSetting {
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
		static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
	};

	//NOTE: must stay as a preprocessor directive as it en/disables includes
	//SupportFunction/util: Cachable and linTrafoParameters
	//struct UtilSetting {
	//	static constexpr bool HYPRO_USE_VECTOR_CACHING = false;
	//};

}