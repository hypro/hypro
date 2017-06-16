/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2016-03-17
 */

#include "Converter.h"

//conversion from V-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const VPolytope& _source, const CONV_MODE  ){
	return _source;
}

template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const ConstraintSet& _source, const CONV_MODE ){
    return VPolytopeT<Number,Converter>(_source.matrix(), _source.vector());
}

template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Ellipsoid& _source, const CONV_MODE  ){
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
	return VPolytope(constraintMatrix, b);
}

//conversion from H-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const HPolytope& _source, const CONV_MODE  ){
	//exact conversion
	return VPolytope(_source.matrix(), _source.vector());
}

//conversion from Box to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Box& _source, const CONV_MODE  ){
	return VPolytope(_source.vertices());
}

//conversion from Zonotope to V-Polytope (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const Zonotope& _source, const CONV_MODE  ){
	return VPolytope(_source.vertices());
}

//TODO verification of alternatoive underapproximation (yields only one point for some reason)
// conversion from Support Function to V-Polytope (OVER, UNDER or ALTERNATIVE)
//ALTERNATIVE mode gives an underapproximation that is probably better but costs a lot more to compute
template<typename Number>
typename Converter<Number>::VPolytope Converter<Number>::toVPolytope( const SupportFunction& _source, const CONV_MODE mode, unsigned numberOfDirections){
	VPolytope target;
	if (mode == OVER){
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
                assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
                std::vector<std::size_t> boundedConstraints;
                for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
                        if(offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                                boundedConstraints.push_back(offsetIndex);
                }
                //builds halfspaces with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
                matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), dim);
                vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
                std::size_t pos = boundedConstraints.size()-1;
                while(!boundedConstraints.empty()){
                     constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
                     constants(pos) = offsets[boundedConstraints.back()].supportValue;
                     boundedConstraints.pop_back();
                     --pos;
                }

	        //constructs a V-Polytope out of the computed halfspaces (implicit conversion H->V)
	        target = VPolytope(constraints, constants);
	        }
        if (mode == UNDER){
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
                assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
                std::vector<std::size_t> boundedConstraints;
                for(unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex){
                        if(offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                                boundedConstraints.push_back(offsetIndex);
                }

                //builds a pointVector from boundary points with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
                std::vector<Point<Number>> points = std::vector<Point<Number>>(boundedConstraints.size());
                std::size_t pos = boundedConstraints.size()-1;
                while(!boundedConstraints.empty()){
                     points[pos] = offsets[boundedConstraints.back()].optimumValue;
                     boundedConstraints.pop_back();
                     --pos;
                }

                //constructs a V-Polytope out of the computed points
                target = VPolytope(points);
        }



        if (mode == ALTERNATIVE){
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

                //computes some central boundary points based on the directions (pretty precise but expensive)
                std::vector<Point<Number>> boundaryPoints = computeBoundaryPointsExpensive(_source, templateDirectionMatrix);

                target = VPolytope(boundaryPoints);

        }
	        return target;
}
