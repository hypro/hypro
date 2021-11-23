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
#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

//conversion from H-Polytope to H-Polytope (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const HPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return _source;
}

template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const ConstraintSetT<Number, inSetting>& _source, const CONV_MODE ) {
	return HPolytopeT<Number, Converter<Number>, HPolytopeSetting>( _source.matrix(), _source.vector() );
}

template <typename Number>
template <typename HPolySetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const Ellipsoid& _source, const CONV_MODE ) {
	vector_t<Number> l( _source.dimension() );
	l.setZero();
	vector_t<Number> evaluation;
	std::vector<vector_t<Number>> constraints;
	vector_t<Number> b;
	for ( std::size_t i = 0; i < _source.dimension(); i++ ) {
		for ( std::size_t j = i + 1; j < _source.dimension(); j++ ) {
			// Evaluation in 8 directions for each pair of dimensions
			// only compute 4 directions, as E is symmetric. Comments denote the combination of i,j
			// (1,0)
			l( i ) = 1;
			evaluation = _source.evaluate( l );
			constraints.push_back( evaluation );
			constraints.push_back( -evaluation );
			// (1,1)
			l( j ) = 1;
			evaluation = _source.evaluate( l );
			constraints.push_back( evaluation );
			constraints.push_back( -evaluation );
			// (-1,1)
			l( i ) = -1;
			evaluation = _source.evaluate( l );
			constraints.push_back( evaluation );
			constraints.push_back( -evaluation );
			// (0,1)
			l( i ) = 0;
			evaluation = _source.evaluate( l );
			constraints.push_back( evaluation );
			constraints.push_back( -evaluation );
			l( j ) = 0;
		}
	}
	b.setOnes( constraints.size() );
	matrix_t<Number> constraintMatrix( constraints.size(), _source.dimension() );
	for ( std::size_t i = 0; i < constraints.size(); i++ ) {
		constraintMatrix.row( i ) = constraints.at( i );
	}
	return HPolytopeT<Number, Converter<Number>, HPolytopeSetting>( constraintMatrix, b );
}

//conversion from V-Polytope to H-Polytope (EXACT or OVER)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const VPolytopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE mode ) {
	if ( _source.empty() ) {
		return HPolytope::Empty();
	}

	HPolytope target;
	if ( mode == EXACT ) {
		target = HPolytope( _source.vertices() );
	} else if ( mode == OVER ) {
		//gets vertices from source object
		typename VPolytopeT<Number, Converter<Number>, inSetting>::pointVector vertices = _source.vertices();

		//computes an oriented Box as overapproximation around the source object (returns Halfspaces)
		PrincipalComponentAnalysis<Number> pca( vertices );
		std::vector<Halfspace<Number>> planes = pca.box();
		target = HPolytope( planes );
	}
	return target;
}

//conversion from Box to H-Polytope (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const BoxT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	return HPolytope( _source.matrix(), _source.vector() );
}

//conversion from zonotope to H-Polytope (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const ZonotopeT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE mode ) {
	//computes vertices from source object
	typename std::vector<Point<Number>> vertices = _source.vertices();
	if ( vertices.empty() ) {
		return HPolytopeT<Number, Converter<Number>, HPolytopeSetting>();
	}
	Converter<Number>::VPolytope vpoly = VPolytope( vertices );

	return toHPolytope( vpoly, mode );
}

