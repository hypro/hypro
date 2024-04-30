//
// This class was created using the implementation of Malte Gerdes. Some of the comments are taken from his thesis.
//
#pragma once

#include <hypro/datastructures/Halfspace.h>
#include <hypro/types.h>

using Eigen::Index;
using Eigen::VectorXi;
using bitset = boost::dynamic_bitset<uint8_t>;

namespace hypro {
    template <typename Number>
    class DDPair {
    public:
        DDPair( const matrix_t<Number>&, const vector_t<Number>& );
        std::vector<vector_t<Number>> getPoints();
        void compute();

    private:
        std::vector<bitset> create_zerosets( const std::vector<int>& );
        void eliminate( matrix_t<Number>&, Index );
        Index select_pivot( const vector_t<Number>&, Index i );
        VectorXi max_independent_rows( matrix_t<Number> );
        bool is_adjacent( const std::vector<bitset>&, bitset::size_type, bitset::size_type );
        vector_t<Number> create_ray( const vector_t<Number>&, const vector_t<Number>&, const vector_t<Number>& );
        void step( const Index&, const std::vector<int>& );

        matrix_t<Number> R;
        matrix_t<Number> A;
    };

    /**
     * This is a constructor. It expects a matrix A and a vector b such that Ax<=b.
     * The homogenized matrix describing the cone containing that H-polytope is saved as an attribute.
     * @tparam Number
     * @param constraints
     * @param offset
     */
    template <typename Number>
    DDPair<Number>::DDPair( const matrix_t<Number>& constraints, const vector_t<Number>& offset ) {
        this->A = matrix_t<Number>( constraints.rows() + 1, constraints.cols() + 1 );
        this->A.row( 0 )[0] = -1;
        for ( Index i = 0; i < constraints.rows(); i++ ) {
            this->A.row( i + 1 ) << -offset[i], constraints.row( i );
        }
    }

    /**
     * Extracts and returns the points which define the V-polytope from the generator matrix.
     * Every column is scaled appropriately.
     * @tparam Number
     * @return
     */
    template <typename Number>
    std::vector<vector_t<Number>> DDPair<Number>::getPoints() {
        std::vector<vector_t<Number>> result;

        for ( const auto& col : this->R.colwise() ) {
			if(col[0] == 0) {
				result.emplace_back( vector_t<Number>(col.size() - 1));
			} else {
				result.emplace_back( col( Eigen::seq( 1, Eigen::last ) ) / col[0] );
			}
        }

        return result;
    }

    /**
     * Does a single elimination step of gauss elimination, given a row index to be used as a pivot.
     * @tparam Number
     * @param A
     * @param i
     */
    template <typename Number>
    void DDPair<Number>::eliminate( matrix_t<Number>& A, Index i ) {
        for ( Index j = i + 1; j < A.rows(); j++ ) {
            if ( A( i, i ) != 0 ) {
                Number l = -A( j, i ) / A( i, i );
                A.row( j ) += A.row( i ) * l;
            }
        }
    }

    /**
     * Returns the index of the absolute maximum value of the current column.
     * @tparam Number
     * @param a
     * @param i
     * @return
     */
    template <typename Number>
    Index DDPair<Number>::select_pivot( const vector_t<Number>& a, Index i ) {
        auto pos = std::max_element( a.begin() + i, a.end(),
                                     []( const Number& x, const Number& y ) {
                                         return abs( x ) < abs( y );
                                     } );

        return std::distance( a.begin(), pos );
    }

    /**
     * Create the zero sets for all rays.
     * @tparam Number
     * @param rows
     * @return
     */
    template <typename Number>
    std::vector<bitset> DDPair<Number>::create_zerosets( const std::vector<int>& rows ) {
        std::vector<bitset> Z;

        for ( Index i = 0; i < this->R.cols(); i++ ) {
            Z.emplace_back( bitset( rows.size() ) );

            for ( Index j = 0; j < rows.size(); j++ ) {
                Number result = this->A.row( rows[j] ) * this->R.col( i );
                if ( result == 0 ) {
                    Z[i][j] = true;
                }
            }
        }

        TRACE("hypro.doubleDescriptionMethod", "A:\n" << this->A(rows, Eigen::all));
        TRACE("hypro.doubleDescriptionMethod", "R:\n" << this->R);
        TRACE("hypro.doubleDescriptionMethod", "ZeroSets:\n" << Z);

        return Z;
    }

    /**
     * Determines the indices of the rows that make up the maximal linear independent subsystem.
     * @tparam Number
     * @param A
     * @return
     */
    template <typename Number>
    VectorXi DDPair<Number>::max_independent_rows( matrix_t<Number> A ) {
        VectorXi perms = VectorXi::LinSpaced( A.rows(), 0, A.rows() - 1 );

        for ( Index i = 0; i < A.cols(); i++ ) {
            Index pivot = select_pivot( A.col( i ), i );

            if ( i != pivot ) {
                A.row( i ).swap( A.row( pivot ) );
                std::swap( perms[i], perms[pivot] );
            }

            eliminate( A, i );
        }

        return perms.head( A.cols() );
    }

