#pragma once
#include "../../../types.h"
#include "../../../util/convenienceOperators.h"

namespace hypro {

template <typename Number>
class linearFlow {
  public:
  protected:
	matrix_t<Number> mFlowMatrix = matrix_t<Number>( 0, 0 );
	mutable TRIBOOL mIsIdentity = TRIBOOL::NSET;
	mutable TRIBOOL mNoFlow = TRIBOOL::NSET;

  public:
	linearFlow() = default;
	linearFlow( const linearFlow& in ) = default;
	linearFlow( const matrix_t<Number>& A )
		: mFlowMatrix( A ) {}
	virtual ~linearFlow() {}

	static DynamicType type() { return DynamicType::linear; }
	std::size_t dimension() const { return mFlowMatrix.cols() - 1; }
	std::size_t size() const { return mFlowMatrix.rows(); }

	void setFlowMatrix( const matrix_t<Number>& newA ) {
		mFlowMatrix = newA;
		mIsIdentity = TRIBOOL::NSET;
		mNoFlow = TRIBOOL::NSET;
	}

	void addRow( const vector_t<Number>& row ) {
		// std::cout << "try to add row " << row << std::endl;
		assert( mFlowMatrix.rows() == 0 || row.rows() == mFlowMatrix.cols() );
		if ( mFlowMatrix.rows() == 0 ) {
			mFlowMatrix = matrix_t<Number>( 1, row.rows() );
			mFlowMatrix.row( 0 ) = row;
		} else {
			mFlowMatrix.conservativeResize( mFlowMatrix.rows() + 1, mFlowMatrix.cols() );
			mFlowMatrix.row( mFlowMatrix.rows() - 1 ) = row;
		}
	}

	const matrix_t<Number>& getFlowMatrix() const { return mFlowMatrix; }
	matrix_t<Number>& rGetFlowMatrix() { return mFlowMatrix; }

	bool isIdentity() const {
		if ( mIsIdentity == TRIBOOL::NSET ) {
			if ( mFlowMatrix.rows() == 0 ) {
				mIsIdentity = TRIBOOL::FALSE;
				mNoFlow = TRIBOOL::FALSE;
				return false;
			} else {
				mIsIdentity = mFlowMatrix == matrix_t<Number>::Identity( mFlowMatrix.rows(), mFlowMatrix.cols() ) ? TRIBOOL::TRUE : TRIBOOL::FALSE;
				if ( mIsIdentity == TRIBOOL::TRUE ) {
					mNoFlow = TRIBOOL::FALSE;
				}
			}
		}
		return mIsIdentity == TRIBOOL::TRUE;
	}

	bool hasNoFlow() const {
		if ( mNoFlow == TRIBOOL::NSET ) {
			if ( mFlowMatrix.rows() == 0 ) {
				mNoFlow = TRIBOOL::FALSE;
				mIsIdentity = TRIBOOL::FALSE;
				return false;
			} else {
				mNoFlow = mFlowMatrix == matrix_t<Number>::Zero( mFlowMatrix.rows(), mFlowMatrix.cols() ) ? TRIBOOL::TRUE : TRIBOOL::FALSE;
				if ( mNoFlow == TRIBOOL::TRUE ) {
					mIsIdentity = TRIBOOL::FALSE;
				}
			}
		}
		return mNoFlow == TRIBOOL::TRUE;
	}

	bool hasNoFlow( std::size_t varIndex ) const {
		assert( Eigen::Index( varIndex ) < mFlowMatrix.rows() );
		return mFlowMatrix.row( varIndex ).isZero();
	}

	std::vector<std::size_t> getNonDiscreteDimensions() const {
		std::vector<std::size_t> result;
		for ( std::size_t d = 0; d < this->dimension(); ++d ) {
			if ( !hasNoFlow( d ) ) {
				result.push_back( d );
			}
		}
		return result;
	}

	bool hasFlow( std::size_t varIndex ) const {
		return !hasNoFlow( varIndex );
	}

	DynamicType getDynamicsType() const {
		if ( isTimed() ) {
			return DynamicType::timed;
		}
		if ( isDiscrete() ) {
			return DynamicType::discrete;
		}
		if ( isSingular() ) {
			return DynamicType::singular;
		}
		return DynamicType::linear;
	}

	DynamicType getDynamicsType( std::size_t varIndex ) const {
		if ( isTimed( varIndex ) ) {
			return DynamicType::timed;
		}
		if ( isDiscrete( varIndex ) ) {
			return DynamicType::discrete;
		}
		if ( isSingular( varIndex ) ) {
			return DynamicType::singular;
		}
		return DynamicType::linear;
	}

	bool isTimed() const {
		TRACE( "hypro.decisionEntity", "Flowmatrix: " << mFlowMatrix );
		Eigen::Index rows = mFlowMatrix.rows();
		if ( mFlowMatrix.block( 0, 0, rows - 1, rows - 1 ) == matrix_t<Number>::Zero( rows - 1, rows - 1 ) ) {
			if ( mFlowMatrix.block( 0, rows - 1, rows - 1, 1 ) == vector_t<Number>::Ones( rows - 1 ) ) {
				return true;
			}
		}
		return false;
	}

	bool isTimed( std::size_t varIndex ) const {
		Eigen::Index rows = mFlowMatrix.rows();
		if ( mFlowMatrix.block( varIndex, 0, 1, rows - 1 ) == matrix_t<Number>::Zero( 1, rows - 1 ) ) {
			if ( mFlowMatrix( varIndex, rows - 1 ) == 1 ) {
				return true;
			}
		}
		return false;
	}

	bool isSingular() const {
		TRACE( "hypro.decisionEntity", "Flowmatrix: " << mFlowMatrix );
		Eigen::Index rows = mFlowMatrix.rows();
		if ( mFlowMatrix.block( 0, 0, rows - 1, rows - 1 ) == matrix_t<Number>::Zero( rows - 1, rows - 1 ) ) {
			return true;
		}
		return false;
	}

	bool isSingular( std::size_t varIndex ) const {
		TRACE( "hypro.decisionEntity", "Flowmatrix: " << mFlowMatrix );
		Eigen::Index rows = mFlowMatrix.rows();
		if ( mFlowMatrix.block( varIndex, 0, 1, rows - 1 ) == matrix_t<Number>::Zero( 1, rows - 1 ) ) {
			return true;
		}
		return false;
	}

	bool isDiscrete() const {
		return hasNoFlow();
	}

	bool isDiscrete( std::size_t varIndex ) const {
		return hasNoFlow( varIndex );
	}

	friend bool operator==( const linearFlow<Number>& lhs, const linearFlow<Number>& rhs ) {
		return lhs.getFlowMatrix() == rhs.getFlowMatrix();
	}

	friend bool operator!=( const linearFlow<Number>& lhs, const linearFlow<Number>& rhs ) {
		return !( lhs == rhs );
	}

	friend std::ostream& operator<<( std::ostream& out, const linearFlow<Number>& in ) {
		bool firstRow = true;
		const matrix_t<Number>& fMat{ in.mFlowMatrix };
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

};	// namespace hypro

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::linearFlow<Number>> {
	std::size_t operator()( const hypro::linearFlow<Number>& f ) const {
		std::size_t seed = 0;
		carl::hash_add( seed, std::hash<hypro::matrix_t<Number>>()( f.getFlowMatrix() ) );
		return seed;
	}
};

}  // namespace std
