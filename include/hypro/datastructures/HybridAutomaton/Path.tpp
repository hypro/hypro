/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Path.cc
 *
 *  Created on: 10.01.2017
 *      Author: j0h
 */
#include "Path.h"

namespace hypro {

    template<typename Number, typename tNumber>
    Path<Number, tNumber>::Path(std::initializer_list<TPathElement<Number, tNumber>> pathElems)
            : mPath() {
        std::for_each(pathElems.begin(), pathElems.end(), [&](const auto &e) { mPath.push_back(e); });
    }

    template<typename Number, typename tNumber>
    void Path<Number, tNumber>::add(const TPathElement<Number, tNumber> &elem) {
        mPath.push_back(elem);
    }

    template<typename Number, typename tNumber>
    void
    Path<Number, tNumber>::addTransition(Transition<Location<Number>> *t, const carl::Interval<tNumber> &enabledTime) {
        mPath.push_back(TPathElement<Number, tNumber>(t, enabledTime));
        TRACE("hypro.datastructures", "Add transition " << t << " with timestamp " << enabledTime << " to path.");
    }

    template<typename Number, typename tNumber>
    void Path<Number, tNumber>::addTimeStep(const carl::Interval<tNumber> &timeStep) {
        mPath.push_back(TPathElement<Number, tNumber>(timeStep));
        TRACE("hypro.datastructures", "Add timestep " << timeStep << " to path.");
    }

    template<typename Number, typename tNumber>
    std::pair<Transition<Location<Number>> *, carl::Interval<tNumber>>
    Path<Number, tNumber>::getTransitionToJumpDepth(unsigned depth) const {
        TRACE("hypro.datastructures", "Get transition for depth " << depth << " in path " << *this);
        if (depth == 0) {
            return std::make_pair(nullptr, createUnboundedInterval<tNumber>());
        }

        unsigned pos = 0;
        while (pos < mPath.size() && depth > 0) {
            if (mPath.at(pos).isDiscreteStep()) {
                depth--;
                if (depth > 0)
                    ++pos;
            } else {
                pos++;
            }
        }
        if (pos == mPath.size()) {
            TRACE("hypro.datastructures", "Did not find appropriate transition.");
            return std::make_pair(nullptr, createEmptyInterval<tNumber>());
        }
        return std::make_pair(mPath.at(pos).transition, mPath.at(pos).timeInterval);
    }

    template<typename Number, typename tNumber>
    Path<Number, tNumber> &Path<Number, tNumber>::deleteAfterPos(std::size_t cutpos) {
        if (cutpos >= this->size()) {
            return *this;
        }
        auto pathIt = mPath.begin();
        while (cutpos > 0) {
            ++pathIt;
            --cutpos;
        }
        ++pathIt;
        while (pathIt != mPath.end()) {
            pathIt = mPath.erase(pathIt);
        }
        return *this;
    }

    template<typename Number, typename tNumber>
    Path<Number, tNumber> &Path<Number, tNumber>::deleteBeforePos(std::size_t cutpos) {
        if (cutpos >= this->size()) {
            this->clear();
            return *this;
        }
        auto pathIt = mPath.begin();
        while (cutpos > 0) {
            pathIt = mPath.erase(pathIt);
            --cutpos;
        }
        return *this;
    }

    template<typename Number, typename tNumber>
    Path<Number, tNumber> &Path<Number, tNumber>::clear() {
        auto pathIt = mPath.begin();
        while (!mPath.empty()) {
            pathIt = mPath.erase(pathIt);
        }
        return *this;
    }

