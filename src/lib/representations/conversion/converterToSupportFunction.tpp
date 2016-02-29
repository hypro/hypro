/**
 * Specialization for a converter to a support function.
 * @file converterToSupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2016-01-28
 */

#include "Converter.h"

// conversion from support function to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const SupportFunction& _source, const CONV_MODE mode){
    return _source;
}

// conversion from box to support function
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Box& _source, const CONV_MODE mode) {
    unsigned dim = _source.dimension();                                                     //gets dimension of box
    assert( dim >= 1);                                                                      //only continue if dimension is at least 1

    matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
    for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
        directions( 2 * i, i ) = -1;
        directions( 2 * i + 1, i ) = 1;                                                     //write fixed entries (because of box) into the normal matrix (2 each column)
    }

    vector_t<Number> distances = vector_t<Number>( 2 * dim );                               //initialize distance vector with 2*dim rows

    std::vector<carl::Interval<Number>> intervals = _source.boundaries();                   //gets intervals of box
    for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
        distances( 2 * i ) = -intervals[i].lower();
        distances( 2 * i + 1 ) = intervals[i].upper();                                      //write inverted lower bound values and upper bound values into the distance vector
    }

    return SupportFunction( SF_TYPE::POLY, directions, distances);
}

// conversion from V-Polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const VPolytope& _source, const CONV_MODE mode) {
    auto temp = toHPolytope(_source, mode);
    return SupportFunction( SF_TYPE::POLY, temp.constraints() );
}



// conversion from H-polytope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const HPolytope& _source, const CONV_MODE mode) {
    return SupportFunction( SF_TYPE::POLY, _source.constraints() );
}

// conversion from Zonotope to support function (no differentiation between conversion modes - always EXACT)
template <typename Number>
typename Converter<Number>::SupportFunction Converter<Number>::toSupportFunction( const Zonotope& _source, const CONV_MODE mode) {
    typename std::vector<vector_t<Number>> vertices = _source.vertices();           //computes the vertices from the source zonotope
    assert (!vertices.empty() );                                                           //checks if any vertices were received
    std::vector<Point<Number>> points;
    
    for(const auto& vertex : vertices){
        points.emplace_back(vertex);
    }
    HPolytope temp = HPolytope(std::move(points));                                          		           
    
    return SupportFunction( SF_TYPE::POLY, temp.constraints() );
}