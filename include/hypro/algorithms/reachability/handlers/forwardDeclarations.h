/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
namespace hypro {

// forward declarations
    template<typename State>
    class ltiFirstSegmentHandler;

    template<typename State>
    class rectangularFirstSegmentHandler;

    template<typename State>
    class timedElapseFirstSegmentHandler;

    template<typename State>
    class timedFirstSegmentHandler;

    template<typename State>
    class TPolyFirstSegmentHandler;

    template<typename State>
    class discreteInvariantHandler;

    template<typename State>
    class ltiInvariantHandler;

    template<typename State>
    class rectangularInvariantHandler;

    template<typename State>
    class timedInvariantHandler;

// template<typename State>
// class TPolyInvariantHandler;
    template<typename State>
    class discreteBadStateHandler;

    template<typename State>
    class ltiBadStateHandler;

    template<typename State>
    class rectangularBadStateHandler;

    template<typename State>
    class timedBadStateHandler;

// template<typename State>
// class TPolyBadstateHandler;
    template<typename State>
    class discreteGuardHandler;

    template<typename State>
    class ltiGuardHandler;

    template<typename State>
    class rectangularGuardHandler;

    template<typename State>
    class timedGuardHandler;

// template<typename State>
// class TPolyGuardHandler;
    template<typename State>
    class ltiTimeEvolutionHandler;

    template<typename State>
    class rectangularTimeEvolutionHandler;

    template<typename State>
    class timedElapseTimeEvolutionHandler;

    template<typename State>
    class timedElapseAfterTickTimeEvolutionHandler;

    template<typename State>
    class timedTickTimeEvolutionHandler;

    template<typename State>
    class TPolyTimeEvolutionHandler;

    template<typename State>
    class ltiResetHandler;

    template<typename State>
    class rectangularResetHandler;

    template<typename State>
    class timedResetHandler;

    template<typename State>
    class ltiJumpHandler;

    template<typename State>
    class rectangularJumpHandler;
// template<typename State>
// class TPolyResetHandler;

}  // namespace hypro
