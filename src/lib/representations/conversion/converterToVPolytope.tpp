/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "Converter.h"

//conversion from V-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const VPolytope& _source, const CONV_MODE mode ){
    return _source;
}


//conversion from H-Polytope to V-Polytope (EXACT or OVER)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const HPolytope& _source, const CONV_MODE mode ){
    //exact conversion
    VPolytope target;
    if (mode == EXACT){
        target = VPolytope(_source.matrix(), _source.vector());
    }
    //overapproximation
    if (mode == OVER){
        //converts source object into a v-polytope first
        VPolytope temp = VPolytope(_source.matrix(), _source.vector());
        //gets vertices from source object
        typename VPolytopeT<Number,Converter>::pointVector vertices = temp.vertices();
        
        //computes an oriented Box as overapproximation around the source object (returns hyperplanes)
        std::vector<Hyperplane<Number>> planes = computeOrientedBox(vertices);
        //saves received hyperplanes as an H-Polytope
        HPolytope temp2 = HPolytope(planes);
        //converts back into V-representation
        target = VPolytope(temp2.matrix(), temp2.vector());
    }
    return target;
}

//conversion from Box to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Box& _source, const CONV_MODE mode ){
    return VPolytope(_source.vertices());
}

//conversion from Zonotope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Zonotope& _source, const CONV_MODE mode ){
    return VPolytope(_source.vertices());
}

//TODO conversion from Support Function to V-Polytope (OVER or UNDER)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const SupportFunction& _source, const CONV_MODE mode){
    return VPolytope();
}
