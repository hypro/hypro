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

//Polytope.h must be tested - maybe get ppl library and test

//helperMethods have a define but no class, so no templating for them.



//TaylorModel/continous
//TODO: 
struct UtilSetting {
	static constexpr unsigned MAX_ITER_NUM = 50		
	static constexpr float STOP_RATIO = 0.99f
};