// conversion from support function to H-Polytope (no differentiation between conversion modes - always OVER)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const SupportFunctionT<Number, Converter<Number>, inSetting>& _source, const std::vector<vector_t<Number>>& additionalDirections, const CONV_MODE, std::size_t numberOfDirections ) {
	std::size_t templateDirectionCnt = numberOfDirections;
	if ( inSetting::REDUCE_TO_BOX ) {
		templateDirectionCnt = 4;
	}
	//gets dimension of source object
	std::size_t dim = _source.dimension();

	std::vector<std::size_t> projections = _source.collectProjections();
	//std::cout << __func__ << ": collected " << projections.size() << " projections." << std::endl;
	if ( projections.size() == dim ) {
		//computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( dim, templateDirectionCnt );
		//only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
		assert( templateDirections.size() <= std::size_t( std::pow( templateDirectionCnt, dim ) ) );
		//creates a matrix with one row for each direction and one column for each dimension
		matrix_t<Number> templateDirectionMatrix = matrix_t<Number>( templateDirections.size() + additionalDirections.size(), dim );

		//fills the matrix with the template directions
		for ( unsigned i = 0; i < templateDirections.size(); ++i ) {
			templateDirectionMatrix.row( i ) = templateDirections[i];
		}
		std::size_t pos = 0;
		for ( Eigen::Index adIndex = Eigen::Index( templateDirections.size() ); adIndex < templateDirectionMatrix.rows(); ++adIndex ) {
			assert( additionalDirections.at( pos ).rows() == templateDirectionMatrix.cols() );
			templateDirectionMatrix.row( adIndex ) = additionalDirections.at( pos );
			++pos;
		}

		//lets the support function evaluate the offset of the halfspaces for each direction
		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate( templateDirectionMatrix, false );
		assert( offsets.size() == std::size_t( templateDirectionMatrix.rows() ) );

		std::vector<std::size_t> boundedConstraints;
		for ( unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex ) {
			//std::cout << "Result: " << offsets[offsetIndex] << std::endl;
			if ( offsets[offsetIndex].errorCode != SOLUTION::INFTY ) {
				boundedConstraints.push_back( offsetIndex );
			}
		}
		matrix_t<Number> constraints = matrix_t<Number>( boundedConstraints.size(), dim );
		vector_t<Number> constants = vector_t<Number>( boundedConstraints.size() );
		pos = boundedConstraints.size() - 1;
		while ( !boundedConstraints.empty() ) {
			constraints.row( pos ) = templateDirectionMatrix.row( boundedConstraints.back() );
			constants( pos ) = offsets[boundedConstraints.back()].supportValue;
			boundedConstraints.pop_back();
			--pos;
		}

		//constructs a H-Polytope out of the computed halfspaces
		return HPolytope( constraints, constants );

	} else {
		std::list<unsigned> zeroDimensions;
		for ( unsigned i = 0; i < dim; ++i ) {
			if ( std::find( projections.begin(), projections.end(), i ) == projections.end() ) {
				//std::cout << "Dimension " << i << " is zero." << std::endl;
				zeroDimensions.emplace_back( i );
			}
		}
		//std::cout << __func__ << ": compute template ... ";
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( projections, templateDirectionCnt, dim );
		//std::cout << "done." << std::endl;
		for ( auto direction : additionalDirections ) {
			// we assume that the additional direction, if it has the right number of rows, is already projected.
			if ( direction.rows() == Eigen::Index( dim ) ) {
				// project direction
				//std::cout << "project " << direction << std::endl;
				for ( const auto& dir : zeroDimensions ) {
					//std::cout << "set " << dir << " to zero" << std::endl;
					direction( dir ) = Number( 0 );
				}
			}
			// add projected direction
			if ( direction.nonZeros() > 0 && std::find( templateDirections.begin(), templateDirections.end(), direction ) == templateDirections.end() ) {
				templateDirections.emplace_back( std::move( direction ) );
			}
		}

		matrix_t<Number> templateDirectionMatrix = matrix_t<Number>( templateDirections.size(), dim );

		//fills the matrix with the template directions
		for ( unsigned i = 0; i < templateDirections.size(); ++i ) {
			templateDirectionMatrix.row( i ) = templateDirections[i];
		}
		//std::cout << __func__ << ": TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;

		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate( templateDirectionMatrix, false );
		assert( offsets.size() == unsigned( templateDirectionMatrix.rows() ) );

		//std::cout << "Multi-Eval done, reduce to relevant dimensions" << std::endl;

		std::size_t newDim = projections.size();
		matrix_t<Number> constraints = matrix_t<Number>( offsets.size(), newDim );
		vector_t<Number> constants = vector_t<Number>( offsets.size() );
		for ( unsigned rowIndex = 0; rowIndex < Eigen::Index( offsets.size() ); ++rowIndex ) {
			Eigen::Index colPos = 0;
			for ( auto projIt = projections.begin(); projIt != projections.end(); ++projIt, ++colPos ) {
				constraints( rowIndex, colPos ) = templateDirectionMatrix( rowIndex, ( *projIt ) );
			}
			constants( rowIndex ) = offsets.at( rowIndex ).supportValue;
		}

		//std::cout << "Construct polytope from constraints " << constraints << " and constants " << constants << std::endl;

		//constructs a H-Polytope out of the computed halfspaces
		return HPolytope( constraints, constants );
	}
}

