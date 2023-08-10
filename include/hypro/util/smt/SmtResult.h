/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 12.07.22.
 */

#ifndef HYPRO_SMTRESULT_H
#define HYPRO_SMTRESULT_H

#include <iostream>

namespace hypro {

    struct SmtResult {
        bool sat;  ///< True, if the formula was satisfiable

        explicit operator bool() const { return sat; }
    };

    inline std::ostream &operator<<(std::ostream &out, const SmtResult &in) {
        switch (in.sat) {
            case true:
                out << "sat";
                break;
            case false:
                out << "unsat";
                break;
        }
        return out;
    }

}  // namespace hypro

#endif    // HYPRO_SMTRESULT_H
