#pragma once
#include "../../datastructures/Point.h"
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"
#include "../../types.h"

namespace hypro {

template <typename T>
class genericUniteVisitor {
  public:
	template <typename A, typename B>
	inline T operator()( const A& lhs, const B& ) const {
		assert( false && "UNION OF DIFFERENT TYPES." );
		return lhs;
	}

	template <typename A>
	inline T operator()( const A& lhs, const A& rhs ) const {
		//auto tmpHPoly = Converter<Number>::toHPolytope(lhs);
		//TRACE("hydra.datastructures","Union visitor lhs " << tmpHPoly);
		//tmpHPoly = Converter<Number>::toHPolytope(rhs);
		//TRACE("hydra.datastructures","Union visitor rhs " << tmpHPoly);
		return lhs.unite( rhs );
	}
};

template <typename T>
class genericMinkowskiSumVisitor {
  public:
	template <typename A, typename B>
	inline T operator()( const A& lhs, const B& ) const {
		TRACE( "hypro.utility", "Type lhs: " << A::type() << " and type rhs: " << B::type() );
		assert( false && "MinkowskiSum OF DIFFERENT TYPES" );
		return lhs;
	}

	template <template <typename, typename, typename> typename A, typename S1, typename S2, typename N, typename C>
	inline T operator()( const A<N, C, S1>& lhs, const A<N, C, S2>& rhs ) const {
		A<N, C, S1> tmp{rhs};
		return lhs.minkowskiSum( tmp );
	}
};

template <typename T>
class genericIntersectVisitor {
  public:
	template <typename A>
	inline T operator()( const A& lhs, const A& rhs ) const {
		return lhs.intersect( rhs );
	}
	
	template <typename A, typename B>
	inline T operator()( const A& lhs, const B& ) const {
		assert( false && "INTERSECTION OF DIFFERENT TYPES." );
		return lhs;
	}
};

template <typename T, typename Number>
class genericAffineTransformationVisitor {
  protected:
	const matrix_t<Number>& mat;
	const vector_t<Number>& vec;

  public:
	genericAffineTransformationVisitor() = delete;
	genericAffineTransformationVisitor( const matrix_t<Number>& m, const vector_t<Number>& v )
		: mat( m )
		, vec( v ) {}

	template <typename B>
	inline T operator()( const B& lhs ) const {
		assert( Eigen::Index( lhs.dimension() ) == mat.rows() );
		assert( Eigen::Index( lhs.dimension() ) == vec.rows() );
		return lhs.affineTransformation( mat, vec );
	}
};

template <typename T, typename To>
class genericConversionVisitor {
  public:
	template <typename B>
	inline T operator()( const B& lhs ) const {
		To tmp;
		convert<typename To::NumberType, typename To::Settings, B>( lhs, tmp );
		return tmp;
	}
};

template <typename T, typename Ext>
class genericInternalConversionVisitor {
  protected:
	Ext mExt;

  public:
	genericInternalConversionVisitor() = delete;
	genericInternalConversionVisitor( const Ext& in )
		: mExt( in ) {}

	template <typename B>
	inline T operator()( const B& ) const {
		B tmp;
		convert<typename B::NumberType, typename B::Settings, Ext>( mExt, tmp );
		return tmp;
	}
};

template <typename OutType>
class genericConvertAndGetVisitor {
  protected:
  public:
	template <typename B>
	inline OutType operator()( const B& in ) const {
		OutType tmp;
		convert<typename OutType::NumberType, typename OutType::Settings, B>( in, tmp );
		return tmp;
	}
};

template <typename T, typename Number>
class genericRedundancyVisitor {
  public:
	template <typename A>
	inline T operator()( A lhs ) const {
		lhs.removeRedundancy();
		return lhs;
	}
};

template <typename T, typename Number>
class genericReductionVisitor {
  public:
	template <typename A>
	inline T operator()( A lhs ) const {
		lhs.reduceRepresentation();
		return lhs;
	}
};

template <typename T, typename Number>
class genericSatisfiesHalfspacesVisitor {
  protected:
	const matrix_t<Number>& constraints;
	const vector_t<Number>& constants;

  public:
	genericSatisfiesHalfspacesVisitor() = delete;
	genericSatisfiesHalfspacesVisitor( const matrix_t<Number>& m, const vector_t<Number>& v )
		: constraints( m )
		, constants( v ) {}

