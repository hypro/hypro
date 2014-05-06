/* 
 * This file contains the additions needed for eigen3 to support our own floating
 * type FLOAT_T.
 * @file   eigenTypetraits.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-02
 * @version 2014-05-02
 */

#pragma once

#include "../config.h"


namespace Eigen
{
    template<> struct NumTraits<number> : GenericNumTraits<number>
    {
        enum
        {
            IsComplex = 0,
            IsInterger = 0,
            ReadCost = 1,
            AddCost = 1,
            MulCost = 1, 
           IsSigned = 1,
            RequireInitialization = 1 // not sure - this indicates that the constructor has to be called
        };

        typedef number Real;
        typedef number NonInteger;
        typedef number Nested;

        static inline Real epsilon() { return Real(0); }
        static inline Real dummy_precision()
        {
            // make sure to override this for floating-point types
            return Real(0);
        }
        static inline number highest() { return number::maxVal(); }
        static inline number lowest()  { return number::minVal(); }


    };
}