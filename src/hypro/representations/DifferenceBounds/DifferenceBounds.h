#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "../../datastructures/Point.h"

namespace hypro {
template<typename Number>
class Point;
/**
 * @brief      Class wrapping the difference bounds content.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 */
template <typename Number, typename Converter>
class DifferenceBoundsT : public GeometricObject<Number, DifferenceBoundsT<Number, Converter>>{
public:
    enum BOUND_TYPE{
        SMALLER,
        SMALLER_EQ,
        INFTY,
    };
private:
    mutable matrix_t<std::pair<Number, BOUND_TYPE>> m_dbm;
    Number m_timeHorizon;

public:
    DifferenceBoundsT ();
    DifferenceBoundsT (const DifferenceBoundsT& orig) = default;
    DifferenceBoundsT (matrix_t<std::pair<Number, BOUND_TYPE >>);

    matrix_t<std::pair<Number, BOUND_TYPE>> getDBM() const;
    void setDBM(matrix_t<std::pair<Number,BOUND_TYPE>> dbm);

    Number getTimeHorizion() const;
    void setTimeHorizon(Number horizon);

    // geometric object
    std::size_t dimension() const;
    std::size_t size() const;
    static representation_name type() {return representation_name::difference_bounds;}
    bool empty() const;
    std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero(0,0) ) const;
    std::pair<CONTAINMENT, DifferenceBoundsT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
    std::pair<CONTAINMENT, DifferenceBoundsT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
    DifferenceBoundsT<Number,Converter> project(const std::vector<std::size_t>& dimensions) const;
    DifferenceBoundsT<Number,Converter> linearTransformation( const matrix_t<Number>& A ) const;
    DifferenceBoundsT<Number,Converter> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
    DifferenceBoundsT<Number,Converter> minkowskiSum( const DifferenceBoundsT<Number,Converter>& _rhs ) const;
    DifferenceBoundsT<Number,Converter> intersect( const DifferenceBoundsT<Number,Converter>& _rhs ) const;
    DifferenceBoundsT<Number,Converter> intersectHalfspace( const Halfspace<Number>& hs ) const;
    DifferenceBoundsT<Number,Converter> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
    bool contains( const Point<Number>& _point ) const;
    DifferenceBoundsT<Number,Converter> unite( const DifferenceBoundsT<Number,Converter>& _rhs ) const;

    // difference bounds specific

    /**
     * Elapses time for all clocks, i.e. d_i0 (that is x_i-0<=d_i0) is set to infinity
     * @return a DBM where the smaller(_eq) constraints for each clock is moved to infinity.
     */
    DifferenceBoundsT<Number,Converter> elapse() const;

    /**
     * Computes the set of clock assignments that can reach the current DBMs Zone when time
     * is elapsed. It is computed by setting all lower clock bound to 0.
     *
     * I.e. d_0i (that is 0-x_i <= d_0i <=> x_i >= -d_01) is set to 0
     * @return a DBM where the greater_(eq) constraints for each clock is moved to 0.
     */
    DifferenceBoundsT<Number,Converter> rewind() const;

    /**
     * Frees a clock i, i.e. removes all bounding constraints for that clock
     * @param i index of the clock
     * @return DBM with clock i freed
     */
    DifferenceBoundsT<Number,Converter> free(int i) const;

    /**
     * Resets clock i to given Number value.
     * @param i index of the clock
     * @param value reset value of the clock
     * @return DBM with clock i reset to value
     */
    DifferenceBoundsT<Number,Converter> reset(int i, Number value) const;

    /**
     * Copies a the value of clock src to clock dest, i.e. resets the value of
     * dest to the value of src.
     * @param src index of src clock
     * @param dest index of dest clock
     * @return DBM with clock dest set to clock src
     */
    DifferenceBoundsT<Number,Converter> copy(int src, int dest) const;

    /**
     * Shifts the valuation of clock i by the given offset
     * @param i index of the clock
     * @param offset offset to be applied
     * @return DBM with clock i shifted by offset
     */
    DifferenceBoundsT<Number,Converter> shift(int i, Number offset) const;


    friend std::ostream& operator<<( std::ostream& ostr, const DifferenceBoundsT<Number,Converter>& db ) {
        long rows = db.getDBM().rows();
        long cols = db.getDBM().cols();
        if(rows > 0 && cols > 0){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    std::pair<Number, BOUND_TYPE> p = db.getDBM()(i,j);
                    ostr << "( ";
                    ostr << p.first;
                    ostr << ", ";
                    ostr << p.second;
                    ostr << " )";
                }
                ostr << "\n";
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& ostr, const BOUND_TYPE value){
        switch (value){
            case SMALLER : ostr << "<"; break;
            case SMALLER_EQ : ostr << "<="; break;
            case INFTY : ostr << "inf"; break;
            default: ostr << "undef"; break;
        }
    }
};
}
#include "DifferenceBounds.tpp"