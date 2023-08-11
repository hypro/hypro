/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *	TemplatePolyhedronContext.h
 *
 *	The overall reachability algorithm for template polyhedra according to the paper from
 *	Sankaranarayanan 2008.
 *	NOTE: The state template here is guaranteed to have the TemplatePolyhedron class
 *	as underlying set representation.
 *
 *	@author Phillip Tse
 *	@date 17.9.2019
 */

#pragma once

#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/SettingsProvider.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../../../util/statistics/statistics.h"
#include "../handlers/HandlerFactory.h"
#include "../handlers/IHandler.h"
#include "../workers/IWorker.h"
#include "Exceptions.h"
#include "LTIContext.h"

namespace hypro {

    template<typename State>
    class TemplatePolyhedronContext : public LTIContext<State> {
        using Number = typename State::NumberType;

    private:
        // Used for minimization of various functions during location invariant strengthening
        Optimizer<Number> mOptimizer;

        // If location invariant strenghtening is used, then the strengthened invariant is saved.
        // The result of the location invariant strengthening. Is passed to TPolyFirstSegmentHandler and TPolyTimeEvolutionHandler.
        // TODO: If we could save info between flowpipes, we could save us a lot more LPs.
        //- If we could save the relaxed invariant for a location, then we could refine it if we get to the same location again.
        //- We could directly build the overapproximated form, since we saved the fitting invariant to the matrix
        std::optional<vector_t<Number>> mStrengthenedInvariant;

        // Offset vector of invariants after overapproximation by template
        // Used to restore invariant offsets after completed flowpipe computation for this location
        std::optional<vector_t<Number>> mOverapproxedInvariant;

        // Constant scaling factor needed for all major algorithms in this context.
        const Number mScaling = 3;

    public:
        TemplatePolyhedronContext() = delete;

        TemplatePolyhedronContext(
                const std::shared_ptr<Task<State>> &t,
                const Strategy<State> &strat,
                WorkQueue<std::shared_ptr<Task<State>>> *localQueue,
                WorkQueue<std::shared_ptr<Task<State>>> *localCEXQueue,
                Flowpipe<State> &localSegments,
                ReachabilitySettings &settings)
                : LTIContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings),
                  mOptimizer(Optimizer<Number>()), mStrengthenedInvariant(std::nullopt) {}

        ~TemplatePolyhedronContext() {}

        // Changes template matrix content according to setting and then call locationInvariantStrengthening
        void execBeforeFirstSegment() override;

        // First Segment computation after Sankaranarayanan
        void firstSegment() override;

        // Continuous Evolution after Sankaranarayanan
        void applyContinuousEvolution() override;

        // Set back invariant to overapproximated form, since LIS fits invariants to flowpipe
        void execBeforeProcessDiscreteBehavior() override;

        // Computes the gradient of a multivariate linear function linearFct
        // DETAIL: Vector (3 2 -1 4) represents 3x+2y-z+4 and its gradient is (3 2 -1 0)
        vector_t<Number> gradientOfLinearFct(const vector_t<Number> &linearFct);

        // Computes the lie derivative given by a linear function and an affine vector field (aka the flow).
        // NOTE: Usually the lie derivative also works with nonlinear functions, but since we cannot parse nonlinear functions yet,
        // we will only use a simple selfwritten derivation function for linear multivariate functions
        // Here The input vector dir is interpreted as a function without a dimensionless coefficient.
        // For example if dir = (3 2 -1) then dir is interpreted as 3x + 2y - z,
        std::pair<vector_t<typename State::NumberType>, typename State::NumberType>
        lieDerivative(const vector_t<Number> &dir);

        // Also computes the lie derivative given by a linear function and an affine vector field (aka the flow).
        // DETAIL: The input vector dir is interpreted as a function with dimensionless coefficient.
        // For example if dir = (3 2 -1) then dir is interpreted as 3x + 2y - 1,
        std::pair<vector_t<typename State::NumberType>, typename State::NumberType>
        lieDerivativeExtended(const vector_t<Number> &dir);

        // Conducts the location invariant strengthening method from Sankranarayanan 2008.
        // Only works for closed invariants where the normals point into the inside.
        // Until it converges, a relaxed bound for the invariants is being computed, thereby shrinking in the region of possible values (strengthening).
        // Returns the relaxed bounds for the invariants.
        vector_t<Number> locationInvariantStrengthening(const TemplatePolyhedron<Number> &invTPpoly,
                                                        const vector_t<Number> &initialOffsets);

        // Adds invariants, guards and bad states to the template matrix according the the setting
        // TemplatePolyhedron<Number> createTemplateContent(const TemplatePolyhedron<Number>& tpoly);
        template<typename Setting>
        TemplatePolyhedronT<typename State::NumberType, hypro::Converter<Number>, Setting>
        createTemplateContent(const TemplatePolyhedronT<Number, hypro::Converter<Number>, Setting> &tpoly);

        // Tests whether the given tpoly is a positive invariant wrt to invVector
        bool isPositiveInvariant(const TemplatePolyhedron<Number> &tpoly, const vector_t<Number> &invVector);

        // Tests whether the given tpoly is a relaxed invariant wrt to invVector
        bool isRelaxedInvariant(const TemplatePolyhedron<Number> &tpoly, const vector_t<Number> &invVector);
    };

}  // namespace hypro

#include "TemplatePolyhedronContext.tpp"
