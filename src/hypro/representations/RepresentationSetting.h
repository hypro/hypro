/* 
 * RepresentationSetting.h
 *
 * Special settings within the different representations are summarized in this file.
 * Each representation has its own RepresentationSettings-struct and is templated extra, 
 * such that a representation can get its setting via this template in Converter.h.
 *
 * @author Phillip Tse
 * @date 11.10.2017
 *
 */ 

//For box and box_double
static const struct BoxSetting {
	bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
};

//For Polytope and Polytope/util.h
static const struct PolytopeSetting {
	bool fukuda_DEBUG = false;
}

//HPolytopes
static const struct HPolySetting {
	bool REDUCE_NUMBERS = true;
	bool AVOID_CONVERSION = true;
	bool HPOLY_DEBUG_MSG = false;
}

//BoxSupportFunctions 
static const struct BoxSupportFunctionSetting {
	bool SUPPORTFUNCTION_VERBOSE = false;		
    bool BOXSUPPORTFUNCTION_VERBOSE = false;     
};

//NonLineaerOmegaOSupportFunction
static const struct NonLineaerOmegaOSupportFunctionSetting {
	bool SUPPORTFUNCTION_VERBOSE = false;
	bool BOXOPERATOR_VERBOSE = false;
	bool CALCEPSILON_VERBOSE = false;
	bool CALCVALUES_VERBOSE = false;
	bool TEST_ = false;
};

//PolytopeSupportFunctions
static const struct PolytopeSupportFunctionSetting {
	bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
	bool PPOLYTOPESUPPORTFUNCTION_VERIFY = false;
};

//SupportFunctionContent
static const struct SupportFunctionContentSetting {
	bool SUPPORTFUNCTION_VERBOSE = false;
	bool MULTIPLICATIONSUPPORTFUNCTION_VERBOSE = false;
	bool USE_LIN_TRANS_REDUCTION = true;
};

//helperMethods have a define but no class, so no templating for them.

//SupportFunction/util: Cachable and linTrafoParameters
static const struct UtilSetting {
	bool HYPRO_USE_VECTOR_CACHING = false;
};

//TaylorModel/continous
//TODO: 
static const struct UtilSetting {
	unsigned MAX_ITER_NUM = 50		
	float STOP_RATIO = 0.99f
};