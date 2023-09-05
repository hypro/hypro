/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * TPolyTimeEvolutionHandler.h
 *
 * @author Phillip Tse
 * @date 4.10.2019
 */

#pragma once

#include "../IHandler.h"

namespace hypro {

    template<typename State>
    class TPolyTimeEvolutionHandler : public ITimeEvolutionHandler {

        using Number = typename State::NumberType;

    protected:

        State *mState;
        size_t mIndex;
        tNumber mTimeStep;
        matrix_t<Number> mTrafo;
        vector_t<Number> mTranslation;

        //Invariant gotten from Location Invariant Strengthening
        std::optional<vector_t<Number>> mStrengthenedInvariant;

    public:

        TPolyTimeEvolutionHandler() = delete;

        TPolyTimeEvolutionHandler(State *state, size_t index, tNumber timeStep, matrix_t<Number> trafo,
                                  vector_t<Number> translation)
                : mState(state), mIndex(index), mTimeStep(timeStep), mTrafo(trafo), mTranslation(translation),
                  mStrengthenedInvariant(std::nullopt) {}

        ~TPolyTimeEvolutionHandler() {}

        //The set integration approximation from [Sankaranarayanan,2008]
        void handle();

        const char *handlerName() { return "TPolyTimeEvolutionHandler"; }

        bool getMarkedForDelete() { return false; };

        void setMarkedForDelete(bool) { /*no op*/ };

        void setInvariant(const vector_t<Number> &inv);

        std::optional<vector_t<Number>> getRelaxedInvariant() const { return mStrengthenedInvariant; }

        const matrix_t<typename State::NumberType> &getTrafo() const { return mTrafo; }

        const vector_t<typename State::NumberType> &getTranslation() const { return mTranslation; }

    private:

        //Computes the gradient of a multivariate but linear function linearFct
        vector_t<Number> gradientOfLinearFct(const vector_t<Number> &linearFct);

        //Computes the lie derivative given a direction and an affine vector field (aka the flow)
        //NOTE: Usually the lie derivative also works with non linear fcts, but since we cannot parse nonlinear functions yet,
        //we will only use a simple selfwritten derivation function for linear multivariate functions
        //DETAIL: The input vector dir is interpreted as a function, for example if dir = (3 2 -1) then dir is interpreted as 3x + 2y - z,
        //since no constants are allowed.
        //The gradient of 3x + 2y - z is therefore the vector (3 2 -1), which is the result that will be returned.
        vector_t<Number> lieDerivative(const vector_t<Number> &dir);

    };

} // namespace hypro

#include "TPolyTimeEvolutionHandler.tpp"
