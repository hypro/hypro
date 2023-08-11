/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.09.22.
 */

#ifndef HYPRO_ADAPTIONS_NUMBERS_H
#define HYPRO_ADAPTIONS_NUMBERS_H

#include "adaptions_carl.h"

#include <hypro/flags.h>

namespace hypro {

    template<typename Number>
    Number getDenominator(const Number &in) {
#ifdef CARL_OLD_STRUCTURE
        return carl::getDenom( in );
#else
        return carl::get_denom(in);
#endif
    }

    template<typename Number>
    Number getNumerator(const Number &in) {
#ifdef CARL_OLD_STRUCTURE
        return carl::getNum( in );
#else
        return carl::get_num(in);
#endif
    }

    template<typename Number>
    bool isInteger(const Number &in) {
#ifdef CARL_OLD_STRUCTURE
        return carl::isInteger( in );
#else
        return carl::is_integer(in);
#endif
    }

    template<typename Number>
    double toDouble(const Number &in) {
#ifdef CARL_OLD_STRUCTURE
        return carl::toDouble( in );
#else
        return carl::to_double(in);
#endif
    }

#ifdef CARL_OLD_STRUCTURE
    template <typename Number>
    using is_rational = carl::is_rational<Number>;
#else
    template<typename Number>
    using is_rational = carl::is_rational_type<Number>;
#endif

#ifdef CARL_OLD_STRUCTURE
    template <typename Number>
    using is_float = carl::is_float<Number>;
#else
    template<typename Number>
    using is_float = carl::is_float_type<Number>;
#endif

}  // namespace hypro

#endif    // HYPRO_ADAPTIONS_NUMBERS_H
