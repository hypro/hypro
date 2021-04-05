#pragma once
#include "../../../types.h"
#include "linear.h"

#include <iosfwd>

namespace hypro {

template <typename Number>
class affineFlow : public linearFlow<Number> {
  public:
  protected:
	vector_t<Number> mTranslation;
	mutable TRIBOOL mIsNoTranslation = TRIBOOL::NSET;

  public:
	affineFlow() = default;
	affineFlow( const affineFlow<Number>& in ) = default;
	affineFlow( const matrix_t<Number>& A, const vector_t<Number>& b )
		: linearFlow<Number>( A )
		, mTranslation( b ) {}

	virtual ~affineFlow() {}

	static DynamicType type() { return DynamicType::affine; }
	std::size_t dimension() const { return linearFlow<Number>::dimension(); }

	void setTranslation( const vector_t<Number>& newB ) {
		mTranslation = newB;
		mIsNoTranslation = TRIBOOL::NSET;
	}
	const vector_t<Number>& getTranslation() const { return mTranslation; }

	DynamicType getDynamicsType() const {
		if ( dimension() == 0 || mTranslation == vector_t<Number>::Zero( dimension() ) ) {
			return linearFlow<Number>::getDynamicsType();
		}
		return DynamicType::affine;
	}

	bool hasTranslation() const {
		if ( mIsNoTranslation == TRIBOOL::NSET ) {
			if ( mTranslation.rows() == 0 ) {
				mIsNoTranslation = TRIBOOL::FALSE;
				return false;
			} else {
				mIsNoTranslation = mTranslation == vector_t<Number>::Zero( mTranslation.rows() ) ? TRIBOOL::TRUE : TRIBOOL::FALSE;
			}
		}
		return mIsNoTranslation == TRIBOOL::FALSE;
	}

	bool isTimed() const {
		TRACE( "hypro.decisionEntity", "Flowmatrix: " << linearFlow<Number>::getFlowMatrix() );
		if ( linearFlow<Number>::isTimed() ) {
			// TODO: we need to remove distinguishing of linear and affine flow.
			return true;
		}
		return linearFlow<Number>::hasNoFlow() && mTranslation == vector_t<Number>::Ones( mTranslation.rows() );
	}

	bool isDiscrete() const {
		return linearFlow<Number>::hasNoFlow() && !hasTranslation();
	}

	friend bool operator==( const affineFlow<Number>& lhs, const affineFlow<Number>& rhs ) {
		return ( lhs.getFlowMatrix() == rhs.getFlowMatrix() && lhs.getTranslation() == rhs.getTranslation() );
	}

	friend bool operator!=( const affineFlow<Number>& lhs, const affineFlow<Number>& rhs ) {
		return !( lhs == rhs );
	}

	friend std::ostream& operator<<( std::ostream& out, const affineFlow<Number>& in ) {
		bool firstRow = true;
		// assemble flow matrix
		matrix_t<Number> fMat = matrix_t<Number>( in.mFlowMatrix.rows(), in.mFlowMatrix.cols() + 1 );
		fMat.block( 0, 0, in.mFlowMatrix.rows(), in.mFlowMatrix.cols() ) = in.mFlowMatrix;
		fMat.col( fMat.cols() - 1 ) = in.mTranslation;
		if ( fMat.rows() > 0 ) {
			for ( Eigen::Index row = 0; row < fMat.rows(); ++row ) {
				if ( !firstRow ) {
					out << "\n";
				} else {
					firstRow = false;
				}
				out << "x" << row << "' = " << to_string<Number>( fMat.row( row ) );
			}
		}
		return out;
	}
};

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::affineFlow<Number>> {
	std::size_t operator()( const hypro::affineFlow<Number>& f ) const {
		std::size_t seed = 0;
		carl::hash_add( seed, std::hash<hypro::linearFlow<Number>>()( hypro::linearFlow<Number>( f ) ) );
		carl::hash_add( seed, std::hash<hypro::vector_t<Number>>()( f.getTranslation() ) );
		return seed;
	}
};

}  // namespace std
