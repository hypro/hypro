/**
 * Specialization for a conversion to an H-polytope.
 * @file converterToHPolytope.tpp
 * @author Simon Froitzheim
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-12-17
 * @version	2016-03-17
 */

#include "Converter.h"

//conversion from H-Polytope to H-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const HPolytope& _source, const CONV_MODE mode ){
    return _source;
}

//conversion from V-Polytope to H-Polytope (EXACT or OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const VPolytope& _source, const CONV_MODE mode ){
	HPolytope target;
    if (mode == EXACT){
	    if ( !_source.empty() ) {
			// degenerate cases
			unsigned size = _source.size();
			unsigned dimension = _source.dimension();
			if ( size == 1 ) {
				// TODO: Return Box constraints.
			} else if ( size < dimension ) {
				std::vector<Point<Number>> vertices = _source.vertices();

				// ATTENTION: Assumption here: _source is reduced, such that the d points in _source span a d-1 dimensional object.

				// find all hyperplanar descriptions by reducing to d dimensions (get the plane)
				std::size_t dim = vertices.size();
				Permutator permutator(dimension, dim);

				std::vector<unsigned> permutation;
				while(!permutator.end()) {
					permutation = permutator();

					// project to chosen dimensions
					std::vector<Point<Number>> reducedVertices;
					reducedVertices.reserve(dim);
					for(const auto& vertex : vertices) {
						vector_t<Number> reductor = vector_t<Number>(dim);
						for(unsigned d = 0; d < dim; ++d)
							reductor(d) = vertex.at(d);

						reducedVertices.push_back(Point<Number>(std::move(reductor)));
					}

					std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( reducedVertices ).first;
					//std::cout << "Conv Hull end" << std::endl;
					for ( auto &facet : facets ) {
						target.insert( facet->halfspace() );
					}

				}

				assert( false );
			} else {
				//std::cout << "Conv Hull" << std::endl;
				// TODO: Chose suitable convex hull algorithm
				typename std::vector<Point<Number>> points = _source.vertices();
				std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
				//std::cout << "Conv Hull end" << std::endl;
				for ( auto &facet : facets ) {
					for( const auto& point : points ) {
						assert( facet->halfspace().normal().dot(point.rawCoordinates()) <= facet->halfspace().offset() );
					}
					target.insert( facet->halfspace() );
				}
			}
		}                                                  //Converter<Number>::toHPolytopes the source object into an H-polytope via constructor
    } else if (mode == OVER) {
    //gets vertices from source object
    typename VPolytopeT<Number,Converter>::pointVector vertices = _source.vertices();

    //computes an oriented Box as overapproximation around the source object (returns Halfspaces)
    std::vector<Halfspace<Number>> planes = computeOrientedBox(vertices);
    target = HPolytope(planes);
    }
    return target;
}

//conversion from Box to H-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const Box& _source, const CONV_MODE mode ){
     //gets dimension of box
     unsigned dim = _source.dimension();
     //only continue if dimension is at least 1
     assert( dim >= 1);

     //initialize normal matrix as zero matrix with 2*dim rows and dim columns
     matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );
     //for every dimension:
     for ( unsigned i = 0; i < dim; ++i ) {
         //write fixed entries (because of box) into the normal matrix (2 each column)
           directions( 2 * i, i ) = -1;
           directions( 2 * i + 1, i ) = 1;
     }

     //initialize distance vector with 2*dim rows
     vector_t<Number> distances = vector_t<Number>( 2 * dim );

      //gets intervals of box
     std::vector<carl::Interval<Number>> intervals = _source.boundaries();
      //for every dimension:
     for ( unsigned i = 0; i < dim; ++i ) {
         //write inverted lower bound values and upper bound values into the distance vector
           distances( 2 * i ) = -intervals[i].lower();
           distances( 2 * i + 1 ) = intervals[i].upper();
     }

     return HPolytope(directions, distances);
}

//conversion from zonotope to H-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const Zonotope& _source, const CONV_MODE mode ){
    //computes vertices from source object
    typename std::vector<vector_t<Number>> vertices = _source.vertices();
    //only continue if any actual vertices were received at all
    assert( !vertices.empty() );
    std::vector<Point<Number>> points;

    for(const auto& vertex : vertices){
        points.emplace_back(vertex);
    }

    return HPolytope(std::move(points));
}

// conversion from support function to H-Polytope (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const SupportFunction& _source, const CONV_MODE mode, unsigned numberOfDirections){
    //gets dimension of source object
    unsigned dim = _source.dimension();

    //computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
    std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
    //only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
    assert (templateDirections.size() <= std::pow(numberOfDirections, dim));
    //creates a matrix with one row for each direction and one column for each dimension
    matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

    //fills the matrix with the template directions
    for (unsigned i=0; i<templateDirections.size();++i){
        templateDirectionMatrix.row(i) = templateDirections[i];
    }

    //lets the support function evaluate the offset of the halfspaces for each direction
    std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
    //std::vector<EvaluationResult<Number>> offsets;
    //for(unsigned i = 0; i < templateDirectionMatrix.rows(); ++i)
    //	offsets.push_back(_source.evaluate(templateDirectionMatrix.row(i)));
    assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
    std::vector<std::size_t> boundedConstraints;
    for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
        if(offsets[offsetIndex].errorCode != SOLUTION::INFTY)
            boundedConstraints.push_back(offsetIndex);
    }
    matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), dim);
    vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
    std::size_t pos = boundedConstraints.size()-1;
    while(!boundedConstraints.empty()){
        constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
        constants(pos) = offsets[boundedConstraints.back()].supportValue;
        boundedConstraints.pop_back();
        --pos;
    }

    //constructs a H-Polytope out of the computed halfspaces
    return HPolytope(constraints, constants);
}
