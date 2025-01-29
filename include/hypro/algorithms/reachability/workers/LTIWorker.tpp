/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTIWorker.h"

namespace hypro {

    template<typename Representation, typename HybridAutomaton>
    template<typename OutputIt>
    REACHABILITY_RESULT
    LTIWorker<Representation, HybridAutomaton>::computeTimeSuccessors(const Representation &initialSet,
                                                                      LocationT const *loc, OutputIt out,
                                                                      long int segmentsToCompute,
                                                                      bool checkSafety, std::optional<OutputIt> outUnderApprox, 
                                                                      const Representation & initialSetUnder ) const {

        if (segmentsToCompute < 0) {
            segmentsToCompute = mNumSegments;
        } else if (segmentsToCompute == 0) {
            DEBUG("hypro.reachability",
                  "No segments to compute (reached global time horizon, segmentsToCompute == 0), return.");
            return REACHABILITY_RESULT::SAFE;
        }

        Representation firstSegment;
        Representation firstSegmentUnder;
        if (mSettings.underapproxReach) {
            
            firstSegment = constructFirstSegments(initialSet, loc->getLinearFlow(mSubspace),
                                                            mTrafoCache.getTransformation(loc, mSettings.timeStep,
                                                                                          mSubspace).fullMatrix,
                                                            mSettings.timeStep, false);


            // minkowski diff is only implemented for HPoly (at least so far)
            if constexpr (std::is_same<Representation, HPolytope<Number>>::value) {
                firstSegmentUnder = constructFirstSegments(initialSetUnder, loc->getLinearFlow(mSubspace),
                                            mTrafoCache.getTransformation(loc, mSettings.timeStep,
                                                                            mSubspace).fullMatrix,
                                            mSettings.timeStep, true);
            }





        } else {
            firstSegment = constructFirstSegment(initialSet, loc->getLinearFlow(mSubspace),
                                                            mTrafoCache.getTransformation(loc, mSettings.timeStep,
                                                                                          mSubspace).fullMatrix,
                                                            mSettings.timeStep);
        }

        std::cout << initialSet << std::endl;

        std::cout << "after construct first segment" << firstSegment << std::endl;

        auto [containment, segment] = intersect(firstSegment, loc->getInvariant(), mSubspace);
        // If the first segment did not fulfill the invariant of the location, the jump here should not have been made
        if (containment == CONTAINMENT::NO) {
            DEBUG("hypro.reachability",
                  "First segment is not contained in the invariant, abort time successor computation.");
            return REACHABILITY_RESULT::SAFE;
        }
        // insert segment
        *out = segment;
        ++out;

        // need the declaration, because it get's assigned inside the if, and after leaving the scope segmentUnder no longer exists
        Representation segmentUnder;
        if (mSettings.underapproxReach && outUnderApprox.has_value()) {
            // if the over-approximation of the segment is in the invariant, than the under-approximation should be also there
            std::tie (std::ignore, segmentUnder) = intersect(firstSegmentUnder, loc->getInvariant(), mSubspace);
            *(outUnderApprox.value()) = segmentUnder;
            ++(outUnderApprox.value());   
        }


        // intersect with badstates
        // if the over-approximation doesn't intersect the bad state, also the under-approximation will not, so there is no point in checking it
        if (checkSafety) {
            std::tie(containment, std::ignore) = ltiIntersectBadStates(segment, loc, mHybridAutomaton, mSubspace);
            if (containment != CONTAINMENT::NO) {
                // Todo: memorize the intersecting state set and keep state.
                DEBUG("hypro.reachability", "First segment intersects the set of bad states, terminate.");
                return REACHABILITY_RESULT::UNKNOWN;
            }
        }
 
        std::cout << "apply linear transform" << std::endl;


        // while not done
        for (size_t segmentCount = 1; segmentCount < (std::size_t) segmentsToCompute; ++segmentCount) {
            std::cout << std::endl << "segmentCount = " << segmentCount << std::endl;

            segment = applyTimeEvolution(segment, mTrafoCache.getTransformation(loc, mSettings.timeStep, mSubspace));
            std::cout << "After apply time evolution " <<std::endl;
#ifdef HYPRO_LOGGING
            auto tmp = segment;
#endif
            std::cout << "Before intersect " <<std::endl;
            std::cout << "segment" << segment << std::endl;
            std::cout << "inv" << loc->getInvariant() << std::endl;
            std::tie(containment, segment) = intersect(segment, loc->getInvariant(), mSubspace);
            std::cout << "After intersect evolution " << std::endl;
            if (containment == CONTAINMENT::NO) {
#ifdef HYPRO_LOGGING
                DEBUG("hypro.reachability",
                      "Segment no " << segmentCount << ", which is " << tmp << " invalidates the invariant condition.");
                DEBUG("hypro.reachability", "Compute time successor states done.");
#endif
                return REACHABILITY_RESULT::SAFE;
            }

            std::cout << "saving segment " << std::endl;
            *out = segment;
            ++out;

            if (mSettings.underapproxReach && outUnderApprox.has_value()) {
                std::cout << "apply time evolution to under-approx"  << std::endl;
                segmentUnder = applyTimeEvolution(segmentUnder, mTrafoCache.getTransformation(loc, mSettings.timeStep, mSubspace));
                // if the over-approximation of the segment is in the invariant, than the under-approximation should be also there
                std::tie(std::ignore, segmentUnder) = intersect(segmentUnder, loc->getInvariant(), mSubspace);
                
                *(outUnderApprox.value()) = segmentUnder;
                ++(outUnderApprox.value()); 
            }



            // intersect with badstates
            if (checkSafety) {
                std::tie(containment, std::ignore) = ltiIntersectBadStates(segment, loc, mHybridAutomaton, mSubspace);
                if (containment != CONTAINMENT::NO) {
                    // Todo: memorize the intersecting state set and keep state.
                    DEBUG("hypro.reachability",
                          "Segment " << segment << " intersects the set of bad states, terminate.");
                    DEBUG("hypro.reachability", "Compute time successor states done.");
                    return REACHABILITY_RESULT::UNKNOWN;
                }
            }
        }
        DEBUG("hypro.reachability", "Compute time successor states done.");
        return REACHABILITY_RESULT::SAFE;
    }