	template <typename B>
	inline std::pair<CONTAINMENT, T> operator()( const B& lhs ) const {
		return lhs.satisfiesHalfspaces( constraints, constants );
	}
};

class genericCompareVisitor {
  public:
	template <typename A, typename B>
	inline bool operator()( const A&, const B& ) const {
		return false;
	}

	template <typename T>
	inline bool operator()( const T& lhs, const T& rhs ) const {
		return ( lhs == rhs );
	}
};

class genericOutstreamVisitor {
  protected:
	std::ostream& out;

  public:
	genericOutstreamVisitor() = delete;
	genericOutstreamVisitor( std::ostream& o )
		: out( o ) {}

	template <typename T>
	inline std::ostream& operator()( const T& shape ) const {
		return out << shape;
	}
};

class genericDimensionVisitor {
  public:
	template <typename T>
	inline std::size_t operator()( const T& shape ) const {
		return shape.dimension();
	}
};

template <typename T>
class genericSupremumVisitor {
  public:
	template <typename A>
	inline T operator()( const A& shape ) const {
		return shape.supremum();
	}
};

class genericTypeVisitor {
  public:
	template <typename A>
	inline representation_name operator()( const A& ) const {
		return A::type();
	}
};

class genericSettingVisitor {
  public:
	template <typename A>
	inline A::Settings operator()( const A& ) const {
		return A::Settings();
	}
};

template <typename Number>
class genericVerticesVisitor {
  public:
	template <typename B>
	inline std::vector<Point<Number>> operator()( const B& lhs ) const {
		return lhs.vertices();
	}
};

template <typename T>
class genericProjectionVisitor {
  protected:
	std::vector<std::size_t> mDimensions;

  public:
	genericProjectionVisitor() = delete;
	genericProjectionVisitor( const std::vector<std::size_t>& dim )
		: mDimensions( dim ) {}

	template <typename A>
	inline T operator()( const A& lhs ) const {
		return lhs.project( mDimensions );
	}
};

class genericSetContainsVisitor {
  public:
	template <typename A, typename B>
	inline bool operator()( const A&, const B& ) const {
		assert( false && "CONTAINS CHECK OF DIFFERENT TYPES." );
		return false;
	}

	template <typename A>
	inline bool operator()( const A& lhs, const A& rhs ) const {
		return lhs.contains( rhs );
	}
};

template <typename T, typename Number>
class genericIntervalAssignmentVisitor {
	const std::vector<carl::Interval<Number>>& mAssignments;

  public:
	genericIntervalAssignmentVisitor() = delete;
	genericIntervalAssignmentVisitor( const std::vector<carl::Interval<Number>>& assignments )
		: mAssignments( assignments ) {}

	// TODO: Add SFINAE mechanism to ensure N=Number
	template <typename N, typename C, typename S>
	inline T operator()( const CarlPolytopeT<N, C, S>& lhs ) const {
		DEBUG( "hypro.datastructures", "Interval assignment." );
		assert( mAssignments.size() >= lhs.dimension() );
		auto res{lhs};
		for ( std::size_t i = 0; i < mAssignments.size(); ++i ) {
			// the empty interval is used to encode identity resets.
			if ( !mAssignments[i].isEmpty() ) {
				assert( VariablePool::getInstance().hasDimension( i ) );
				TRACE( "hypro.datastructures", "Assign " << mAssignments[i] << " to variable " << VariablePool::getInstance().carlVarByIndex( i ) );
				res.eliminateVariable( VariablePool::getInstance().carlVarByIndex( i ) );
				res.addIntervalConstraints( mAssignments[i], VariablePool::getInstance().carlVarByIndex( i ) );
			}
		}
		DEBUG( "hypro.datastructures", "Result: " << res );
		return res;
	}

	template <typename B>
	inline T operator()( const B& lhs ) const {
		DEBUG( "hypro.datastructures", "INTERVAL ASSIGNMENT NOT IMPLEMENTED FOR THIS TYPE." );
		std::cout << "Interval assignment not implemented for this type." << std::endl;
		return lhs;
	}
};

class genericToStringVisitor {
  public:
	template <typename A>
	inline std::string operator()( const A& in ) const {
		std::stringstream ss;
		ss << in;
		return ss.str();
	}
};

}  // namespace hypro
