#include "../src/lib/config.h"
#include "../src/lib/util/eigenTypetraits.h"

int main(int argc, char** argv) {
    typedef Eigen::Matrix<carl::FLOAT_T<double>, Eigen::Dynamic, Eigen::Dynamic> mpfr_matrix;
    
    mpfr_matrix test1;

}



