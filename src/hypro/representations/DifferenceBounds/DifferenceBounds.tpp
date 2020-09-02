#include "DifferenceBounds.h"

namespace hypro {

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting>::DifferenceBoundsT() {
	m_dbm = matrix_t<DBMEntry>( 1, 1 );
	m_dbm << DBMEntry( 0, DifferenceBoundsT<Number, Converter, Setting>::BOUND_TYPE::SMALLER );
	m_timeHorizon = 0.0;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting>::DifferenceBoundsT( matrix_t<Number> matrix, vector_t<Number> vector ) {
	typename Converter::ConstraintSet cSet( matrix, vector );
	DifferenceBoundsT<Number, Converter, Setting> dbm = Converter::toDifferenceBounds( cSet );
	m_dbm = dbm.getDBM();
	m_timeHorizon = 0.0;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting>::DBMEntry::DBMEntry( Number number, BOUND_TYPE boundType )
	: std::pair<Number, BOUND_TYPE>( number, boundType ) {
	//nop
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting>::DBMEntry::DBMEntry()
	: std::pair<Number, BOUND_TYPE>() {
	//nop
}

template <typename Number, typename Converter, class Setting>
matrix_t<typename DifferenceBoundsT<Number, Converter, Setting>::DBMEntry> DifferenceBoundsT<Number, Converter, Setting>::getDBM() const {
	return m_dbm;
}
template <typename Number, typename Converter, class Setting>
void DifferenceBoundsT<Number, Converter, Setting>::setDBM( matrix_t<DifferenceBoundsT<Number, Converter, Setting>::DBMEntry> dbm ) {
	m_dbm = dbm;
}

template <typename Number, typename Converter, class Setting>
Number DifferenceBoundsT<Number, Converter, Setting>::getTimeHorizon() const {
	return m_timeHorizon;
}

template <typename Number, typename Converter, class Setting>
void DifferenceBoundsT<Number, Converter, Setting>::setTimeHorizon( Number horizon ) {
	m_timeHorizon = horizon;
}

template <typename Number, typename Converter, class Setting>
carl::Interval<tNumber> DifferenceBoundsT<Number, Converter, Setting>::getCoveredTimeInterval() const {
	carl::Interval<tNumber> res{ 0, 0 };
	auto box = Converter::toBox( *this );
	auto intervals = box.getIntervals();
	for ( const auto& i : intervals ) {
		if ( i.diameter() > res.diameter() ) {
			res = i;
		}
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
std::size_t DifferenceBoundsT<Number, Converter, Setting>::dimension() const {
	// number of clocks
	return this->getDBM().cols() - 1;
}

template <typename Number, typename Converter, class Setting>
std::size_t DifferenceBoundsT<Number, Converter, Setting>::size() const {
	// number of dbm entries
	return this->getDBM().cols() * this->getDBM().rows();
}

template <typename Number, typename Converter, class Setting>
bool DifferenceBoundsT<Number, Converter, Setting>::empty() const {
	/*
         *  It suffices to traverse the lower half of the dbm matrix
         *  (i.e. where i is larger than j) to check emptiness.
         *
         *  Further, we can abuse the entry d_00 to keep track of an invalid dbm by
         *  assigning it -1.
         *
         *  This will for one avoid double checking emptiness and secondly if we
         *  recognize during transformation that the resulting dbm will be
         *  empty we can directly invalidate the dbm by setting d00 = -1 and thus
         *  save future emptiness checks.
         *
         */
	if ( m_dbm( 0, 0 ).first == -1.0 ) {
		// d_00 is -1 so we already found out that the dbm is empty
		return true;
	}
	// we assume that the dbm is non empty
	for ( int i = 1; i < m_dbm.rows(); i++ ) {
		// lower half (i > j)
		for ( int j = 0; j < i; j++ ) {
			// if straight upper bound
			if ( j == 0 ) {
				if ( m_dbm( i, j ) < DBMEntry( -m_dbm( j, i ).first, m_dbm( j, i ).second ) ) {	 // Note: I've changed to -m_dbm(j,i).
																								 //std::cout << i << ", "<< j << ": 0-Clock entry." << std::endl;
					m_dbm( 0, 0 ).first = -1.0;
					return true;
				}
			} else {
				//diagonal bound
				if ( m_dbm( i, j ) < DBMEntry( -m_dbm( j, i ).first, m_dbm( j, i ).second ) ) {	 // Note: I've changed to -m_dbm(j,i).
																								 //std::cout << i << ", "<< j << ": regular entry." << std::endl;
					m_dbm( 0, 0 ).first = -1.0;
					return true;
				}
			}
		}
	}
	return false;
}

//TODO
template <typename Number, typename Converter, class Setting>
EvaluationResult<Number> DifferenceBoundsT<Number, Converter, Setting>::evaluate( const vector_t<Number>&, bool ) const {
	assert( "Evaluate not implemented for DifferenceBounds." && false );
	return EvaluationResult<Number>();
}

//TODO
template <typename Number, typename Converter, class Setting>
std::vector<EvaluationResult<Number>> DifferenceBoundsT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>&, bool ) const {
	assert( "multiEvaluate not implemented for DifferenceBounds." && false );
	return std::vector<EvaluationResult<Number>>();
}

template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> DifferenceBoundsT<Number, Converter, Setting>::vertices( const matrix_t<Number>& ) const {
	auto poly = Converter::toHPolytope( *this );
	// A time Horizon can be defined that avoids plotting of potentially infinite polytopes
	if ( getTimeHorizon() != 0.0 ) {
		// we need 2 additional timeHorizon constraint for each clock (except 0 clock)
		int numclocks = getDBM().cols() - 1;
		//constraints of the polytope
		hypro::matrix_t<Number> HPolyConstraints = poly.matrix();
		hypro::vector_t<Number> HPolyConstants = poly.vector();
		int numconstraints = HPolyConstraints.rows();
		HPolyConstraints.conservativeResize( numconstraints + 2 * numclocks, HPolyConstraints.cols() );
		//HPolyConstants.conservativeResize(numconstraints+2*numclocks, HPolyConstraints.cols());
		HPolyConstants.conservativeResize( numconstraints + 2 * numclocks );

		int counter = numconstraints;  //start at next row
		for ( int i = 0; i < numclocks; i++ ) {
			// for each clock add a timehorizon so the polytope to plot is finite in plus direction
			matrix_t<Number> constraintVars = matrix_t<Number>::Zero( 1, numclocks );
			constraintVars( 0, i ) = 1.0;
			HPolyConstraints.row( counter ) = constraintVars;
			HPolyConstants( counter, 0 ) = getTimeHorizon();
			counter++;
			// for each clock add a greater than 0 constraint so the polytope to plot is finity in
			// in negative direction
			matrix_t<Number> constraintVars2 = matrix_t<Number>::Zero( 1, numclocks );
			constraintVars2( 0, i ) = -1.0;
			HPolyConstraints.row( counter ) = constraintVars2;
			HPolyConstants( counter, 0 ) = 0.0;
			counter++;
		}

		//assert( false );
		FATAL( "hypro", "Not implemented." );

		//auto polyNew( HPolyConstraints, HPolyConstants );
		//return polyNew.vertices();
		return poly.vertices();	 // TODO: this is to avoid warnings.
	}
	return poly.vertices();
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter, Setting>> DifferenceBoundsT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	auto tmp = Converter::toHPolytope( *this );
	auto res = tmp.satisfiesHalfspace( rhs );
	return std::make_pair( res.first, Converter::toDifferenceBounds( res.second ) );
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter, Setting>> DifferenceBoundsT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	auto tmp = Converter::toHPolytope( *this );
	auto res = tmp.satisfiesHalfspaces( _mat, _vec );
	return std::make_pair( res.first, Converter::toDifferenceBounds( res.second ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	if ( (unsigned)dimensions.size() + 1 == m_dbm.rows() ) {
		// if the dimensions to plot to are as large as our dbm, we are already done
		return hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	}
	// TODO can this be done better? especially for higher dimensions?
	// YES! Read the values from the DBM directly!!!
	auto tmp = Converter::toHPolytope( *this );
	auto projected = tmp.projectOn( dimensions );
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = Converter::toDifferenceBounds( projected );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	auto tmp = Converter::toHPolytope( *this );
	return Converter::toDifferenceBounds( tmp.linearTransformation( A ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	auto tmp = Converter::toHPolytope( *this );
	return Converter::toDifferenceBounds( tmp.affineTransformation( A, b ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::minkowskiSum( const DifferenceBoundsT<Number, Converter, Setting>& _rhs ) const {
	auto tmp1 = Converter::toHPolytope( *this );
	auto tmp2 = Converter::toHPolytope( _rhs );
	return Converter::toDifferenceBounds( tmp1.minkowskiSum( tmp2 ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::intersect( const DifferenceBoundsT<Number, Converter, Setting>& _rhs ) const {
	hypro::DifferenceBoundsT<Number, Converter, Setting> retDBM = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	// for each entry in the other dbm, intersect that entry with this dbm
	for ( int i = 0; i < _rhs.getDBM().rows(); i++ ) {
		for ( int j = 0; j < _rhs.getDBM().cols(); j++ ) {
			if ( i != j ) {
				retDBM = retDBM.intersectConstraint( i, j, _rhs.getDBM()( i, j ) );
			}
		}
	}
	return retDBM;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hs ) const {
	auto tmp = Converter::toHPolytope( *this );
	return Converter::toDifferenceBounds( tmp.intersectHalfspace( hs ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	auto tmp = Converter::toHPolytope( *this );
	return Converter::toDifferenceBounds( tmp.intersectHalfspaces( _mat, _vec ) );
}

template <typename Number, typename Converter, class Setting>
bool DifferenceBoundsT<Number, Converter, Setting>::contains( const Point<Number>& _point ) const {
	// describe point as dbm
	vector_t<Number> coordinates = _point.rawCoordinates();
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm.rows(), m_dbm.cols() );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i == j ) {
				// diagonals are zero
				mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ );
			} else if ( i == 0 ) {
				// constraint of the form 0-x_j-1<=b <=> x_j-1 >=-b
				mat( i, j ) = DBMEntry( -1.0 * coordinates( j - 1 ), BOUND_TYPE::SMALLER_EQ );
			} else if ( j == 0 ) {
				// constraint of the form x_i-1-0 <= b
				mat( i, j ) = DBMEntry( coordinates( i - 1 ), BOUND_TYPE::SMALLER_EQ );
			} else {
				// constaint of the form x_i-1-x_j-1<=b
				mat( i, j ) = DBMEntry( coordinates( i - 1 ) - coordinates( j - 1 ), BOUND_TYPE::SMALLER_EQ );
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> pDBM = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	pDBM.setDBM( mat );
	return this->contains( pDBM );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::unite( const DifferenceBoundsT<Number, Converter, Setting>& _rhs ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i != j ) {
				mat( i, j ) = DBMEntry::max( mat( i, j ), _rhs.getDBM()( i, j ) );
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res; /*
        auto left = Converter::toHPolytope(*this);
        auto right = Converter::toHPolytope(_rhs);
        return Converter::toDifferenceBounds(left.unite(right));*/
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::elapse() const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 1; i < m_dbm.rows(); i++ ) {
		mat( i, 0 ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::rewind() const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 1; i < m_dbm.rows(); i++ ) {
		mat( 0, i ) = DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ );
		for ( int j = 1; j < m_dbm.rows(); j++ ) {
			// if the diagonal intersects the clock axis later than 0, it is tighter than the 0 constraint
			if ( m_dbm( j, i ) < m_dbm( 0, i ) ) {
				mat( 0, i ) = DBMEntry( m_dbm( j, i ).first, m_dbm( j, i ).second );
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::free( int x ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < m_dbm.rows(); i++ ) {
		if ( i != x ) {
			// d_xi = inf
			mat( x, i ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );

			// d_ix = d_i0
			mat( i, x ) = DBMEntry( m_dbm( i, 0 ).first, m_dbm( i, 0 ).second );
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::reset( int x, Number value ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < m_dbm.rows(); i++ ) {
		if ( i != x ) {	 //don't touch diagonals
			// d_xi = (value,<=)+d_0i
			mat( x, i ) = DBMEntry( value, BOUND_TYPE::SMALLER_EQ ) + m_dbm( 0, i );

			// d_ix = d_i0 + (-value, <=)
			mat( i, x ) = m_dbm( i, 0 ) + DBMEntry( ( -value ) + 0.0, BOUND_TYPE::SMALLER_EQ );
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::copy( int src, int dest ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < m_dbm.rows(); i++ ) {
		if ( i != dest ) {
			// d_desti = d_srci
			mat( dest, i ) = DBMEntry( m_dbm( src, i ).first, m_dbm( src, i ).second );
			// d_idest = d_isrc
			mat( i, dest ) = DBMEntry( m_dbm( i, src ).first, m_dbm( i, src ).second );
		}
	}
	// d_destsrc = (0,<=)
	mat( dest, src ) = DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ );
	// d_srcdest = (0,<=)
	mat( src, dest ) = DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ );

	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::shift( int x, Number offset ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );

	for ( int i = 0; i < m_dbm.rows(); i++ ) {
		if ( i != x ) {
			// d_xi = d_xi+ (offset, <=)
			mat( x, i ) = m_dbm( x, i ) + DBMEntry( offset, BOUND_TYPE::SMALLER_EQ );

			// d_ix = d_ix + (-offset, <=)
			mat( i, x ) = m_dbm( i, x ) + DBMEntry( -offset, BOUND_TYPE::SMALLER_EQ );
		}
	}
	//d_x0 = max(d_x0, (0, <=))
	mat( x, 0 ) = DBMEntry::max( mat( x, 0 ), DBMEntry( 0, BOUND_TYPE::SMALLER_EQ ) );
	//d_0x = min(d_0x, (0, <=))
	mat( 0, x ) = DBMEntry::min( mat( 0, x ), DBMEntry( 0, BOUND_TYPE::SMALLER_EQ ) );

	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::shift( Number offset ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	/*
        for(int clock = 1; clock < m_dbm.rows(); clock++){
            // for each clock apply the shift(x,offset) procedure
            for (int i = 0; i < m_dbm.rows(); i++) {
                if (i != clock) {
                    // d_xi = d_xi+ (offset, <=)
                    mat(clock, i) = m_dbm(clock, i) + DBMEntry(offset, BOUND_TYPE::SMALLER_EQ);

                    // d_ix = d_ix + (-offset, <=)
                    mat(i, clock) = m_dbm(i, clock) + DBMEntry(-offset, BOUND_TYPE::SMALLER_EQ);
                }
            }
            //d_x0 = max(d_x0, (0, <=))
            mat(clock, 0) = DBMEntry::max(mat(clock,0), DBMEntry(0, BOUND_TYPE::SMALLER_EQ));
            //d_0x = min(d_0x, (0, <=))
            mat(0, clock) = DBMEntry::min(mat(0,clock), DBMEntry(0, BOUND_TYPE::SMALLER_EQ));
        }*/

	for ( int clock = 1; clock < m_dbm.rows(); clock++ ) {
		// d_xi = d_xi+ (offset, <=)
		mat( clock, 0 ) = m_dbm( clock, 0 ) + DBMEntry( offset, BOUND_TYPE::SMALLER_EQ );

		// d_ix = d_ix + (-offset, <=)
		mat( 0, clock ) = m_dbm( 0, clock ) + DBMEntry( -offset, BOUND_TYPE::SMALLER_EQ );

		//d_x0 = max(d_x0, (0, <=))
		mat( clock, 0 ) = DBMEntry::max( mat( clock, 0 ), DBMEntry( 0, BOUND_TYPE::SMALLER_EQ ) );
		//d_0x = min(d_0x, (0, <=))
		mat( 0, clock ) = DBMEntry::min( mat( 0, clock ), DBMEntry( 0, BOUND_TYPE::SMALLER_EQ ) );
	}

	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
bool DifferenceBoundsT<Number, Converter, Setting>::contains( const DifferenceBoundsT<Number, Converter, Setting>& _rhs ) const {
	// we assert that both DBM constraint the same clocks. Note that a DBM that would describe a projection
	// to some subset of clocks can be given by setting the entries of the other clocks in the DBM to 0.
	// Hence a DBM should always be as large as the number of clocks in the automaton.
	assert( this->getDBM().cols() == _rhs.getDBM().cols() );
	bool contains = true;
	for ( int i = 0; i < this->getDBM().rows(); i++ ) {
		for ( int j = 0; j < this->getDBM().cols(); j++ ) {
			if ( i != j ) {
				contains = contains && ( _rhs.getDBM()( i, j ) <= this->getDBM()( i, j ) );
			}
		}
	}
	return contains;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::intersectConstraint( const int x, const int y, const DBMEntry& bound ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	if ( mat( x, y ) == bound ) {
		// bound does not change
		hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
		res.setDBM( mat );
		return res;
	}
	// d_yx+bound < 0
	DBMEntry potentialEntry = mat( y, x ) + bound;
	//TODO hot fix to account for rounding issue (should be way lower than time step)
	if ( potentialEntry < DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ ) && !( potentialEntry > DBMEntry( -0.00000001, BOUND_TYPE::SMALLER_EQ ) ) ) {
		//invalid dbm because upper bound became negative
		mat( 0, 0 ).first = -1.0;
	}
	// bound < d_xy
	else if ( ( bound < mat( x, y ) ) ) {
		mat( x, y ) = bound;
		// cutting off parts of the dbm can yield to other constrainst not being tight anymore
		// we correct this because other operations depend on this assumption
		for ( int i = 0; i < mat.rows(); i++ ) {
			for ( int j = 0; j < mat.cols(); j++ ) {
				if ( i != j ) {
					DBMEntry firstEntry = mat( i, x ) + mat( x, j );
					// do not write really small error values (~10^⁻16)
					if ( firstEntry < mat( i, j ) && !( firstEntry < DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ ) && firstEntry > DBMEntry( -0.00000001, BOUND_TYPE::SMALLER_EQ ) ) ) {
						mat( i, j ) = firstEntry;
					}
					DBMEntry secondEntry = mat( i, y ) + mat( y, j );
					if ( secondEntry < mat( i, j ) && !( secondEntry < DBMEntry( 0.0, BOUND_TYPE::SMALLER_EQ ) && secondEntry > DBMEntry( -0.00000001, BOUND_TYPE::SMALLER_EQ ) ) ) {
						mat( i, j ) = secondEntry;
					}
				}
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>();
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter, Setting>> DifferenceBoundsT<Number, Converter, Setting>::intersectConstraints( const matrix_t<Number> constraints, const vector_t<Number> constants, const CONTAINMENT defaultOnEmptyConstraints ) const {
	if ( constraints.rows() == 0 ) {
		return std::make_pair( defaultOnEmptyConstraints, *this );
	}

	hypro::DifferenceBoundsT<Number, Converter, Setting> dbm = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	for ( int i = 0; i < constraints.rows(); i++ ) {
		// for each constraint find the variable index it constraints
		hypro::matrix_t<Number> constraint = constraints.row( i );
		int var = -1;
		for ( int j = 0; j < constraint.cols(); j++ ) {
			if ( constraint( 0, j ) == 1.0 || constraint( 0, j ) == -1.0 ) {
				var = j;
				break;
			}
		}

		// index found
		if ( var != -1 ) {
			if ( constraint( 0, var ) == 1.0 ) {
				// cut with x-0 <= c
				dbm = dbm.intersectConstraint( var + 1, 0, hypro::DifferenceBoundsT<Number, Converter, Setting>::DBMEntry( constants( i ), hypro::DifferenceBoundsT<Number, Converter, Setting>::BOUND_TYPE::SMALLER_EQ ) );
			} else {
				// cut with 0-x <= c
				dbm = dbm.intersectConstraint( 0, var + 1, hypro::DifferenceBoundsT<Number, Converter, Setting>::DBMEntry( constants( i ), hypro::DifferenceBoundsT<Number, Converter, Setting>::BOUND_TYPE::SMALLER_EQ ) );
			}
		}
		// if the resulting dbm is empty, the guard is not satisfied
		if ( dbm.getDBM()( 0, 0 ).first == -1.0 ) {
			return std::make_pair( CONTAINMENT::NO, std::move( dbm ) );
		}
	}
	return std::make_pair( CONTAINMENT::PARTIAL, std::move( dbm ) );
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::extraM( const vector_t<DBMEntry>& MBounds ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i != j ) {
				// INFTY if c_ij > M(x_i)
				if ( m_dbm( i, j ).first > MBounds( i ).first || MBounds( i ).second == BOUND_TYPE::INFTY ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// (-M(x_j), <) if -c_ij > M(x_j)
				else if ( ( -1.0 * m_dbm( i, j ).first ) > MBounds( j ).first || MBounds( j ).second == BOUND_TYPE::INFTY ) {
					if ( MBounds( j ).second == BOUND_TYPE::INFTY ) {
						// -c_ij > -INFTY >= c_ij' = (-M(x_j), <) = INFTY
						mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
					} else {
						mat( i, j ) = DBMEntry( -1.0 * MBounds( j ).first, BOUND_TYPE::SMALLER );
					}
				}
			}
			// (c_ij, </<=/INFTY) otherwise (i.e. copy) -> no op
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::extraMPlus( const vector_t<DBMEntry>& MBounds ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i != j ) {
				// INFTY if c_ij > M(x_i)
				if ( m_dbm( i, j ).first > MBounds( i ).first || MBounds( i ).second == BOUND_TYPE::INFTY ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// INFTY if  -c_0i > M(x_i)
				else if ( -1.0 * m_dbm( 0, i ).first > MBounds( i ).first ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// INFTY if -c_0j > M(x_j), i!=0
				else if ( ( -1.0 * m_dbm( 0, j ).first > MBounds( j ).first || MBounds( j ).second == BOUND_TYPE::INFTY ) && i != 0 ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// (-M(x_j), <) if -c_ij > M(x_j)
				else if ( ( ( -1.0 * m_dbm( i, j ).first ) > MBounds( j ).first || MBounds( j ).second == BOUND_TYPE::INFTY ) && i == 0 ) {
					if ( MBounds( j ).second == BOUND_TYPE::INFTY ) {
						// -c_ij > -INFTY >= c_ij' = (-M(x_j), <) = INFTY
						mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
					} else {
						mat( i, j ) = DBMEntry( -1.0 * MBounds( j ).first, BOUND_TYPE::SMALLER );
					}
				}
				// (c_ij, </<=/INFTY) otherwise (i.e. copy) -> no op
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::extraLU( const vector_t<DBMEntry>& LBounds, const vector_t<DBMEntry>& UBounds ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i != j ) {
				// INFTY if c_ij > L(x_i)
				if ( m_dbm( i, j ).first > LBounds( i ).first || LBounds( i ).second == BOUND_TYPE::INFTY ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// (-U(x_j),<) if -c_ij > U(x_j)
				else if ( -1.0 * m_dbm( i, j ).first > UBounds( j ).first || UBounds( j ).second == BOUND_TYPE::INFTY ) {
					if ( UBounds( j ).second == BOUND_TYPE::INFTY ) {
						// -c_ij > -INFTY >= c_ij' = (-U(x_j), <) = INFTY
						mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
					} else {
						mat( i, j ) = DBMEntry( -1.0 * UBounds( j ).first, BOUND_TYPE::SMALLER );
					}
				}
				// (c_ij, </<=/INFTY) otherwise (i.e. copy) -> no op
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
DifferenceBoundsT<Number, Converter, Setting> DifferenceBoundsT<Number, Converter, Setting>::extraLUPlus( const vector_t<DBMEntry>& LBounds, const vector_t<DBMEntry>& UBounds ) const {
	hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>( m_dbm );
	for ( int i = 0; i < mat.rows(); i++ ) {
		for ( int j = 0; j < mat.cols(); j++ ) {
			if ( i != j ) {
				// INFTY if c_ij > L(x_i)
				if ( m_dbm( i, j ).first > LBounds( i ).first || LBounds( i ).second == BOUND_TYPE::INFTY ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// INFTY if -c_0i > L(x_i)
				else if ( -1.0 * m_dbm( 0, i ).first > LBounds( i ).first ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// INFTY if -c_0j>U(x_j), i!=0
				else if ( ( -1.0 * m_dbm( 0, j ).first > UBounds( j ).first || UBounds( j ).second == BOUND_TYPE::INFTY ) &&
						  i != 0 ) {
					mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
				}
				// (-U(x_j),<) if -c_0j > U(x_j), i==0
				else if ( ( -1.0 * m_dbm( 0, j ).first > UBounds( j ).first || UBounds( j ).second == BOUND_TYPE::INFTY ) &&
						  i == 0 ) {
					if ( UBounds( j ).second == BOUND_TYPE::INFTY ) {
						// -c_ij > -INFTY >= c_ij' = (-U(x_j), <) = INFTY
						mat( i, j ) = DBMEntry( 0.0, BOUND_TYPE::INFTY );
					} else {
						mat( i, j ) = DBMEntry( -1.0 * UBounds( j ).first, BOUND_TYPE::SMALLER );
					}
				}
				// (c_ij, </<=/INFTY) otherwise (i.e. copy) -> no op
			}
		}
	}
	hypro::DifferenceBoundsT<Number, Converter, Setting> res = hypro::DifferenceBoundsT<Number, Converter, Setting>( *this );
	res.setDBM( mat );
	return res;
}

template <typename Number, typename Converter, class Setting>
const DifferenceBoundsT<Number, Converter, Setting>& DifferenceBoundsT<Number, Converter, Setting>::removeRedundancy() {
	// we intend to always have a canonized dbm, so this should always be redundancy free
	return *this;
}
}  // namespace hypro
