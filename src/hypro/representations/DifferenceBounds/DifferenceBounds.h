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
public:
    DifferenceBoundsT ();
    DifferenceBoundsT (const DifferenceBoundsT& orig) = default;
    DifferenceBoundsT (matrix_t<std::pair<Number, BOUND_TYPE >>);

    matrix_t<std::pair<Number, BOUND_TYPE>> getDBM() const;
    void setDBM(matrix_t<std::pair<Number,BOUND_TYPE>> dbm);

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