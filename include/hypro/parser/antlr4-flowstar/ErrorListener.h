/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * ErrorListener.h
 *
 * A class that takes the exception messages from AnTLR4 and converts them
 * into self defined exceptions. 
 *
 * @author Phillip Tse
 * @date 5.9.2017
 */

#pragma once

#include <stdexcept>
#include <exception>
#include "antlr4-runtime.h"

using namespace antlr4;

namespace hypro {

    class ErrorListener : public antlr4::BaseErrorListener {

    public:

        ErrorListener() {}

        ~ErrorListener() {}

        //The parameters Recognizer*, Token* and std::exception_ptr must stay as this is a function inherited from BaseErrorListener
        void syntaxError(Recognizer *, Token *, size_t line, size_t charPositionInLine, const std::string &msg,
                         std::exception_ptr);

    };

} //namespace hypro
