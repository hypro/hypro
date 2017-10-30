#include "DifferenceBounds.h"

namespace hypro {


    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DifferenceBoundsT(){
        m_dbm = matrix_t<DBMEntry>(1,1);
        m_dbm << DBMEntry(0,DifferenceBoundsT<Number, Converter>::BOUND_TYPE::SMALLER);
        m_timeHorizon = 0.0;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DBMEntry::DBMEntry(Number number, BOUND_TYPE boundType) : std::pair<Number, BOUND_TYPE>(number, boundType) {
        //nop
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number, Converter>::DBMEntry::DBMEntry() : std::pair<Number, BOUND_TYPE>() {
        //nop
    }

    template <typename Number, typename Converter>
    matrix_t<typename DifferenceBoundsT<Number, Converter>::DBMEntry> DifferenceBoundsT<Number, Converter>::getDBM() const{
        return m_dbm;
    }
    template <typename Number, typename Converter>
    void DifferenceBoundsT<Number, Converter>::setDBM(matrix_t<DifferenceBoundsT<Number, Converter>::DBMEntry> dbm) {
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
        /*
         *  A DBM is empty if the following holds for a position i,j in a dbm matrix
         *
         *  Let i>j, i.e. d_ij defines an upper bound. Then its value must be larger
         *  or equal to the corresponding lower bound d_ji.
         *
         *  TODO i assume that the dbm is also invalid if both bounds are infinity (correct???)
         *
         *  Consequently it suffices to traverse the lower half of the dbm matrix
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
        /*if(m_dbm(0,0).first == -1.0){
            // d_00 is -1 so we already found out that the dbm is empty
            return true;
        }
        // we assume that the dbm is non empty
        for(int i=0; i< m_dbm.rows();i++){
            // lower half (i > j)
            for(int j = 0; j < i; j++){
                std::cout << "( " << i << ", " << j << ") : " <<  m_dbm(i,j).first << " is smaller than " << "( " << j << ", " << i << ") : " <<  m_dbm(j,i).first << "\n";
                // if lower bound is infty, we know the dbm must be invalid (even if upper bound if infty as well)
                if(m_dbm(j,i).second == BOUND_TYPE::INFTY) {
                    m_dbm(0,0).first = -1.0;
                    return true;
                }
                // if the upper bound is lower than the corresponding lower bound we know the dbm is invalid
                if(m_dbm(i,j).second != BOUND_TYPE::INFTY && m_dbm(i,j).first <  m_dbm(j,i).first){
                     m_dbm(0,0).first = -1.0;
                    return true;
                }

            }
        }*/
        return false;
    }

    template <typename Number, typename Converter>
    std::vector<Point<Number>> DifferenceBoundsT<Number, Converter>::vertices( const matrix_t<Number>& ) const {
        /*
         * Convert the Difference Bound Matrix into a polytope and then compute the vertices on it
         * TODO move the conversion process into a converter
         */
        //std::cout << "Starting to calculate vertices on DBM: " << *this << "\n";
        int numclocks = m_dbm.cols() - 1;
        //std::cout << "Number of clocks: " << numclocks << "\n";
        int numconstraints = 0; //all entries of the DBM (except the diagonal and inifinities) define a constraint
        for (int i = 0; i < m_dbm.rows(); i++) {
            for (int j = 0; j < m_dbm.rows(); j++) {
                if (i != j && !(m_dbm(i, j).second == BOUND_TYPE::INFTY)) {
                    numconstraints++;
                }
            }
        }
        // TODO enhace plotting for inifinite polytopes
        numconstraints += numclocks; // we need numclocks additional constraints for the timehorizon to  plot infinite polytopes

        //constraints of the polytope
        hypro::matrix_t<Number> HPolyConstraints = hypro::matrix_t<Number>::Zero(numconstraints, numclocks);
        hypro::vector_t<Number> HPolyConstants = hypro::vector_t<Number>::Zero(numconstraints);

        int counter = 0; // counter for indexing constraints
        for (int i = 0; i < m_dbm.rows(); i++) {
            for (int j = 0; j < m_dbm.cols(); j++) {
                //std::cout<< "Process entry at: (" <<i<<","<<j<<")\n";
                // do not consider diagonals
                if (i != j && !(m_dbm(i, j).second == BOUND_TYPE::INFTY)) {
                    // the constraint to add
                    matrix_t<Number> constraintVars = matrix_t<Number>::Zero(1, numclocks);
                    if (i == 0) {
                        // constraint of the form 0-x_j <= c_ij
                        constraintVars(0, j - 1) = -1.0; // j-1 because we don't consider static clock 0
                    } else if (j == 0) {
                        // constraint of the form x_i - 0  <= c_ij
                        constraintVars(0, i - 1) = 1.0; // i-1 because we don't consider static clock 0
                    } else {
                        // constraint of the form x_i - x_j  <= c_ij
                        constraintVars(0, i - 1) = 1.0; // i-1 because we don't consider static clock 0
                        constraintVars(0, j - 1) = -1.0; // j-1 because we don't consider static clock 0
                    }
                    //std::cout << "Constraint variable vector: " << constraintVars <<"\n";
                    HPolyConstraints.row(counter) = constraintVars;
                    //std::cout << "New constraint matrix: " << HPolyConstraints << "\n";
                    HPolyConstants(counter, 0) = m_dbm(i, j).first;
                    //std::cout << "New constant vector: " << HPolyConstants << "\n";
                    counter++;
                }
            }
        }
        // TODO enhace plotting for inifinite polytopes
        if (getTimeHorizion() != 0.0) {
            for (int i = 0; i < numclocks; i++) {
                // for each clock at a timehorizon constraint so the polytope to plot is finite
                matrix_t<Number> constraintVars = matrix_t<Number>::Zero(1, numclocks);
                constraintVars(0, i) = 1.0;
                //std::cout << "Constraint variable vector: " << constraintVars <<"\n";
                HPolyConstraints.row(counter) = constraintVars;
                //std::cout << "New constraint matrix: " << HPolyConstraints << "\n";
                HPolyConstants(counter, 0) = getTimeHorizion();
                //std::cout << "New constant vector: " << HPolyConstants << "\n";
                counter++;
            }
        }
        else{
            std::cout << "Warning: TimeHorizon may not be configured correctly.";
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
        hypro::matrix_t<DBMEntry> mat =  hypro::matrix_t<DBMEntry>(m_dbm);
        for(int i = 1; i < m_dbm.rows(); i++){
            mat(i,0) = DBMEntry(0.0, BOUND_TYPE::INFTY);
        }
        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>(*this);
        res.setDBM(mat);
        return res;
    }


    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::rewind() const{
        hypro::matrix_t<DBMEntry> mat =  hypro::matrix_t<DBMEntry>(m_dbm);
        for(int i = 1; i < m_dbm.rows(); i++){
            mat(0,i) = DBMEntry(0.0, BOUND_TYPE::SMALLER_EQ);
            for (int j = 1; j < m_dbm.rows(); j++){
                // if the diagonal intersects the clock axis later than 0, it is tighter than the 0 constraint
                if(m_dbm(j,i) < m_dbm(0,i)){
                    mat(0,i) =  DBMEntry(m_dbm(j,i).first,m_dbm(j,i).second);
                }
            }
        }
        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>(*this);
        res.setDBM(mat);
        return res;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::free(int x) const{
        hypro::matrix_t<DBMEntry> mat =  hypro::matrix_t<DBMEntry>(m_dbm);
        for(int i = 0; i < m_dbm.rows(); i++){
            if (i != x){
                // d_xi = inf
                mat(x,i) = DBMEntry(0.0, BOUND_TYPE::INFTY);

                // d_ix = d_i0
                mat(i,x) = DBMEntry(m_dbm(i,0).first, m_dbm(i,0).second);
            }
        }
        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>(*this);
        res.setDBM(mat);
        return res;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::reset(int x, Number value) const{
        hypro::matrix_t<DBMEntry> mat =  hypro::matrix_t<DBMEntry>(m_dbm);
        for (int i = 0; i < m_dbm.rows();i++){
            // d_xi = (value,<=)+d_0i
            mat(x,i) = DBMEntry(value, BOUND_TYPE::SMALLER_EQ)+m_dbm(0,i);

            // d_ix = d_i0 + (-value, <=)
            mat(i,x) = m_dbm(i,0)+ DBMEntry(-value,BOUND_TYPE::SMALLER_EQ);
        }
        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>(*this);
        res.setDBM(mat);
        return res;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::copy(int src, int dest) const{
        hypro::matrix_t<DBMEntry> mat =  hypro::matrix_t<DBMEntry>(m_dbm);
        for(int i = 0; i < m_dbm.rows(); i++){
            if (i != dest){
                // d_desti = d_srci
                mat(dest,i) = DBMEntry(m_dbm(src,i).first,m_dbm(src,i).second);
                // d_idest = d_isrc
                mat(i,dest) = DBMEntry(m_dbm(i,src).first,m_dbm(i,src).second);
            }
        }
        // d_destsrc = (0,<=)
        mat(dest,src)= DBMEntry(0.0,BOUND_TYPE::SMALLER_EQ);
        // d_srcdest = (0,<=)
        mat(src,dest) = DBMEntry(0.0,BOUND_TYPE::SMALLER_EQ);

        hypro::DifferenceBoundsT<Number,Converter> res = hypro::DifferenceBoundsT<Number,Converter>(*this);
        res.setDBM(mat);
        return res;
    }

    template <typename Number, typename Converter>
    DifferenceBoundsT<Number,Converter> DifferenceBoundsT<Number, Converter>::shift(int x, Number offset) const {
        hypro::matrix_t<DBMEntry> mat = hypro::matrix_t<DBMEntry>(m_dbm);

        for (int i = 0; i < m_dbm.rows(); i++) {
            if (i != x) {
                // d_xi = d_xi+ (offset, <=)
                mat(x, i) = m_dbm(x, i) + DBMEntry(offset, BOUND_TYPE::SMALLER_EQ);

                // d_ix = d_ix + (-offset, <=)
                mat(i, x) = m_dbm(i, x) + DBMEntry(-offset, BOUND_TYPE::SMALLER_EQ);
            }
        }
        //d_x0 = max(d_x0, (0, <=))
        mat(x, 0) = DBMEntry::max(mat(x,0), DBMEntry(0, BOUND_TYPE::SMALLER_EQ));
        //d_0x = min(d_0x, (0, <=))
        mat(0, x) = DBMEntry::min(mat(0,x), DBMEntry(0, BOUND_TYPE::SMALLER_EQ));

        hypro::DifferenceBoundsT<Number, Converter> res = hypro::DifferenceBoundsT<Number, Converter>(*this);
        res.setDBM(mat);
        return res;
    }

    template <typename Number, typename Converter>
    bool DifferenceBoundsT<Number, Converter>::contains( const DifferenceBoundsT<Number,Converter>& _rhs ) const{
        return true;
    }
}