    template<typename Representation, typename HybridAutomaton>
    auto LTIWorker<Representation, HybridAutomaton>::getJumpSuccessors(std::vector<Representation> const &flowpipe,
                                                                       Transition<LocationT> const *transition) const -> JumpSuccessorGen {
        std::size_t blockSize = 1;
        if (mSettings.aggregation == AGG_SETTING::AGG ||
            (mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG)) {
            if (mSettings.clustering > 0) {
                blockSize = (flowpipe.size() + mSettings.clustering) / mSettings.clustering;    // division rounding up
            } else {
                blockSize = flowpipe.size();
            }

        } else if (mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG) {
            if (transition->getAggregation() == AGG_SETTING::CLUSTERING) {
                blockSize = (blockSize + transition->getClusterBound()) /
                            transition->getClusterBound();    // division rounding up
            }
        }
        return JumpSuccessorGen{flowpipe, transition, blockSize};
    }

    template<typename Representation, typename HybridAutomaton>
    struct LTIWorker<Representation, HybridAutomaton>::EnabledSegmentsGen {
        std::vector<Representation> const *flowpipe;
        Transition<LocationT> const *transition;
        std::size_t current = 0;

        EnabledSegmentsGen(std::vector<Representation> const *flowpipe, Transition<LocationT> const *transition)
                : flowpipe(flowpipe), transition(transition) {}