// conversion from difference bounds to H-Polytope (no differentiation between conversion modes - always EXACT)
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const DifferenceBoundsT<Number, Converter<Number>, inSetting>& _source, const CONV_MODE ) {
	assert( _source.getDBM().rows() == _source.getDBM().cols() );
	Eigen::Index numclocks = _source.getDBM().cols() - 1;
	Eigen::Index numconstraints = 0;  //all entries of the DBM (except the diagonal and inifinities) define a constraint
	for ( Eigen::Index i = 0; i < _source.getDBM().rows(); i++ ) {
		for ( Eigen::Index j = 0; j < _source.getDBM().rows(); j++ ) {
			if ( i != j && !( _source.getDBM()( i, j ).second == DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::INFTY ) ) {
				numconstraints++;
			}
		}
	}
	//constraints of the polytope
	hypro::matrix_t<Number> HPolyConstraints = hypro::matrix_t<Number>::Zero( numconstraints, numclocks );
	hypro::vector_t<Number> HPolyConstants = hypro::vector_t<Number>::Zero( numconstraints );

	Eigen::Index counter = 0;  // counter for indexing constraints
	for ( Eigen::Index i = 0; i < _source.getDBM().rows(); i++ ) {
		for ( Eigen::Index j = 0; j < _source.getDBM().cols(); j++ ) {
			// do not consider diagonals
			if ( i != j && !( _source.getDBM()( i, j ).second == DifferenceBoundsT<Number, Converter<Number>, DifferenceBoundsSetting>::BOUND_TYPE::INFTY ) ) {
				// the constraint to add
				matrix_t<Number> constraintVars = matrix_t<Number>::Zero( 1, numclocks );
				if ( i == 0 ) {
					// constraint of the form 0-x_j <= c_ij
					constraintVars( 0, j - 1 ) = -1.0;	// j-1 because we don't consider static clock 0
				} else if ( j == 0 ) {
					// constraint of the form x_i - 0  <= c_ij
					constraintVars( 0, i - 1 ) = 1.0;  // i-1 because we don't consider static clock 0
				} else {
					// constraint of the form x_i - x_j  <= c_ij
					constraintVars( 0, i - 1 ) = 1.0;	// i-1 because we don't consider static clock 0
					constraintVars( 0, j - 1 ) = -1.0;	// j-1 because we don't consider static clock 0
				}
				HPolyConstraints.row( counter ) = constraintVars;
				HPolyConstants( counter, 0 ) = _source.getDBM()( i, j ).first;
				counter++;
			}
		}
	}
	return HPolytope( HPolyConstraints, HPolyConstants );
}

#ifdef HYPRO_USE_PPL
//Convert a ppl polytope into a HPolytope. Luckily, ppl polytopes have halfspaces internally.
template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE mode ) {
	if ( source.empty() ) {
		return HPolytope::Empty();
	}

	HPolytope target;
	if ( mode == EXACT ) {
		target = HPolytope( source.vertices() );
	} else if ( mode == OVER ) {
		//gets vertices from source object
		auto vertices = source.vertices();

		//computes an oriented Box as overapproximation around the source object (returns Halfspaces)
		PrincipalComponentAnalysis<Number> pca( vertices );
		std::vector<Halfspace<Number>> planes = pca.box();
		target = HPolytope( planes );
	}
	return target;
}
#endif

