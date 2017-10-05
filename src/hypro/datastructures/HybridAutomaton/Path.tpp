/*
 * Path.cc
 *
 *  Created on: 10.01.2017
 *      Author: j0h
 */
#include "Path.h"

namespace hypro {

	template<typename Number>
	void Path<Number>::add(const TPathElement<Number>& elem) {
		mPath.push_back(elem);
	}

	template<typename Number>
	void Path<Number>::addTransition(Transition<Number>* t, const carl::Interval<Number>& enabledTime) {
		mPath.push_back(TPathElement<Number>(t,enabledTime));
		TRACE("hypro.datastructures","Add transition " << t << " with timestamp " << enabledTime << " to path.");
	}

	template<typename Number>
	void Path<Number>::addTimeStep(const carl::Interval<Number>& timeStep) {
		mPath.push_back(TPathElement<Number>(timeStep));
		TRACE("hypro.datastructures","Add timestep " << timeStep << " to path.");
	}

	template<typename Number>
	std::pair<Transition<Number>*, carl::Interval<Number>> Path<Number>::getTransitionToJumpDepth(unsigned depth) const {
		TRACE("hypro.datastructures","Get transition for depth " << depth << " in path " << *this);
		if(depth == 0) {
			return std::make_pair(nullptr, carl::Interval<Number>::unboundedInterval());
		}

		unsigned pos = 0;
		while(pos < mPath.size() && depth > 0) {
			if(mPath.at(pos).isDiscreteStep()) {
				depth--;
				if(depth > 0)
					++pos;
			} else {
				pos++;
			}
		}
		if(pos == mPath.size()) {
			TRACE("hypro.datastructures","Did not find appropriate transition.");
			return std::make_pair(nullptr, carl::Interval<Number>::emptyInterval());
		}
		return std::make_pair(mPath.at(pos).transition, mPath.at(pos).timeInterval);
	}

	template<typename Number>
	bool Path<Number>::sharePrefix(const Path<Number>& lhs, const Path<Number>& rhs) {
        for (auto lhsIt = lhs.mPath.begin(); lhsIt != lhs.mPath.end(); ++lhsIt) {
            for (auto rhsIt = rhs.mPath.begin(); rhsIt != rhs.mPath.end(); ++rhsIt) {
                if (*lhsIt == *rhsIt) {
                    return true;
                }
            }
        }
        return false;
	}

	template<typename Number>
	Path<Number> Path<Number>::sharedPrefix(const Path<Number>& lhs) const {
		Path<Number> prefix;
		for(unsigned pos = 0; pos < mPath.size() && pos < lhs.size(); ++pos) {
			if( mPath.at(pos) == lhs.at(pos)) {
				prefix.add(mPath.at(pos));
			}
		}
		return prefix;
	}

	template<typename Number>
	Path<Number> Path<Number>::removeSharedPrefix(const Path<Number>& rhs) const {
		Path<Number> res(*this);
		TRACE("hydra.hypro.datastructures","Shared prefix of " << *this << " and " << rhs << ": " << this->sharedPrefix(rhs));
		std::size_t prefixLength = this->sharedPrefix(rhs).size();
		while(prefixLength > 0){
			res.pop_front();
			--prefixLength;
		}
		return res;
	}

	template<typename Number>
	Number Path<Number>::maximalTimeSpan(typename std::deque<TPathElement<Number>>::const_iterator start, typename std::deque<TPathElement<Number>>::const_iterator end) const {
		Number timespan = 0;
		bool validPath = true;
		auto currentPos = start;
		//std::cout << __func__ << ": start loop." << std::endl;
		while(validPath){
			if(currentPos == end) {
				if(!currentPos->isDiscreteStep()){
					timespan += currentPos->timeInterval.upper();
				}
				//std::cout << "Found end." << std::endl;
				assert(validPath);
				break;
			} else if (currentPos == mPath.end()) {
				validPath = false;
				//std::cout << "did not find end - invalid path." << std::endl;
				break;
			} else {
				assert(validPath);
				if(!(currentPos->isDiscreteStep())){
					//std::cout << "increase timespan by " << currentPos->timeInterval.upper() << std::endl;
					timespan += currentPos->timeInterval.upper();
				}
			}
			++currentPos;
		}
		//std::cout << "Exited loop." << std::endl;
		if(!validPath) {
			return -1;
		}
		return timespan;
	}

	template<typename Number>
	std::size_t Path<Number>::getNumberDiscreteJumps() const {
		std::size_t res = 0;
		for(const auto& pathElem : mPath) {
			if(pathElem.isDiscreteStep()) {
				++res;
			}
		}
		return res;
	}