        std::optional<std::pair<std::vector<Representation>, SegmentInd>> next() {
            std::vector<Representation> enabledSegments{};

            SegmentInd firstEnabled{};

            // find next enabled segment
            for (; current < flowpipe->size(); ++current) {
                auto [containment, intersected] = intersect((*flowpipe)[current], transition->getGuard());
                if (containment != CONTAINMENT::NO) {
                    enabledSegments.push_back(intersected);
                    firstEnabled = SegmentInd(current);
                    break;
                }
            }

            // collect enabled segments
            for (current += 1; current < flowpipe->size(); ++current) {
                auto [containment, intersected] = intersect((*flowpipe)[current], transition->getGuard());
                if (containment == CONTAINMENT::NO) break;
                enabledSegments.push_back(intersected);
            }

            if (enabledSegments.empty()) return std::nullopt;
            return std::pair{enabledSegments, firstEnabled};
        }
    };

    template<typename Representation, typename HybridAutomaton>
    struct LTIWorker<Representation, HybridAutomaton>::AggregatedGen {
        size_t segmentsPerBlock{};
        std::vector<Representation> *enabled{};
        std::size_t firstEnabled{};
        std::size_t current = 0;

        AggregatedGen(size_t segmentsPerBlock, std::vector<Representation> &enabled, SegmentInd firstEnabled)
                : segmentsPerBlock(segmentsPerBlock), enabled(&enabled), firstEnabled(firstEnabled) {}

        AggregatedGen(size_t segmentsPerBlock, std::pair<std::vector<Representation>, SegmentInd> &p)
                : AggregatedGen(segmentsPerBlock, p.first, p.second) {}

        std::optional<std::pair<Representation, carl::Interval<SegmentInd>>> next() {
            if (current == enabled->size()) return std::nullopt;
            Representation aggregated = (*enabled)[current];
            SegmentInd indexFirst = SegmentInd(firstEnabled + current);  // flowpipe ind of first aggregated segment
            current += 1;
            for (size_t inBlock = 1; inBlock < segmentsPerBlock && current < enabled->size(); ++inBlock, ++current) {
                aggregated.unite((*enabled)[current]);
            }
            return std::pair{aggregated, carl::Interval<SegmentInd>{indexFirst, SegmentInd(firstEnabled + current)}};
        }
    };

    template<typename Representation, typename HybridAutomaton>
    struct LTIWorker<Representation, HybridAutomaton>::JumpSuccessorGen {
        std::optional<std::pair<std::vector<Representation>, SegmentInd>> mEnabledRange = std::pair<std::vector<Representation>, SegmentInd>{};

        size_t mSegmentsPerBlock{};
        Transition<LocationT> const *mTransition;

        EnabledSegmentsGen mEnabled;
        AggregatedGen mAggregated;

    public:
        JumpSuccessorGen(std::vector<Representation> const &flowpipe, Transition<LocationT> const *transition,
                         size_t segmentsPerBlock)
                : mSegmentsPerBlock(segmentsPerBlock), mTransition(transition), mEnabled(&flowpipe, transition),
                  mAggregated(segmentsPerBlock, *mEnabledRange) {}

        std::optional<std::pair<Representation, carl::Interval<SegmentInd>>> next() {
            while (true) {
                auto agg = mAggregated.next();

                while (!agg) {
                    mEnabledRange = mEnabled.next();
                    if (!mEnabledRange) return std::nullopt;
                    mAggregated = AggregatedGen{mSegmentsPerBlock, *mEnabledRange};
                    agg = mAggregated.next();
                }

                agg->first = applyReset(agg->first, mTransition->getReset());
                CONTAINMENT containment;
                std::tie(containment, agg->first) = intersect(agg->first, mTransition->getTarget()->getInvariant());

                if (containment != CONTAINMENT::NO) {
                    agg->first.reduceRepresentation();
                    return agg;
                }
            }
        }
    };

    template<typename Representation, typename Location>
    std::string print(std::vector<EnabledSetsUnderOver<Representation, Location>> const &pipes) {
        std::stringstream str{};

        for (auto &pipe: pipes) {
            for (auto &indSet: pipe.valuationSets) {
                str << "[" << indSet.index << "] " << indSet.valuationSet << " ";
            }
            str << "\n";
        }
        str << "\n";

        return str.str();
    }

