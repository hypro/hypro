/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 17.02.22.
 */

#ifndef HYPRO_MPQ_SERIALIZATION_H
#define HYPRO_MPQ_SERIALIZATION_H

#include <hypro/flags.h>

#ifdef HYPRO_USE_SERIALIZATION

#include "../../types.h"

#include <cereal/types/string.hpp>

namespace cereal {

    template<class Archive>
    void save(Archive &archive,
              mpq_class const &rational) {
        archive(rational.get_str(10));
    }

    template<class Archive>
    void load(Archive &archive,
              mpq_class &rational) {
        std::string stringRepresentation;
        archive(stringRepresentation);
        rational.set_str(stringRepresentation, 10);
    }

}  // namespace cereal

#endif

#endif    // HYPRO_MPQ_SERIALIZATION_H