template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const CarlPolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE ) {
	return HPolytopeT<Number, Converter<Number>, HPolySetting>( source.getHalfspaces() );
}

template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const TemplatePolyhedronT<Number, Converter<Number>, inSetting>& source, const CONV_MODE ) {
	return HPolytopeT<Number, Converter<Number>, HPolySetting>( source.matrix(), source.vector() );
}

//template<typename Number>
//template<typename HPolySetting, typename inSetting>
//HPolytopeT<Number,Converter<Number>,HPolySetting> Converter<Number>::toHPolytope( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return HPolytopeT<Number,Converter<Number>,HPolySetting>();
//}

template <typename Number>
template <typename HPolySetting, typename inSetting>
HPolytopeT<Number, Converter<Number>, HPolySetting> Converter<Number>::toHPolytope( const SupportFunctionNewT<Number, Converter<Number>, inSetting>& _source, const std::vector<vector_t<Number>>& additionalDirections, const CONV_MODE, std::size_t numberOfDirections ) {
	//gets dimension of source object
	//assert(!_source.empty());
	std::size_t dim = _source.dimension();
	//std::cout << __func__ << ": Dimension of source: " << dim << std::endl;
	std::vector<std::size_t> projections = _source.collectProjections();
	//std::cout << __func__ << ": collected " << projections.size() << " projections." << std::endl;
	//std::cout << __func__ << ": numberOfDirections: " << numberOfDirections << std::endl;
	//std::cout << __func__ << ": additionalDirections: \n";
	if ( projections.size() == dim ) {
		//computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( dim, numberOfDirections );
		//only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
		assert( templateDirections.size() <= std::size_t( std::pow( numberOfDirections, dim ) ) );
		//creates a matrix with one row for each direction and one column for each dimension
		matrix_t<Number> templateDirectionMatrix = matrix_t<Number>( templateDirections.size() + additionalDirections.size(), dim );

		//fills the matrix with the template directions
		for ( unsigned i = 0; i < templateDirections.size(); ++i ) {
			templateDirectionMatrix.row( i ) = templateDirections[i];
		}
		std::size_t pos = 0;
		for ( Eigen::Index adIndex = Eigen::Index( templateDirections.size() ); adIndex < templateDirectionMatrix.rows(); ++adIndex ) {
			templateDirectionMatrix.row( adIndex ) = additionalDirections.at( pos );
			++pos;
		}
		//std::cout << "templateDirectionMatrix: \n" << templateDirectionMatrix << std::endl;

		//lets the support function evaluate the offset of the halfspaces for each direction
		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate( templateDirectionMatrix, false );
		assert( offsets.size() == std::size_t( templateDirectionMatrix.rows() ) );

		std::vector<std::size_t> boundedConstraints;
		for ( unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex ) {
			//std::cout << "Result: " << offsets[offsetIndex] << std::endl;
			if ( offsets[offsetIndex].errorCode != SOLUTION::INFTY ) {
				boundedConstraints.push_back( offsetIndex );
			}
		}
		matrix_t<Number> constraints = matrix_t<Number>( boundedConstraints.size(), dim );
		vector_t<Number> constants = vector_t<Number>( boundedConstraints.size() );
		pos = boundedConstraints.size() - 1;
		while ( !boundedConstraints.empty() ) {
			constraints.row( pos ) = templateDirectionMatrix.row( boundedConstraints.back() );
			constants( pos ) = offsets[boundedConstraints.back()].supportValue;
			boundedConstraints.pop_back();
			--pos;
		}
		//std::cout << "constraints: \n" << constraints << std::endl;
		//std::cout << "constants: \n" << constants << std::endl;

		//constructs a H-Polytope out of the computed halfspaces
		return HPolytope( constraints, constants );

	} else {
		//std::cout << __func__ << "Projection" << std::endl;
		//for(auto dim : projections) {
		//	std::cout << "projection dimension " << dim << std::endl;
		//}
		std::list<unsigned> zeroDimensions;
		for ( unsigned i = 0; i < dim; ++i ) {
			if ( std::find( projections.begin(), projections.end(), i ) == projections.end() ) {
				//std::cout << "Dimension " << i << " is zero." << std::endl;
				zeroDimensions.emplace_back( i );
			}
		}
		//std::cout << __func__ << ": compute template ... " << std::endl;
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( projections, numberOfDirections, dim );	 // TODO: ATTENTION, 8 is hardcoded here.
		//std::cout << "done." << std::endl;
		for ( auto direction : additionalDirections ) {
			// project direction
			for ( const auto& dir : zeroDimensions ) {
				direction( dir ) = Number( 0 );
			}
			// add projected direction
			if ( direction.nonZeros() > 0 && std::find( templateDirections.begin(), templateDirections.end(), direction ) == templateDirections.end() ) {
				templateDirections.emplace_back( std::move( direction ) );
			}
		}

		matrix_t<Number> templateDirectionMatrix = matrix_t<Number>( templateDirections.size(), dim );

		//fills the matrix with the template directions
		for ( unsigned i = 0; i < templateDirections.size(); ++i ) {
			templateDirectionMatrix.row( i ) = templateDirections[i];
		}
		//std::cout << "TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;
		std::size_t pos = 0;
		for ( Eigen::Index adIndex = Eigen::Index( templateDirections.size() ); adIndex < templateDirectionMatrix.rows(); ++adIndex ) {
			templateDirectionMatrix.row( adIndex ) = additionalDirections.at( pos );
			++pos;
		}
		//std::cout << __func__ << ": TemplateDirectionMatrix: " << std::endl << templateDirectionMatrix << std::endl;

		std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate( templateDirectionMatrix, false );
		assert( offsets.size() == unsigned( templateDirectionMatrix.rows() ) );

		//std::cout << "Multi-Eval done, reduce to relevant dimensions" << std::endl;

		std::size_t newDim = projections.size();
		matrix_t<Number> constraints = matrix_t<Number>( offsets.size(), newDim );
		vector_t<Number> constants = vector_t<Number>( offsets.size() );
		for ( unsigned rowIndex = 0; rowIndex < Eigen::Index( offsets.size() ); ++rowIndex ) {
			Eigen::Index colPos = 0;
			for ( auto projIt = projections.begin(); projIt != projections.end(); ++projIt, ++colPos ) {
				constraints( rowIndex, colPos ) = templateDirectionMatrix( rowIndex, ( *projIt ) );
			}
			constants( rowIndex ) = offsets.at( rowIndex ).supportValue;
		}

		//std::cout << "Construct polytope from constraints " << constraints << " and constants " << constants << std::endl;

		//constructs a H-Polytope out of the computed halfspaces
		return HPolytope( constraints, constants );
	}
}

template<typename Number>
template<typename HPolytopeSetting, typename inSetting>
HPolytopeT<Number,Converter<Number>,HPolytopeSetting> Converter<Number>::toHPolytope( const StarsetT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
	//std::cout<<"wtf"<<std::endl;
	if(source.generator()==(matrix_t<Number>::Identity(source.generator().cols(),source.generator().cols()))){
		return source.constraintss();
	}
	//HPolytopeT<Number,Converter<Number>,HPolytopeSetting> temp=source.constraintss();
	VPolytopeT<Number,Converter<Number>,VPolytopeSetting> temp2= Converter::toVPolytope(source.constraintss());
	auto temp3=HPolytopeT<Number,Converter<Number>,HPolytopeSetting>(temp2.affineTransformation(source.generator(),source.center()).vertices());
	//std::cout<<"TOhpoly"<<temp3.matrix()<<std::endl;
	return temp3;
	std::cout<<"wtf"<<std::endl;
	return source.constraintss().affineTransformation(source.generator(),source.center());
}
}  // namespace hypro

