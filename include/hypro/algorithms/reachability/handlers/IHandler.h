/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/HybridAutomaton/State.h"
#include "../../../types.h"

namespace hypro {

    class IHandler {
    public:
        virtual void handle() = 0;

        virtual const char *handlerName() = 0;
    };

    template<typename State>
    class IFirstSegmentHandler : public IHandler {
    public:
        virtual ~IFirstSegmentHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;

        virtual const flowVariant<typename State::NumberType> &getTransformation() const = 0;
    };

    class IInvariantHandler : public IHandler {
    public:
        virtual ~IInvariantHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;

        // provides information whether the handlers set fullfils containment conditions (eg. invariant)
        virtual CONTAINMENT getContainment() = 0;

        virtual bool getMarkedForDelete() = 0;

        virtual void setMarkedForDelete(bool toDelete) = 0;
    };

    class IBadStateHandler : public IHandler {
    public:
        virtual ~IBadStateHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;

        // provides information whether the handlers set intersects its bad states
        virtual bool intersectsBadState() = 0;

        virtual bool getMarkedForDelete() = 0;

        virtual void setMarkedForDelete(bool toDelete) = 0;
    };

    template<typename State>
    class IGuardHandler : public IHandler {
    public:
        virtual ~IGuardHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;

        // provides information whether the handlers set intersects the transitions guard
        virtual bool satisfiesGuard() = 0;

        virtual std::shared_ptr<State> getState() = 0;

        virtual void setState(std::shared_ptr<State> ptr) = 0;

        virtual void reinitialize() = 0;

        virtual double getSortIndex() = 0;

        virtual void setSortIndex(double sortIndex) = 0;

        virtual bool getMarkedForDelete() = 0;

        virtual void setMarkedForDelete(bool toDelete) = 0;
    };

    class ITimeEvolutionHandler : public IHandler {
    public:
        virtual ~ITimeEvolutionHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;

        virtual bool getMarkedForDelete() = 0;

        virtual void setMarkedForDelete(bool toDelete) = 0;
    };

    class IResetHandler : public IHandler {
    public:
        virtual ~IResetHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;
    };

    class IJumpHandler : public IHandler {
    public:
        virtual ~IJumpHandler() {}

        virtual void handle() = 0;

        virtual const char *handlerName() = 0;
    };
}  // namespace hypro
