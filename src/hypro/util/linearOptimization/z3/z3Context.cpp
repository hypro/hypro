/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/flags.h>

#ifdef HYPRO_USE_Z3
#include "hypro/util/linearOptimization/z3/z3Context.h"
namespace hypro {
z3::expr z3Context::real_val( mpq_class val ) {
    std::string valStr = val.get_str();
    assert( z3::context::real_val( valStr.c_str() ).is_real() );
    return z3::context::real_val( valStr.c_str() );	 // hack for now
                                                     // problem: z3 wraps mpq using a "rational" class. we can't directly use mpq_class but need the value of mpq_class. There is no
                                                     // public member function doing this
}
}  // namespace hypro
#endif
