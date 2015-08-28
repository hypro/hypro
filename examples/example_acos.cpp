/* 
 * File:   example_acos.cpp
 * Author: Stefan Schupp
 */

#include "../src/lib/config.h"
#include "../src/lib/datastructures/Point.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //carl::FLOAT_T<mpfr_t> value(3);
    //carl::FLOAT_T<mpfr_t> result = 1 / value;
    //result = acos(value);

    hypro::Point<carl::FLOAT_T<mpfr_t>> p({3,4});
   	p.polarCoordinates(hypro::Point<carl::FLOAT_T<mpfr_t>>({0,0}));
    
    /*
    mpfr_t mf1;
    mpfr_t mResult;
    
    mpfr_init(mf1);
    mpfr_init(mResult);
    
    mpfr_set_d(mf1,f1,MPFR_RNDN);
    */

    return 0;
}

