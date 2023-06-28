/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 18.03.22.
 */

#ifndef HYPRO_COLORS_H
#define HYPRO_COLORS_H

#include <cstddef>

namespace hypro::plotting {

/**
 * Enum required for referencing colors in the color array.
 */
    enum {
        petrol = 0,
        turquoise,
        green,
        maygreen,
        orange,
        red,
        bordeaux,
        violett,
        lila,
        blue
    };
/**
 * Color array holding a set of colors.
 */
    const std::size_t colors[] = {0x006165, 0x0098A1, 0x57AB27, 0xBDCD00, 0xF6A800,
                                  0xCC071E, 0xA11035, 0x612158, 0x7A6FAC, 0x00549F};

}  // namespace hypro::plotting

#endif    // HYPRO_COLORS_H
