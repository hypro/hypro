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
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const HPolytope& _source, const CONV_MODE ){
    return _source;
}

//conversion from V-Polytope to H-Polytope (EXACT or OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const VPolytope& _source, const CONV_MODE mode ){
	HPolytope target;
    if (mode == EXACT){
	    if ( !_source.empty() ) {
			target = HPolytope(_source.vertices());
		}                                                  //Converter<Number>::toHPolytopes the source object into an H-polytope via constructor
    } else if (mode == OVER) {
	    //gets vertices from source object
	    typename VPolytopeT<Number,Converter>::pointVector vertices = _source.vertices();

	    //computes an oriented Box as overapproximation around the source object (returns Halfspaces)
	    PrincipalComponentAnalysis<Number> pca(vertices);
	    std::vector<Halfspace<Number>> planes = pca.box();
	    target = HPolytope(planes);
    }
    return target;
}

//conversion from Box to H-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const Box& _source, const CONV_MODE ){
     //gets dimension of box
     unsigned dim = _source.dimension();
     //only continue if dimension is at least 1
     assert( dim >= 1);

     //initialize normal matrix as zero matrix with 2*dim rows and dim columns
     matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );
     //for every dimension:
     for ( unsigned i = 0; i < dim; ++i ) {
         //write fixed entries (because of box) into the normal matrix (2 each column)
           directions( 2 * i, i ) = Number(-1);
           directions( 2 * i + 1, i ) = Number(1);
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
    typename std::vector<Point<Number>> vertices = _source.vertices();
    if(vertices.empty()){
    	return HPolytopeT<Number,Converter>();
    }
    VPolytope vpoly = VPolytope(vertices);

    return toHPolytope(vpoly, mode);
}

// conversion from support function to H-Polytope (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const SupportFunction& _source, const std::vector<vector_t<Number>>& additionalDirections, const CONV_MODE, unsigned numberOfDirections){
    //gets dimension of source object
    unsigned dim = _source.dimension();

    std::list<unsigned> projections = _source.collectProjections();
	if( projections.size() == dim ){
		//computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
	    std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
	    //only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
	    assert (templateDirections.size() <= std::pow(numberOfDirections, dim));
	    //creates a matrix with one row for each direction and one column for each dimension
	    matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size()+additionalDirections.size() , dim);

	    //fills the matrix with the template directions
	    for (unsigned i=0; i<templateDirections.size();++i){
	        templateDirectionMatrix.row(i) = templateDirections[i];
	    }
	    std::size_t pos = 0;
	    for (unsigned adIndex = templateDirections.size(); adIndex < templateDirectionMatrix.rows(); ++adIndex) {
	        templateDirectionMatrix.row(adIndex) = additionalDirections.at(pos);
	        ++pos;
	    }

	    //std::cout << "Template direction matrix: " << std::endl << templateDirectionMatrix << std::endl;

	    //lets the support function evaluate the offset of the halfspaces for each direction
	    std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
	    assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));

	    std::vector<std::size_t> boundedConstraints;
	    for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
			// std::cout << "Result: " << offsets[offsetIndex] << std::endl;
	        if(offsets[offsetIndex].errorCode != SOLUTION::INFTY){
	            boundedConstraints.push_back(offsetIndex);
	        }
	    }
	    matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), dim);
	    vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
	    pos = boundedConstraints.size()-1;
	    while(!boundedConstraints.empty()){
	        constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
	        constants(pos) = offsets[boundedConstraints.back()].supportValue;
	        boundedConstraints.pop_back();
	        --pos;
	    }

	    //std::cout << "Construct HPoly from " << constraints << " <= " << constants << std::endl;

	    //constructs a H-Polytope out of the computed halfspaces
    	return HPolytope(constraints, constants);

	} else {
		//std::cout << "Projection" << std::endl;
		std::list<unsigned> zeroDimensions;
		for(unsigned i = 0; i < dim; ++i) {
			if(std::find(projections.begin(), projections.end(), i) == projections.end()){
				//std::cout << "Dimension " << i << " is zero." << std::endl;
				zeroDimensions.emplace_back(i);
			}
		}
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(projections, numberOfDirections, dim); // TODO: ATTENTION, 8 is hardcoded here.
		for(auto direction : additionalDirections) {
			// project direction
			for(const auto& dir : zeroDimensions) {
				direction(dir) = Number(0);
			}
			// add projected direction
			if(direction.nonZeros() > 0 && std::find(templateDirections.begin(), templateDirections.end(), direction) == templateDirections.end()) {
				templateDirections.emplace_back(std::move(direction));
			}
		}

		matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size() , dim);

		//fills the matrix with the template directions
		for (unsigned i=0; i<templateDirections.size();++i){
			templateDirectionMatrix.row(i) = templateDirections[i];
		}
		//std::cout << "TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;
		unsigned pos = 0;
		for (unsigned adIndex = templateDirections.size(); adIndex < templateDirectionMatrix.rows(); ++adIndex) {
			templateDirectionMatrix.row(adIndex) = additionalDirections.at(pos);
			++pos;
		}
		//std::cout << "TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;

		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
		assert(offsets.size() == unsigned(templateDirectionMatrix.rows()));

		//std::cout << "Multi-Eval done, add zero constraints" << std::endl;

		std::vector<unsigned> boundedConstraints;
		for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
			if(offsets[offsetIndex].errorCode != SOLUTION::INFTY){
				boundedConstraints.push_back(offsetIndex);
			}
		}
		matrix_t<Number> constraints = matrix_t<Number>::Zero(boundedConstraints.size()+2*zeroDimensions.size(), dim);
		vector_t<Number> constants = vector_t<Number>::Zero(boundedConstraints.size()+2*zeroDimensions.size());
		pos = boundedConstraints.size()-1;
		unsigned zeroDimensionPos = boundedConstraints.size();
		while(!boundedConstraints.empty()){
			constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
			constants(pos) = offsets[boundedConstraints.back()].supportValue;
			boundedConstraints.pop_back();
			--pos;
		}

		//std::cout << "Projected Polytope wiithout zero constraints: " << std::endl << constraints << std::endl << constants << std::endl;

		// add zero dimension constraints
		while(!zeroDimensions.empty()) {
			//std::cout << "Add zero constraints for dimension " << zeroDimensions.front() << " at rows " << zeroDimensionPos << "f" << std::endl;
			vector_t<Number> zDimConstraint = vector_t<Number>::Zero(dim);
			zDimConstraint(zeroDimensions.front()) = Number(1);
			constraints.row(zeroDimensionPos) = zDimConstraint;
			constants(zeroDimensionPos) = Number(0);
			//std::cout << "Positive zero constraint for dimension " << zeroDimensions.front() << ": " << zDimConstraint << std::endl;

			++zeroDimensionPos;

			zDimConstraint(zeroDimensions.front()) = Number(-1);
			constraints.row(zeroDimensionPos) = zDimConstraint;
			constants(zeroDimensionPos) = Number(0);
			//std::cout << "Negative zero constraint for dimension " << zeroDimensions.front() << ": " << zDimConstraint << std::endl;

			zeroDimensions.pop_front();
			++zeroDimensionPos;
		}

		//constructs a H-Polytope out of the computed halfspaces
    	return HPolytope(constraints, constants);
	}
}
