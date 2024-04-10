#include "eliminate.h"

namespace smtrat::fmplex {
    double test_double() {
        EigenMat<double> m = EigenMat<double>::Zero(2,2);
        EigenVec<double> b = EigenVec<double>::Zero(2);
        eliminate_cols(m,b,{0});
        return 0.0;
    }

    mpq_class test_exact() {
        EigenMat<mpq_class> m = EigenMat<mpq_class>::Zero(2,2);
        EigenVec<mpq_class> b = EigenVec<mpq_class>::Zero(2);
        eliminate_cols(m,b,{0});
        return mpq_class(0);
    }
}