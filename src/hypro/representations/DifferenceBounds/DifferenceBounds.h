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

    class DBMEntry : public std::pair<Number, BOUND_TYPE>{
    public:
        using std::pair<Number, BOUND_TYPE>::first;
        using std::pair<Number, BOUND_TYPE>::second;
        DBMEntry();
        DBMEntry(Number number, BOUND_TYPE boundType);

        static DBMEntry max(const DBMEntry& lhs, const DBMEntry& rhs)  { return lhs < rhs ? rhs : lhs;}
        static DBMEntry min(const DBMEntry& lhs, const DBMEntry& rhs)  { return lhs < rhs ? lhs : rhs;}

        bool operator<(const DBMEntry rhs){
            if(this->second == BOUND_TYPE::INFTY){
                // TODO correct?
                return false;
            }
            // (n, </<=) < infty
            if(rhs.second == BOUND_TYPE::INFTY) {
                return true;
            }
            // (n_1, </<=) < (n_2, </<=) if n_1 < n_2
            if(this->first < rhs.first){
                return true;
            }
            // (n, <) < (n,<=)
            if(this->first == rhs.first && this->second == BOUND_TYPE::SMALLER && rhs.second == BOUND_TYPE::SMALLER_EQ){
                return true;
            }
            return false;
        }

        bool operator==(const DBMEntry rhs){
            if(this->second == BOUND_TYPE::INFTY && rhs.second == BOUND_TYPE::INFTY) {
                return true;
            }
            // (n_1, </<=) == (n_2, </<=) if n_1 == n_2 and </<=_1 == </<=_2
            if(this->first == rhs.first && this->second == rhs.second){
                return true;
            }
            return false;
        }

        bool operator<=(const DBMEntry rhs){
            return (*this < rhs) || (*this == rhs);
        }

        DBMEntry operator+(const DBMEntry rhs){
            // adding infinity yields infinity;
            if(this->second == BOUND_TYPE::INFTY || rhs.second == BOUND_TYPE::INFTY){
                return DBMEntry(0.0, BOUND_TYPE::INFTY);
            }
            // (m,<=)+(n,<=) = (m+n,<=)
            if(this->second == BOUND_TYPE::SMALLER_EQ && rhs.second == BOUND_TYPE::SMALLER_EQ){
                return DBMEntry(this->first+rhs.first, BOUND_TYPE::SMALLER_EQ);
            }
            // (m,<)+(n,</<=) = (m+n,<)
            return DBMEntry(this->first+rhs.first, BOUND_TYPE::SMALLER);
        }

        friend std::ostream& operator<<( std::ostream& ostr, const DBMEntry entry ) {
            ostr << "( ";
            ostr << entry.first;
            ostr << ", ";
            ostr << entry.second;
            ostr << " )";
            return ostr;
        }
    };
private:
    mutable matrix_t<DBMEntry> m_dbm;
    Number m_timeHorizon;

public:
    DifferenceBoundsT ();
    DifferenceBoundsT (const DifferenceBoundsT& orig) = default;

    matrix_t<DBMEntry> getDBM() const;
    void setDBM(matrix_t<DBMEntry> dbm);

    Number getTimeHorizon() const;
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
     * Frees a clock x, i.e. removes all bounding constraints for that clock
     * @param x index of the clock
     * @return DBM with clock x freed
     */
    DifferenceBoundsT<Number,Converter> free(int x) const;

    /**
     * Resets clock x to given Number value.
     * @param x index of the clock
     * @param value reset value of the clock
     * @return DBM with clock x reset to value
     */
    DifferenceBoundsT<Number,Converter> reset(int x, Number value) const;

    /**
     * Copies a the value of clock src to clock dest, i.e. resets the value of
     * dest to the value of src.
     * @param src index of src clock
     * @param dest index of dest clock
     * @return DBM with clock dest set to clock src
     */
    DifferenceBoundsT<Number,Converter> copy(int src, int dest) const;

    /**
     * Shifts the valuation of clock x by the given offset
     * @param x index of the clock
     * @param offset offset to be applied
     * @return DBM with clock x shifted by offset
     */
    DifferenceBoundsT<Number,Converter> shift(int x, Number offset) const;


    /**
     * checks whether _rhs is contained in the left hand side
     *
     * A DBM X contains a DBM Y if the lower bounds of Y are greater or equal than the lower bounds of X
     * and the upper bounds of Y are smaller or equal than the upper bounds of X.
     *
     * This is the case if for every entry i,j in Y d_ij is lower or equal than the corresponding d_ij in X
     * @param _rhs
     * @return true is lhs contains rhs
     */
    bool contains( const DifferenceBoundsT<Number,Converter>& _rhs ) const;

    /**
     * intersects the DBM with the bound given by index x, y and bound value bound
     * i.e. x-y <= bound
     * @param i
     * @param j
     * @param bound
     * @return the intersection of the DBM with constraint x-y bound
     */
    DifferenceBoundsT<Number,Converter> intersectConstraint( const int x, const int y, const DBMEntry& bound ) const;

    friend std::ostream& operator<<( std::ostream& ostr, const DifferenceBoundsT<Number,Converter>& db ) {
        long rows = db.getDBM().rows();
        long cols = db.getDBM().cols();
        if(rows > 0 && cols > 0){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    ostr <<  db.getDBM()(i,j);
                }
                ostr << "\n";
            }
        }
        return ostr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const BOUND_TYPE value){
        switch (value){
            case SMALLER : ostr << "<"; break;
            case SMALLER_EQ : ostr << "<="; break;
            case INFTY : ostr << "inf"; break;
            default: ostr << "undef"; break;
        }
        return ostr;
    }
};
}
#include "DifferenceBounds.tpp"