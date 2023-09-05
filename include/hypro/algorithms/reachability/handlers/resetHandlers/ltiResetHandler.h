/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../IHandler.h"

namespace hypro {
    template<typename State>
    class ltiResetHandler : public IResetHandler {
        using Number = typename State::NumberType;

    protected:
        State *mState;    // A state containing the first segment for each subspace
        matrix_t<Number> mTrafo;
        vector_t<Number> mTranslation;

        size_t mIndex;

    public:
        ltiResetHandler() = delete;

        ltiResetHandler(State *state, size_t index, matrix_t<Number> trafo, vector_t<Number> translation) {
            mState = state;
            mIndex = index;
            mTrafo = trafo;
            mTranslation = translation;
        }

        void handle();

        const char *handlerName() { return "ltiResetHandler"; }
    };
}  // namespace hypro

#include "ltiResetHandler.tpp"
