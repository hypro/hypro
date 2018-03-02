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
#include "../../util/templateDirections.h"

//conversion from H-Polytope to H-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const HPolytope& _source, const CONV_MODE ){
    return _source;
}

template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const ConstraintSet& _source, const CONV_MODE ){
    return HPolytopeT<Number,Converter,HPolytopeSetting>(_source.matrix(), _source.vector());
}

template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const Ellipsoid& _source, const CONV_MODE ){
	vector_t<Number> l(_source.dimension());
	l.setZero();
	vector_t<Number> evaluation;
	std::vector<vector_t<Number>> constraints;
	vector_t<Number> b;
	for ( std::size_t i = 0; i < _source.dimension(); i++) {
	    for (std:: size_t j = i+1; j < _source.dimension(); j++ ) {
	        // Evaluation in 8 directions for each pair of dimensions
	        // only compute 4 directions, as E is symmetric. Comments denote the combination of i,j
	        // (1,0)
	        l(i) = 1;
	        evaluation = _source.evaluate(l);
	        constraints.push_back(evaluation);
	        constraints.push_back(-evaluation);
	        // (1,1)
	        l(j) = 1;
	        evaluation = _source.evaluate(l);
	        constraints.push_back(evaluation);
	        constraints.push_back(-evaluation);
	        // (-1,1)
	        l(i) = -1;
	        evaluation = _source.evaluate(l);
	        constraints.push_back(evaluation);
	        constraints.push_back(-evaluation);
	        // (0,1)
	        l(i) = 0;
	        evaluation = _source.evaluate(l);
	        constraints.push_back(evaluation);
	        constraints.push_back(-evaluation);
	        l(j) = 0;
	    }
	}
	b.setOnes(constraints.size());
	matrix_t<Number> constraintMatrix(constraints.size(),_source.dimension());
	for (std::size_t i = 0; i < constraints.size(); i++){
	    constraintMatrix.row(i) = constraints.at(i);
	}
	return HPolytopeT<Number,Converter,HPolytopeSetting>(constraintMatrix, b);
}

//conversion from V-Polytope to H-Polytope (EXACT or OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const VPolytope& _source, const CONV_MODE mode ){
	if(_source.empty()) {
		return HPolytope::Empty();
	}

	HPolytope target;
    if (mode == EXACT){
		target = HPolytope(_source.vertices());
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
     std::size_t dim = _source.dimension();
     //only continue if dimension is at least 1
     assert( dim >= 1);

     //initialize normal matrix as zero matrix with 2*dim rows and dim columns
     matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );
     //for every dimension:
     for ( std::size_t i = 0; i < dim; ++i ) {
         //write fixed entries (because of box) into the normal matrix (2 each column)
           directions( 2 * i, i ) = Number(-1);
           directions( 2 * i + 1, i ) = Number(1);
     }

     //initialize distance vector with 2*dim rows
     vector_t<Number> distances = vector_t<Number>( 2 * dim );

      //gets intervals of box
     std::vector<carl::Interval<Number>> intervals = _source.boundaries();
      //for every dimension:
     for ( std::size_t i = 0; i < dim; ++i ) {
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
    	return HPolytopeT<Number,Converter,HPolytopeSetting>();
    }
    VPolytope vpoly = VPolytope(vertices);

    return toHPolytope(vpoly, mode);
}

// conversion from support function to H-Polytope (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope( const SupportFunction& _source, const std::vector<vector_t<Number>>& additionalDirections, const CONV_MODE, std::size_t numberOfDirections){
    //gets dimension of source object
    std::size_t dim = _source.dimension();

    std::vector<std::size_t> projections = _source.collectProjections();
    //std::cout << __func__ << ": collected " << projections.size() << " projections." << std::endl;
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
	    for (Eigen::Index adIndex = Eigen::Index(templateDirections.size()); adIndex < templateDirectionMatrix.rows(); ++adIndex) {
	        templateDirectionMatrix.row(adIndex) = additionalDirections.at(pos);
	        ++pos;
	    }

	    //lets the support function evaluate the offset of the halfspaces for each direction
	    std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix, false);
	    assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));

	    std::vector<std::size_t> boundedConstraints;
	    for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
			//std::cout << "Result: " << offsets[offsetIndex] << std::endl;
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

	    //constructs a H-Polytope out of the computed halfspaces
    	return HPolytope(constraints, constants);

	} else {
		//std::cout << "Projection" << std::endl;
		//for(auto dim : projections) {
		//	std::cout << "projection dimension " << dim << std::endl;
		//}
		std::list<unsigned> zeroDimensions;
		for(unsigned i = 0; i < dim; ++i) {
			if(std::find(projections.begin(), projections.end(), i) == projections.end()){
				//std::cout << "Dimension " << i << " is zero." << std::endl;
				zeroDimensions.emplace_back(i);
			}
		}
		//std::cout << __func__ << ": compute template ... ";
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(projections, numberOfDirections, dim); // TODO: ATTENTION, 8 is hardcoded here.
		//std::cout << "done." << std::endl;
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
		std::size_t pos = 0;
		for (Eigen::Index adIndex = Eigen::Index(templateDirections.size()); adIndex < templateDirectionMatrix.rows(); ++adIndex) {
			templateDirectionMatrix.row(adIndex) = additionalDirections.at(pos);
			++pos;
		}
		//std::cout << __func__ << ": TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;

		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix, false);
		assert(offsets.size() == unsigned(templateDirectionMatrix.rows()));

		//std::cout << "Multi-Eval done, reduce to relevant dimensions" << std::endl;

		std::size_t newDim = projections.size();
		matrix_t<Number> constraints = matrix_t<Number>(offsets.size(), newDim);
		vector_t<Number> constants = vector_t<Number>(offsets.size());
		for(unsigned rowIndex = 0; rowIndex < Eigen::Index(offsets.size()); ++rowIndex) {
			Eigen::Index colPos = 0;
			for(auto projIt = projections.begin(); projIt != projections.end(); ++projIt, ++colPos) {
				constraints(rowIndex,colPos) = templateDirectionMatrix(rowIndex, (*projIt));
			}
			constants(rowIndex) = offsets.at(rowIndex).supportValue;
		}

		//std::cout << "Construct polytope from constraints " << constraints << " and constants " << constants << std::endl;

		//constructs a H-Polytope out of the computed halfspaces
    	return HPolytope(constraints, constants);
	}
}

#ifdef HYPRO_USE_PPL

//Convert a ppl polytope into a HPolytope. Luckily, ppl polytopes have halfspaces internally.
template<typename Number>
typename Converter<Number>::HPolytope Converter<Number>::toHPolytope(const Polytope& source, const CONV_MODE){
	Converter<Number>::VPolytope v(source.vertices());
	return toHPolytope(v, CONV_MODE::EXACT);
}

#endif