	template<typename Number>
	std::vector<Transition<Number>*> Path<Number>::getTransitionSequence(typename std::deque<TPathElement<Number>>::const_iterator start, typename std::deque<TPathElement<Number>>::const_iterator end) const {
		auto currentPos = start;
		std::vector<Transition<Number>*> res;
		while(currentPos != mPath.end() && currentPos != end) {
			if(currentPos->isDiscreteStep()){
				res.push_back(currentPos->transition);
			}
			++currentPos;
		}
		if(currentPos == mPath.end() && end != mPath.end()) {
			// path end is not part of mPath or lies before start.
			return std::vector<Transition<Number>*>();
		}
		return res;
	}

	template<typename Number>
	bool Path<Number>::hasChatteringZeno() const {
		// find all cycles first and store potential cycles
		// std::cout << __func__ << ": checking path: " << *this << std::endl;
		std::vector<std::vector<Transition<Number>*>> potentialCycles;
		for(auto startElemIt = mPath.begin(); startElemIt != mPath.end(); ++startElemIt) {
			// start measuring the time from a timestep -> if the startElement is not a timestep, increase it.
			if(!startElemIt->isDiscreteStep()){
				++startElemIt;
			}
			if(startElemIt == mPath.end()) {
				break;
			}
			//std::cout << __func__ << ": Starting point is: " << *startElemIt << std::endl;
			// if the startElement iterator is not pointing to the end of the path (this is the case when the last item is a transition)
			// detect cycle by finding the same location.
			if(startElemIt != mPath.end()) {
				auto nextElem = startElemIt;
				nextElem++;
				if((nextElem) == mPath.end()) {
					break;
				}
				const Location<Number>* startLoc = (startElemIt)->transition->getSource();
				// std::cout << "Dimension: " << (startElemIt)->transition->getReset().getContinuousResetMatrix().cols() << std::endl;
				std::vector<Transition<Number>*> transitionSequence;
				transitionSequence.push_back((startElemIt)->transition);
				//std::cout << __func__ << ": Starting location is " << startLoc->getId() << std::endl;
				for( ; nextElem != mPath.end(); ++nextElem) {
					//std::cout << __func__ << ": next element is " << *(nextElem) << std::endl;
					//std::cout << __func__ << ": current maximal timespan is " << maximalTimeSpan(startElemIt,nextElem) << std::endl;
					if(nextElem->isDiscreteStep() &&
						nextElem->transition->getTarget() == startLoc &&
						maximalTimeSpan(startElemIt,nextElem) == 0 ){
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
		for(auto& transitionSequence : potentialCycles) {
			assert((*transitionSequence.begin())->getSource() == transitionSequence.back()->getTarget());
			assert(!transitionSequence.empty());
			auto transitionIt = transitionSequence.begin();
			// std::cout << "Reset: " << (*transitionIt)->getReset() << std::endl;
			// std::cout << "Dimension: " << (*transitionIt)->getReset().getContinuousResetMatrix().cols() << std::endl;
			hypro::matrix_t<Number> resetMatrix = (*transitionIt)->getReset().getContinuousResetMatrix();
			++transitionIt;
			for( ; transitionIt != transitionSequence.end(); ++transitionIt) {
				// std::cout << "Reset: " << (*transitionIt)->getReset() << std::endl;
				resetMatrix = (*transitionIt)->getReset().getContinuousResetMatrix() * resetMatrix;
			}
			//std:cout << __func__ << ": Resulting reset matrix: " << resetMatrix << std::endl;
			if(resetMatrix == hypro::matrix_t<Number>::Identity(resetMatrix.rows(), resetMatrix.cols())) {
				// std::cout << __func__ << ": Found chattering Zeno path: " <<  *this << std::endl;
				return true;
			}
		}
		return false;
	}

	template<typename Number>
	bool Path<Number>::operator>(const Path<Number>& r) const {
		return mPath.size() > r.mPath.size();
	}

	template<typename Number>
	bool Path<Number>::operator>(unsigned r) const {
		return mPath.size() > r;
	}

	template<typename Number>
	std::size_t Path<Number>::size() const {
		return mPath.size();
	}

	template<typename Number>
	TPathElement<Number> Path<Number>::at(int index) const {
		return mPath.at(index);
	}

	template<typename Number>
	void Path<Number>::pop_front() {
		mPath.pop_front();
	}

	template<typename Number>
	void Path<Number>::push_front(const TPathElement<Number>& elem) {
		mPath.push_front(elem);
	}

	template<typename Number>
	bool Path<Number>::sharesPrefix(const Path<Number>& rhs) const {
		return sharePrefix(*this, rhs);
	}

	template<typename Number>
	typename Path<Number>::TIterator Path<Number>::begin () {
		return mPath.begin();
	}

	template<typename Number>
	typename Path<Number>::TIterator Path<Number>::end() {
		return mPath.end();
	}

	template<typename Number>
	const TPathElement<Number>& Path<Number>::back() const {
		assert(!mPath.empty());
		return mPath.back();
	}

	template<typename Number>
	const TPathElement<Number>& Path<Number>::front() const {
		assert(!mPath.empty());
		return mPath.front();
	}

} // namespace hypro