    template<typename Representation, typename Location>
    std::string print(std::vector<JumpSuccessor<Representation, Location>> const &pipes) {
        std::stringstream str{};

        for (auto &pipe: pipes) {
            if (!pipe.valuationSets.empty()) {
                for (auto &indSet: pipe.valuationSets) {
                    str << "[" << indSet.time << "] " << indSet.valuationSet << " ";
                }
                str << "\n";
            }
        }
        str << "\n";

        return str.str();
    }

    template<typename Representation, typename HybridAutomaton>
    std::string print(std::vector<Representation> const &sets) {
        std::stringstream str{};
        for (auto &set: sets) {
            if (!set.empty()) {
                str << set << "; ";
            }
        }
        auto resultString = str.str();
        str.str("");
        return resultString;
    }

    template<typename Representation, typename HybridAutomaton>
    std::vector<JumpSuccessor<Representation, typename HybridAutomaton::LocationType>>
    LTIWorker<Representation, HybridAutomaton>::computeJumpSuccessors(std::vector<Representation> const &flowpipe,
                                                                      LocationT const *loc, std::vector<Representation> const &flowpipeUnderApprox) const {
        // TRACE( "hypro.reachability", "flowpipe: " << print( flowpipe ) );

        // transition x enabled segments, segment ind
        std::vector<EnabledSetsUnderOver<Representation, typename HybridAutomaton::LocationType>> enabledSegments{};

        TRACE("hypro.reachability", "Find non-empty guard intersections");
        for (const auto &transition: loc->getTransitions()) {
            TRACE("hypro.reachability", "Consider transition " << (*transition.get()));
            auto &currentSucc = enabledSegments.emplace_back(
                    EnabledSetsUnderOver<Representation, typename HybridAutomaton::LocationType>{transition.get()});

            SegmentInd cnt = 0;
            auto itUnderApprox = flowpipeUnderApprox.begin();

            for (auto const &valuationSet: flowpipe) {
                auto [containment, intersected] = intersect(valuationSet, transition->getGuard());
                if (containment != CONTAINMENT::NO) {
                    currentSucc.valuationSets.push_back({intersected, cnt});
                }


                if (mSettings.underapproxReach) {
                    auto [containment, intersectedUnder] = intersect(*itUnderApprox, transition->getGuard());

                    if (containment != CONTAINMENT::NO) {
                        currentSucc.valuationSetsUnder.push_back({intersectedUnder, cnt});
                    }
                    ++itUnderApprox;
                } else {
                    // if we don't do under-approximation then the rest of the code will work with empty objects
                    currentSucc.valuationSetsUnder.push_back({});
                }

                ++cnt;

            }
        }

        TRACE("hypro.reachability", "Guard-enabling segments: " << print(enabledSegments));

        std::vector<JumpSuccessor<Representation, typename HybridAutomaton::LocationType>> successors{};

        // aggregation
        // for each transition
        for (auto &[transition, valuationSets, valuationSetsUnder]: enabledSegments) {
            // no aggregation
            std::size_t blockSize = 1;
            if (mSettings.aggregation == AGG_SETTING::AGG ||
                (mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG)) {
                if (mSettings.clustering > 0) {
                    blockSize = (valuationSets.size() + mSettings.clustering) /
                                mSettings.clustering;     // division rounding up
                } else {
                    blockSize = valuationSets.size();
                }

            } else if (mSettings.aggregation == AGG_SETTING::MODEL &&
                       transition->getAggregation() != AGG_SETTING::NO_AGG) {
                if (transition->getAggregation() == AGG_SETTING::CLUSTERING) {
                    blockSize = (blockSize + transition->getClusterBound()) /
                                transition->getClusterBound();    // division rounding up
                }
            }
            if (mSettings.underapproxReach) {
                successors.emplace_back(JumpSuccessor<Representation, typename HybridAutomaton::LocationType>{transition,
                                                                                                            aggregate( blockSize, valuationSets),
                                                                                                            aggregate( blockSize, valuationSetsUnder) 
                                                                                                          });
            } else {
                successors.emplace_back(JumpSuccessor<Representation, typename HybridAutomaton::LocationType>{transition,
                                                                                                            aggregate( blockSize, valuationSets),
                                                                                                            {} 
                                                                                                          });
            }
            // TRACE( "hypro.reachability", transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << ", " << transition->getReset() << ":\nenabledSegments after aggregation: " << print( successors ) << "\n" );
        }
        // DEBUG( "hypro.reachability", "All enabledSegments after aggregation: " << print( successors ) );

        // applyReset
        for (auto &[transition, valuationSets, valuationSetsUnder]: successors) {
            auto itUnder = valuationSetsUnder.begin();
            for (auto it = valuationSets.begin(); it != valuationSets.end() ;) {

                it->valuationSet = applyReset(it->valuationSet, transition->getReset());
                if (mSettings.underapproxReach) {
                    itUnder->valuationSet = applyReset(itUnder->valuationSet, transition->getReset());
                }

                TRACE("hypro.reachability", "Set after reset " << it->valuationSet);
                TRACE("hypro.reachability",
                      transition->getSource()->getName() << " -> " << transition->getTarget()->getName()
                                                         << ": Reset is: " << transition->getReset());
                CONTAINMENT containment;
                // if the over-approximative set is inside the invariant, then so is the under-approximative 
                std::tie(containment, it->valuationSet) = intersect(it->valuationSet,
                                                                    transition->getTarget()->getInvariant());
                TRACE("hypro.reachability", "Set after reset and intersection with invariant " << it->valuationSet);
                if (containment == CONTAINMENT::NO) {
                    it = valuationSets.erase(it);
                    if (mSettings.underapproxReach) {
                        itUnder = valuationSetsUnder.erase(itUnder);
                    }
                } else {
                    it->valuationSet.reduceRepresentation();
                    ++it;
                    if (mSettings.underapproxReach) {
                        itUnder->valuationSet.reduceRepresentation();
                        ++itUnder;   
                    }
                }
            }
        }

        return successors;
    }

