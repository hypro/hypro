/** 
 * @file   gmpqsupport.h
 * Created on June 29, 2011
 * Last modified July 5, 2011
 * 
 * @author Sebastian Junges
 */
#ifndef GMPQSUPPORT_H
#define	GMPQSUPPORT_H

#include <Eigen/Core>
#include <iostream>
#include <gmpxx.h>

namespace reachLin {
    
    typedef mpq_class rational;
}

namespace Eigen {

    typedef Matrix<reachLin::rational, Dynamic, Dynamic> MatrixXr; 
    typedef Matrix<reachLin::rational, Dynamic, 1> VectorXr;
    
template<> struct NumTraits<reachLin::rational>
{
  typedef reachLin::rational Real;
  typedef reachLin::rational NonInteger;
  typedef reachLin::rational Nested;

  /*
   TODO set costs better.
   */
  enum {
    IsComplex = 0,
    IsInteger = 0,
    IsSigned,
    ReadCost = 2,
    AddCost = 3,
    MulCost = 2,
    RequireInitialization = 1
  };
};

}

// the gmpq is defined in the global namespace.
// therefore, the following ei_* functions *must* be defined
// in the same namespace
inline const reachLin::rational& ei_conj(const reachLin::rational& x)  { return x; }
inline const reachLin::rational& ei_real(const reachLin::rational& x)  { return x; }
inline reachLin::rational ei_imag(const reachLin::rational&)    { return 0; }
inline reachLin::rational ei_abs(const reachLin::rational&  x)  { return abs (x); }
inline reachLin::rational ei_abs2(const reachLin::rational& x)  { return x*x; }
inline reachLin::rational ei_sqrt(const reachLin::rational& x)  { 
    std::cout << "WARNING! SQRT/ not exact.\n";
    return mpq_class(sqrt(x.get_d())); 
}
inline reachLin::rational ei_exp(const reachLin::rational&  x)  {
    std::cout << "WARNING! EXP/ not implemented.\n";
    return 0; 
}
inline reachLin::rational ei_log(const reachLin::rational&  x)  {
    std::cout << "WARNING! log/ not implemented.\n";
    return 0; 
}
inline reachLin::rational ei_sin(const reachLin::rational&  x)  {
    std::cout << "WARNING! sin/ not implemented.\n";
    return 0; 
}
inline reachLin::rational ei_cos(const reachLin::rational&  x)  {
    std::cout << "WARNING! cos/ not implemented.\n";
    return 0; 
}
inline reachLin::rational ei_pow(const reachLin::rational& x, reachLin::rational y)  {
    std::cout << "WARNING! pow/ not implemented.\n";
    return 0; 
}



#endif	/* GMPQSUPPORT_H */

