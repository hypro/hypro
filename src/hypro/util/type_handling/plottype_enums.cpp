/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/util/type_handling/plottype_enums.h"

namespace hypro::plotting {

    PLOTTYPE outputFormat(const std::string &in) {
        if (in == "pdf") return PLOTTYPE::pdf;
        if (in == "png") return PLOTTYPE::png;
        if (in == "eps") return PLOTTYPE::eps;
        if (in == "gen") return PLOTTYPE::gen;
        if (in == "tex") return PLOTTYPE::tex;
        return PLOTTYPE::nset;
    }

    std::string to_string(PLOTTYPE in) {
        if (in == PLOTTYPE::pdf) return "pdf";
        if (in == PLOTTYPE::png) return "png";
        if (in == PLOTTYPE::eps) return "eps";
        if (in == PLOTTYPE::gen) return "gen";
        if (in == PLOTTYPE::tex) return "tex";
        return "";
    }

}  // namespace hypro::plotting
