/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/util/type_handling/settings_enums.h"

#include "hypro/representations/GeometricObjectBase.h"

#include <cassert>

namespace hypro {

/// Recursive call of string to setting enum conversion
    template<class Enum, class... Enums>
    struct stringToSetting_Impl {
        static int toSetting(const std::string &name) {
            auto result = Enum::_from_string_nothrow(name.c_str());
            if (result) return result->_to_integral();
            return stringToSetting_Impl<Enums...>::toSetting(name);
        }
    };

/// Base case of string to setting enum conversion
    template<class Enum>
    struct stringToSetting_Impl<Enum> {
        static int toSetting(const std::string &name) {
            auto result = Enum::_from_string_nothrow(name.c_str());
            if (result) return result->_to_integral();
            assert(false && "No enum was matched.");
            return -1;
        }
    };

    int stringToSetting(const std::string &name) {
        return stringToSetting_Impl<
                boxSetting_name,
                supportFunctionSetting_name,
                sfnSetting_name,
                hPolytopeSetting_name,
                vPolytopeSetting_name,
                carlPolytopeSetting_name,
                tpolySetting_name,
                StarsetSetting_name>::toSetting(name);
    }

}  // namespace hypro
