#include "DifferenceBounds.h"

namespace hypro {

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DifferenceBoundsT(){
        m_dbm = matrix_t<std::pair<Number,DifferenceBoundsT<Number, Converter>:: BOUND_TYPE>>(1,1);
        m_dbm << std::pair<Number,DifferenceBoundsT<Number, Converter>::BOUND_TYPE>(0,DifferenceBoundsT<Number, Converter>::BOUND_TYPE::SMALLER);
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DifferenceBoundsT (matrix_t<std::pair<Number, DifferenceBoundsT<Number, Converter>::BOUND_TYPE >>){
        // TODO
    }

    template <typename Number, typename Converter>
    matrix_t<std::pair<Number, typename DifferenceBoundsT<Number, Converter>::BOUND_TYPE>> DifferenceBoundsT<Number, Converter>::getDBM() const{
        return m_dbm;
    }

    template <typename Number, typename Converter>
    void DifferenceBoundsT<Number, Converter>::setDBM(matrix_t<std::pair<Number,Converter>> dbm){
        // TODO
    }

    template <typename Number, typename Converter>
    std::size_t DifferenceBoundsT<Number, Converter>::dimension() const{
        // TODO
        return 0;
    }

    template <typename Number, typename Converter>
    std::size_t DifferenceBoundsT<Number, Converter>::size() const{
        // TODO
        return 0;
    }

    template <typename Number, typename Converter>
    bool DifferenceBoundsT<Number, Converter>::empty() const{
        // TODO
        return false;
    }

    template <typename Number, typename Converter>
    std::vector<Point<Number>> DifferenceBoundsT<Number, Converter>::vertices( const matrix_t<Number>& ) const{
        // TODO
        return vector<Point<Number>>(2);
    }

    template <typename Number, typename Converter>
    std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter>> DifferenceBoundsT<Number, Converter>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const{
        // TODO
        return std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter>>();
    }

    template <typename Number, typename Converter>
    std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter>> DifferenceBoundsT<Number, Converter>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const{
        // TODO
        return std::pair<CONTAINMENT, DifferenceBoundsT<Number, Converter>>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::project(const std::vector<std::size_t>& dimensions) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::linearTransformation( const matrix_t<Number>& A ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::minkowskiSum( const DifferenceBoundsT<Number,Converter>& _rhs ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::intersect( const DifferenceBoundsT<Number,Converter>& _rhs ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::intersectHalfspace( const Halfspace<Number>& hs ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    bool DifferenceBoundsT<Number, Converter>::contains( const Point<Number>& _point ) const{
        // TODO
        return true;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::unite( const DifferenceBoundsT<Number,Converter>& _rhs ) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }
}