    template<typename Number, typename tNumber>
    bool Path<Number, tNumber>::sharePrefix(const Path<Number, tNumber> &lhs, const Path<Number, tNumber> &rhs) {
        for (auto lhsIt = lhs.mPath.begin(); lhsIt != lhs.mPath.end(); ++lhsIt) {
            for (auto rhsIt = rhs.mPath.begin(); rhsIt != rhs.mPath.end(); ++rhsIt) {
                if (*lhsIt == *rhsIt) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename Number, typename tNumber>
    Path<Number, tNumber> Path<Number, tNumber>::sharedPrefix(const Path<Number, tNumber> &lhs) const {
        Path<Number, tNumber> prefix;
        for (unsigned pos = 0; pos < mPath.size() && pos < lhs.size(); ++pos) {
            TRACE("hypro.datastructures", "Compare path elements " << mPath.at(pos) << " and " << lhs.at(pos));
            if (mPath.at(pos) == lhs.at(pos)) {
                TRACE("hypro.datastructures", "Add to shared prefix.");
                prefix.add(mPath.at(pos));
            }
        }
        return prefix;
    }

    template<typename Number, typename tNumber>
    Path<Number, tNumber> Path<Number, tNumber>::removeSharedPrefix(const Path<Number, tNumber> &rhs) const {
        Path<Number, tNumber> res(*this);
        TRACE("hydra.hypro.datastructures",
              "Shared prefix of " << *this << " and " << rhs << ": " << this->sharedPrefix(rhs));
        std::size_t prefixLength = this->sharedPrefix(rhs).size();
        while (prefixLength > 0) {
            res.pop_front();
            --prefixLength;
        }
        return res;
    }

    template<typename Number, typename tNumber>
    tNumber
    Path<Number, tNumber>::maximalTimeSpan(typename std::deque<TPathElement<Number, tNumber>>::const_iterator start,
                                           typename std::deque<TPathElement<Number, tNumber>>::const_iterator end) const {
        tNumber timespan = 0;
        bool validPath = true;
        auto currentPos = start;
        // std::cout << __func__ << ": start loop." << std::endl;
        while (validPath) {
            if (currentPos == end) {
                if (!currentPos->isDiscreteStep()) {
                    timespan += currentPos->timeInterval.upper();
                }
                // std::cout << "Found end." << std::endl;
                assert(validPath);
                break;
            } else if (currentPos == mPath.end()) {
                validPath = false;
                // std::cout << "did not find end - invalid path." << std::endl;
                break;
            } else {
                assert(validPath);
                if (!(currentPos->isDiscreteStep())) {
                    // std::cout << "increase timespan by " << currentPos->timeInterval.upper() << std::endl;
                    timespan += currentPos->timeInterval.upper();
                }
            }
            ++currentPos;
        }
        // std::cout << "Exited loop." << std::endl;
        if (!validPath) {
            return -1;
        }
        return timespan;
    }

    template<typename Number, typename tNumber>
    std::size_t Path<Number, tNumber>::getNumberDiscreteJumps() const {
        std::size_t res = 0;
        for (const auto &pathElem: mPath) {
            if (pathElem.isDiscreteStep()) {
                ++res;
            }
        }
        return res;
    }

    template<typename Number, typename tNumber>
    std::vector<Transition<Location<Number>> *> Path<Number, tNumber>::getTransitionSequence(
            typename std::deque<TPathElement<Number, tNumber>>::const_iterator start,
            typename std::deque<TPathElement<Number, tNumber>>::const_iterator end) const {
        auto currentPos = start;
        std::vector<Transition<Location<Number>> *> res;
        while (currentPos != mPath.end() && currentPos != end) {
            if (currentPos->isDiscreteStep()) {
                res.push_back(currentPos->transition);
            }
            ++currentPos;
        }
        if (currentPos == mPath.end() && end != mPath.end()) {
            // path end is not part of mPath or lies before start.
            return std::vector<Transition<Location<Number>> *>();
        }
        return res;
    }

    template<typename Number, typename tNumber>
    bool Path<Number, tNumber>::hasChatteringZeno() const {
        // find all cycles first and store potential cycles
        // std::cout << __func__ << ": checking path: " << *this << std::endl;
        std::vector<std::vector<Transition<Location<Number>> *>> potentialCycles;
        for (auto startElemIt = mPath.begin(); startElemIt != mPath.end(); ++startElemIt) {
            // start measuring the time from a timestep -> if the startElement is not a timestep, increase it.
            if (!startElemIt->isDiscreteStep()) {
                ++startElemIt;
            }
            if (startElemIt == mPath.end()) {
                break;
            }
            // std::cout << __func__ << ": Starting point is: " << *startElemIt << std::endl;
            //  if the startElement iterator is not pointing to the end of the path (this is the case when the last item is a transition)
            //  detect cycle by finding the same location.
            if (startElemIt != mPath.end()) {
                auto nextElem = startElemIt;
                nextElem++;
                if ((nextElem) == mPath.end()) {
                    break;
                }
                const Location<Number> *startLoc = (startElemIt)->transition->getSource();
                // std::cout << "Dimension: " << (startElemIt)->transition->getReset().getContinuousResetMatrix().cols() << std::endl;
                std::vector<Transition<Location<Number>> *> transitionSequence;
                transitionSequence.push_back((startElemIt)->transition);
                // std::cout << __func__ << ": Starting location is " << startLoc->getId() << std::endl;
                for (; nextElem != mPath.end(); ++nextElem) {
                    // std::cout << __func__ << ": next element is " << *(nextElem) << std::endl;
                    // std::cout << __func__ << ": current maximal timespan is " << maximalTimeSpan(startElemIt,nextElem) << std::endl;
                    if (nextElem->isDiscreteStep() &&
                        nextElem->transition->getTarget() == startLoc &&
                        maximalTimeSpan(startElemIt, nextElem) == 0) {
                        transitionSequence.push_back(nextElem->transition);
                        // std::cout << "Found potential path." << std::endl;
                        // std::cout << "Transition<Number> sequence length: " << transitionSequence.size() << std::endl;
                        potentialCycles.push_back(transitionSequence);
                        break;
                    } else if (nextElem->isDiscreteStep()) {
                        transitionSequence.push_back(nextElem->transition);
                    }
                }
            }
        }

        // std::cout << __func__ << ": Exited loop, now verifying resets. Number of potential cycles: " << potentialCycles.size() << std::endl;

        // for each of the location sequences collect the resets - if they form the identity we have found a simple case of chattering Zeno behavior.
        // TODO: Extend this for discrete and clock resets!
        // TODO: Extend this for the reset vector!
        for (auto &transitionSequence: potentialCycles) {
            assert((*transitionSequence.begin())->getSource() == transitionSequence.back()->getTarget());
            assert(!transitionSequence.empty());
            auto transitionIt = transitionSequence.begin();
            // std::cout << "Reset: " << (*transitionIt)->getReset() << std::endl;
            // std::cout << "Dimension: " << (*transitionIt)->getReset().getContinuousResetMatrix().cols() << std::endl;
            hypro::matrix_t<Number> resetMatrix = (*transitionIt)->getReset().getMatrix();
            ++transitionIt;
            for (; transitionIt != transitionSequence.end(); ++transitionIt) {
                // std::cout << "Reset: " << (*transitionIt)->getReset() << std::endl;
                resetMatrix = (*transitionIt)->getReset().getMatrix() * resetMatrix;
            }
            // std:cout << __func__ << ": Resulting reset matrix: " << resetMatrix << std::endl;
            if (resetMatrix == hypro::matrix_t<Number>::Identity(resetMatrix.rows(), resetMatrix.cols())) {
                // std::cout << __func__ << ": Found chattering Zeno path: " <<  *this << std::endl;
                return true;
            }
        }
        return false;
    }

    template<typename Number, typename tNumber>
    bool Path<Number, tNumber>::operator>(const Path<Number, tNumber> &r) const {
        return mPath.size() > r.mPath.size();
    }

    template<typename Number, typename tNumber>
    bool Path<Number, tNumber>::operator>(unsigned r) const {
        return mPath.size() > r;
    }

    template<typename Number, typename tNumber>
    std::size_t Path<Number, tNumber>::size() const {
        return mPath.size();
    }

    template<typename Number, typename tNumber>
    TPathElement<Number, tNumber> Path<Number, tNumber>::at(std::size_t index) const {
        return mPath.at(index);
    }

    template<typename Number, typename tNumber>
    void Path<Number, tNumber>::pop_front() {
        mPath.pop_front();
    }

    template<typename Number, typename tNumber>
    void Path<Number, tNumber>::push_front(const TPathElement<Number, tNumber> &elem) {
        mPath.push_front(elem);
    }

    template<typename Number, typename tNumber>
    bool Path<Number, tNumber>::sharesPrefix(const Path<Number, tNumber> &rhs) const {
        return sharePrefix(*this, rhs);
    }

    template<typename Number, typename tNumber>
    typename Path<Number, tNumber>::TIterator Path<Number, tNumber>::begin() {
        return mPath.begin();
    }

    template<typename Number, typename tNumber>
    typename Path<Number, tNumber>::TIterator Path<Number, tNumber>::end() {
        return mPath.end();
    }

    template<typename Number, typename tNumber>
    typename Path<Number, tNumber>::TIterator_const Path<Number, tNumber>::begin() const {
        return mPath.begin();
    }

    template<typename Number, typename tNumber>
    typename Path<Number, tNumber>::TIterator_const Path<Number, tNumber>::end() const {
        return mPath.end();
    }

    template<typename Number, typename tNumber>
    const TPathElement<Number, tNumber> &Path<Number, tNumber>::back() const {
        assert(!mPath.empty());
        return mPath.back();
    }

    template<typename Number, typename tNumber>
    const TPathElement<Number, tNumber> &Path<Number, tNumber>::front() const {
        assert(!mPath.empty());
        return mPath.front();
    }

}  // namespace hypro