    template<typename Representation, typename HybridAutomaton>
    std::vector<TimedValuationSet<Representation>>
    LTIWorker<Representation, HybridAutomaton>::computeJumpSuccessorsForGuardEnabled(
            std::vector<IndexedValuationSet<Representation>> &predecessors,
            Transition<LocationT> const *transition) const {
        std::size_t blockSize = 1;
        if (mSettings.aggregation == AGG_SETTING::AGG ||
            (mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() == AGG_SETTING::AGG)) {
            if (mSettings.clustering > 0) {
                blockSize =
                        (predecessors.size() + mSettings.clustering) / mSettings.clustering;    // division rounding up
            } else {
                blockSize = predecessors.size();
            }

        } else if (mSettings.aggregation == AGG_SETTING::MODEL && transition->getAggregation() != AGG_SETTING::NO_AGG) {
            if (transition->getAggregation() == AGG_SETTING::CLUSTERING) {
                blockSize = (blockSize + transition->getClusterBound()) /
                            transition->getClusterBound();    // division rounding up
            }
        }
        auto valuationSets = aggregate<Representation>(blockSize, predecessors);

        // applyReset
        // for ( auto& valuationSets : successors ) {
        for (auto it = valuationSets.begin(); it != valuationSets.end();) {
            it->valuationSet = applyReset(it->valuationSet, transition->getReset(), mSubspace);
            CONTAINMENT containment;
            std::tie(containment, it->valuationSet) = intersect(it->valuationSet,
                                                                transition->getTarget()->getInvariant(), mSubspace);
            if (containment == CONTAINMENT::NO) {
                it = valuationSets.erase(it);
            } else {
                it->valuationSet.reduceRepresentation();
                ++it;
            }
        }
        //}

        return valuationSets;
    }

}  // namespace hypro
