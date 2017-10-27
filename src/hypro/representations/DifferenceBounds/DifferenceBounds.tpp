#include "DifferenceBounds.h"

namespace hypro {


    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DifferenceBoundsT(){
        m_dbm = matrix_t<std::pair<Number,DifferenceBoundsT<Number, Converter>:: BOUND_TYPE>>(1,1);
        m_dbm << std::pair<Number,DifferenceBoundsT<Number, Converter>::BOUND_TYPE>(0,DifferenceBoundsT<Number, Converter>::BOUND_TYPE::SMALLER);
        m_timeHorizon = 0.0;
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
    void DifferenceBoundsT<Number, Converter>::setDBM(matrix_t<std::pair<Number,DifferenceBoundsT<Number, Converter>::BOUND_TYPE>> dbm) {
        m_dbm = dbm;
    }

    template <typename Number, typename Converter>
    Number DifferenceBoundsT<Number, Converter>::getTimeHorizion() const{
        return m_timeHorizon;
    }

    template <typename Number, typename Converter>
    void DifferenceBoundsT<Number, Converter>::setTimeHorizon(Number horizon) {
        m_timeHorizon = horizon;
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
        /*
         * Convert the Difference Bound Matrix into a polytope and then compute the vertices on it
         * TODO move the conversion process into a converter
         */
        //std::cout << "Starting to calculate vertices on DBM: " << *this << "\n";
        int numclocks = m_dbm.cols()-1;
        //std::cout << "Number of clocks: " << numclocks << "\n";
        int numconstraints = 0; //all entries of the DBM (except the diagonal and inifinities) define a constraint
        for(int i = 0; i < m_dbm.rows(); i++){
            for(int j=0; j < m_dbm.rows();j++){
                if(!(i == j) && !(m_dbm(i,j).second ==  BOUND_TYPE::INFTY)){
                    numconstraints++;
                }
            }
        }
        // TODO enhace plotting for inifinite polytopes
        numconstraints += numclocks; // we need numclocks additional constraints for the timehorizon to  plot infinite polytopes

        //constraints of the polytope
        hypro::matrix_t<Number> HPolyConstraints = hypro::matrix_t<Number>::Zero(numconstraints,numclocks);
        hypro::vector_t<Number> HPolyConstants = hypro::vector_t<Number>::Zero(numconstraints);

        int counter = 0; // counter for indexing constraints
        for(int i = 0; i < m_dbm.rows();i++){
            for(int j = 0; j < m_dbm.cols();j++){
                //std::cout<< "Process entry at: (" <<i<<","<<j<<")\n";
                // do not consider diagonals
                if(! (i == j) && !(m_dbm(i,j).second == BOUND_TYPE::INFTY)){
                    // the constraint to add
                    matrix_t<Number> constraintVars = matrix_t<Number>::Zero(1,numclocks);
                    if (i == 0){
                        // constraint of the form 0-x_j <= c_ij
                        constraintVars(0,j-1) = -1.0; // j-1 because we don't consider static clock 0
                    }
                    else if (j==0){
                        // constraint of the form x_i - 0  <= c_ij
                        constraintVars(0,i-1) = 1.0; // i-1 because we don't consider static clock 0
                    }
                    else{
                        // constraint of the form x_i - x_j  <= c_ij
                        constraintVars(0,i-1) = 1.0; // i-1 because we don't consider static clock 0
                        constraintVars(0,j-1) = -1.0; // j-1 because we don't consider static clock 0
                    }
                    //std::cout << "Constraint variable vector: " << constraintVars <<"\n";
                    HPolyConstraints.row(counter) = constraintVars;
                    //std::cout << "New constraint matrix: " << HPolyConstraints << "\n";
                    HPolyConstants(counter,0) = m_dbm(i,j).first;
                    //std::cout << "New constant vector: " << HPolyConstants << "\n";
                    counter++;
                }
            }
        }
        // TODO enhace plotting for inifinite polytopes
        for(int i=0; i < numclocks; i++){
            // for each clock at a timehorizon constraint so the polytope to plot is finite
            matrix_t<Number> constraintVars = matrix_t<Number>::Zero(1,numclocks);
            constraintVars(0,i) = 1.0;
            std::cout << "Constraint variable vector: " << constraintVars <<"\n";
            HPolyConstraints.row(counter) = constraintVars;
            std::cout << "New constraint matrix: " << HPolyConstraints << "\n";
            HPolyConstants(counter,0) = getTimeHorizion();
            std::cout << "New constant vector: " << HPolyConstants << "\n";
            counter++;
        }
        std::cout << "Generated polytope: \n Matrix: \n" << HPolyConstraints << "\n Vector: \n" << HPolyConstants <<"\n";
        hypro::HPolytopeT<Number,Converter> poly(HPolyConstraints,HPolyConstants);
        return poly.vertices();
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


    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::elapse() const{
        hypro::matrix_t<std::pair<Number, BOUND_TYPE >> mat =  hypro::matrix_t<std::pair<Number, BOUND_TYPE >>(m_dbm);
        for(int i = 1; i < m_dbm.rows(); i++){
            mat(i,0).second = BOUND_TYPE::INFTY;
        }
        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>();
        res.setDBM(mat);
        return res;
    }


    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::rewind() const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::free(int i) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::reset(int i, Number value) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::copy(int src, int dest) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::shift(int i, Number offset) const{
        // TODO
        return DifferenceBoundsT<Number,Converter>();
    }
}

