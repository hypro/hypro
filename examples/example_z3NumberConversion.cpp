#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/linearOptimization/z3/z3Context.h"

#include <iostream>
#include <z3++.h>

typedef mpq_class Number;

template <typename Number>
Number testNumberConversion( z3::context& c, z3::ast& resZ3 ) {   
    int64_t* p = new int64_t;
    uint64_t* q = new uint64_t;
    
    Number resNumber;
    if (Z3_get_numeral_int64(c, Z3_get_numerator(c, resZ3), p) && Z3_get_numeral_uint64(c, Z3_get_denominator(c, resZ3), q)){
        std::cout << "Using int64" << std::endl;
        //Try to fit numerator and denomiator into 64-bit (signed/unsigned) ints
        mpq_t resRational;
        mpq_init( resRational );
        mpq_set_si( resRational, *p, *q);
        resNumber = carl::convert<mpq_class, Number>( mpq_class( resRational ) );
        mpq_clear( resRational );
        
        
    } else {
        //Otherwise use a string of arbitary length
        std::cout << "Using string" << std::endl;
        resNumber =  carl::convert<mpq_class, Number>(mpq_class(Z3_get_numeral_string(c,resZ3)));  
        // resNumber = Number(Z3_get_numeral_string(c,resZ3));
    }

    delete p;
    delete q;
    return resNumber;    
}

template <typename Number>
Number power(int exponent, Number base){
    if (exponent > 0){
        return power(exponent - 1, base) * base;    
    } else if (exponent < 0){
        return power(exponent + 1, base) / base;
    }
    return 1;
}

void numberConversionPowersOfTwo(int highestPower = 10){
    hypro::z3Context c; 
    Number base(2);
    for (int exponent = -highestPower; exponent <= highestPower; exponent++ ){
        Number po = power<Number>(exponent, base);
        z3::expr number = c.real_val( po );
        Number result = testNumberConversion<Number>(c, number);
        std::cout << "Exponent: "
                  << exponent
                  << "\nPower: "
                  << po
                  << "\nz3::expr: "
                  << number
                  << "\nExpression to number: "
                  << result
                  << std::endl;
    }
}

void numberConversionPowerOfTwo(int ex = 10){
    hypro::z3Context c; 
    Number base(2);
    Number po = power<Number>(ex, base);
    z3::expr number = c.real_val( po );
    Number result = testNumberConversion<Number>(c, number);
    std::cout << "Conversion of " << " 2^" << ex << "=\n" << po << "\n\n" << number << "\n\n" << result << "\n------------------------------\n"<< std::endl;
}

int main() {
    int maxExponent;
    std::cin >> maxExponent;
    numberConversionPowersOfTwo(maxExponent);
    // numberConversionPowerOfTwo(maxExponent);
    return 0;
}