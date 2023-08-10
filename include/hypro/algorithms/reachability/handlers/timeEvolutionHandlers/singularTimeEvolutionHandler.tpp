/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "singularTimeEvolutionHandler.h"
//#define SINGULAR_TIME_EVOL_USE_MINKOWSKI

namespace hypro {
    template<typename StateSet>
    StateSet singularApplyTimeEvolution(const StateSet &initialSet,
                                        const std::vector<Point<typename StateSet::NumberType>> &flowVertices) {
        using Number = typename StateSet::NumberType;
        VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope(initialSet);
        VPolytope<Number> flowSetPolytope{flowVertices};
        VPolytope<Number> timeElapsePolytope{initSetPolytope.vertices()};
        // set rays
        auto combinedRays = initSetPolytope.rays();
        // add rays from flow set
        combinedRays.insert(flowSetPolytope.rays().begin(), flowSetPolytope.rays().end());
        // add rays originating to vertices of the flow set
        std::for_each(flowSetPolytope.vertices().begin(), flowSetPolytope.vertices().end(), [&](const auto &point) {
            combinedRays.insert(point.rawCoordinates());
        });

        timeElapsePolytope.setRays(combinedRays);

        // Convert back
        StateSet timeElapse;
        convert(timeElapsePolytope, timeElapse);
        return timeElapse;
    }

    template<typename StateSet>
    StateSet singularApplyBoundedTimeEvolution(const StateSet &initialSet,
                                               const std::vector<Point<typename StateSet::NumberType>> &flowVertices,
                                               tNumber timeBound) {
// todo: this doesn't work if hpolytopes are used. If vpolytopes are used (no conversion of flowShiftVPol), the approach works
// todo: make this representation-dependent and use minkowski directly
#ifdef SINGULAR_TIME_EVOL_USE_MINKOWSKI
        using Number = typename StateSet::NumberType;
        HPolytope<Number> initSetHPol = hypro::Converter<Number>::toHPolytope( initialSet );
        VPolytope<Number> flowShiftVPol( { carl::convert<tNumber, Number>( timeBound ) * flowVertices[0], Point<Number>::Zero( initSetHPol.dimension() ) } );
        HPolytope<Number> flowShiftHPol = hypro::Converter<Number>::toHPolytope( flowShiftVPol );

        auto timeElapseHPol = initSetHPol.minkowskiSum( flowShiftHPol );
        StateSet timeElapse;
        convert( timeElapseHPol, timeElapse );
        timeElapse.removeRedundancy();
        return timeElapse;

#else
        using Number = typename StateSet::NumberType;
        VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope(initialSet);
        VPolytope<Number> flowSetPolytope{flowVertices};
        VPolytope<Number> timeElapsePolytope{initSetPolytope.vertices()};
        // process rays: bound time, create new vertices
        typename VPolytope<Number>::pointVector newVertices;

        auto combinedRays = initSetPolytope.rays();
        // add rays from flow set
        combinedRays.insert(flowSetPolytope.rays().begin(), flowSetPolytope.rays().end());
        // add rays originating from vertices of the flow set
        std::for_each(flowSetPolytope.vertices().begin(), flowSetPolytope.vertices().end(), [&](const auto &point) {
            combinedRays.insert(point.rawCoordinates());
        });

        for (const auto &vertex: initSetPolytope.vertices()) {
            for (const auto &ray: combinedRays) {
                newVertices.emplace_back(
                        Point<Number>(vertex.rawCoordinates() + carl::convert<tNumber, Number>(timeBound) * ray));
            }
        }

        // update vertices
        timeElapsePolytope.insert(newVertices.begin(), newVertices.end());

        assert(timeElapsePolytope.rays().empty());

        // Convert back
        StateSet timeElapse;
        convert(timeElapsePolytope, timeElapse);
        timeElapse.removeRedundancy();
        return timeElapse;
#endif
    }

}  // namespace hypro
