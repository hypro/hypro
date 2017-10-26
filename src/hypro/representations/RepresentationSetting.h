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

//Box and Orthogonal polyhedron

//Polytope.h must be tested - maybe get ppl library and test

//BoxSupportFunctions 
struct BoxSupportFunctionSetting {
	static constexpr bool SUPPORTFUNCTION_VERBOSE = false;		
    static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;     
};

//NonLineaerOmegaOSupportFunction
struct NonLineaerOmegaOSupportFunctionSetting {
	static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool BOXOPERATOR_VERBOSE = false;
	static constexpr bool CALCEPSILON_VERBOSE = false;
	static constexpr bool CALCVALUES_VERBOSE = false;
	static constexpr bool TEST_ = false;
};

//PolytopeSupportFunctions
struct PolytopeSupportFunctionSetting {
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = false;
};

//SupportFunctionContent
struct SupportFunctionContentSetting {
	static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool MULTIPLICATIONSUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool USE_LIN_TRANS_REDUCTION = true;
};

//helperMethods have a define but no class, so no templating for them.

//SupportFunction/util: Cachable and linTrafoParameters
struct UtilSetting {
	static constexpr bool HYPRO_USE_VECTOR_CACHING = false;
};

//TaylorModel/continous
//TODO: 
struct UtilSetting {
	static constexpr unsigned MAX_ITER_NUM = 50		
	static constexpr float STOP_RATIO = 0.99f
};