    /**
     * Does the combinatorial adjacency check.
     * The implementation is a literal translation of Algorithm 3.2.
     * @tparam Number
     * @param Z
     * @param i
     * @param j
     * @return
     */
    template <typename Number>
    bool DDPair<Number>::is_adjacent( const std::vector<bitset>& Z, bitset::size_type i, bitset::size_type j ) {
        bitset intersection = Z[i] & Z[j];

        for ( std::size_t k = 0; k < Z.size(); k++ ) {
            if ( k == i || k == j ) continue;

            if ( intersection.is_proper_subset_of( Z[k] ) )
                return false;
        }
        return true;
    }

    /**
     * Literal translation of the equally named function from Algorithm 3.1.
     * <n,v>w - <n,w>v
     * where n is row, v and w are a and b, respectively
     * @tparam Number
     * @param row
     * @param a
     * @param b
     * @return
     */
    template <typename Number>
    vector_t<Number> DDPair<Number>::create_ray( const vector_t<Number>& row, const vector_t<Number>& a, const vector_t<Number>& b ) {
        return ( row.dot( a ) * b ) - ( row.dot( b ) * a );
    }

    /**
     * Literal translation of the equally named function from Algorithm 3.1.
     * @tparam Number
     * @param index
     * @param rows
     */
    template <typename Number>
    void DDPair<Number>::step( const Index& index, const std::vector<int>& rows ) {
        bitset pos( this->R.cols() );
        bitset neg( this->R.cols() );

        TRACE("hypro.doubleDescriptionMethod", "current row of A: \n" << A.row(index));
        TRACE("hypro.doubleDescriptionMethod", "current R: \n" << this->R);

        //We only use J+ and J-, therefore J0 can be ommited.
        std::size_t o = 0;
        for ( const auto& col : this->R.colwise() ) {
            Number x = this->A.row( index ).dot( col );

            if ( x > 0 ) {
                pos[o] = true;
            } else if ( x < 0 ) {
                neg[o] = true;
            }
            o++;
        }

        TRACE("hypro.doubleDescriptionMethod", "pos/neg: " << pos << " / " << neg)

        std::vector<bitset> Z = create_zerosets( rows );
        TRACE("hypro.doubleDescriptionMethod", "have zerosets")
        std::vector<std::pair<Index, Index>> want_rays;
        for ( bitset::size_type i = pos.find_first(); i < pos.size(); i = pos.find_next( i ) ) {
            for ( bitset::size_type j = neg.find_first(); j < neg.size(); j = neg.find_next( j ) ) {
                if ( is_adjacent( Z, i, j ) ) {
                    want_rays.emplace_back( std::make_pair( i, j ) );
                }
            }
        }

        bitset keep_rays = ~neg;
        matrix_t<Number> result( this->A.cols(), keep_rays.count() + want_rays.size() );

        std::size_t i = 0;
        for ( bitset::size_type j = pos.find_first(); j < pos.size(); j = pos.find_next( j ) ) {
            result.col( i++ ) = this->R.col( j );
        }

        keep_rays ^= pos;
        for ( bitset::size_type j = keep_rays.find_first(); j < keep_rays.size(); j = keep_rays.find_next( j ) ) {
            result.col( i++ ) = this->R.col( j );
        }

        TRACE("hypro.doubleDescriptionMethod", "create rays")
        for ( const auto& adj : want_rays ) {
            result.col( i++ ) = create_ray( this->A.row( index ), this->R.col( adj.first ), this->R.col( adj.second ) );
        }
        TRACE("hypro.doubleDescriptionMethod", "created rays")
        this->R = result;
    }

    /**
     * Initializes all data structures and does the actual iteration.
     * After this method the generator matrix holds the minimal amount of extreme rays.
     * @tparam Number
     */
    template <typename Number>
    void DDPair<Number>::compute() {
        VectorXi rows = max_independent_rows( A );
        matrix_t<Number> A_inv = this->A( rows, Eigen::all ).inverse();
        TRACE("hypro.doubleDescriptionMethod", 	this->A << "\nA_small\n" << this->A(rows, Eigen::all) << "A_inv:\n" << A_inv << "\n" << rows)
        TRACE("hypro.doubleDescriptionMethod", this->A(rows, Eigen::all) * A_inv)
        std::vector<int> _rows( rows.data(), rows.data() + rows.rows() * rows.cols() );

        bitset seen( this->A.rows() );
        for ( const auto& x : rows ) {
            seen[x] = true;
        }
        seen.flip();

        this->R = A_inv;
        for ( bitset::size_type i = seen.find_first(); i < seen.size(); i = seen.find_next( i ) ) {
            step( i, _rows );
            seen[i].flip();
            _rows.push_back( i );
        }

        TRACE("hypro.doubleDescriptionMethod", "final R:\n" << this->R)
    }
}  // namespace hypro