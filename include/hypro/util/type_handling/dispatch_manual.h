/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../representations/Box/BoxSetting.h"
#include "../../representations/GeometricObjectBase.h"
#include "representation_enums.h"
#include "settings_enums.h"

#include <assert.h>

namespace hypro {

/**
 * @brief
 * @detail  Example usage: see example_dispatch.cpp
 */
    template<typename Number, typename Converter, typename Callable, typename... Args>
    auto dispatch(representation_name representation, int setting, Callable func, Args... args) {
        switch (representation) {
            case representation_name::box:
                switch (static_cast<boxSetting_name>( setting )) {
                    case boxSetting_name::BoxLinearOptimizationOn:
                        return func.template operator()<BoxT<Number, Converter, BoxLinearOptimizationOn>>(args...);
                    case boxSetting_name::BoxAllOff:
                        return func.template operator()<BoxT<Number, Converter, BoxLinearOptimizationOn>>(args...);
                }
        }
        assert(false);
    }
}  // namespace hypro
