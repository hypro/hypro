#include "HierarchicalIntervalVector.h"

namespace hypro {

	template<typename T, typename Number>
	void HierarchicalIntervalVector<T, Number>::initialize(const T& baseElement, Number endTime) {
		assert(mIntervals.empty());
		mIntervals.emplace_back(endPoint<T,Number>(baseElement,endTime));
		assert(this->isSane());
	}

	template<typename T, typename Number>
	void HierarchicalIntervalVector<T, Number>::insertInterval(const T& type, const carl::Interval<Number>& timespan) {
		assert(this->isSane());
		carl::Interval<Number> copy = timespan;
		carl::Interval<double> tmp = carl::Interval<double>(carl::convert<Number,double>(copy.lower()),carl::convert<Number,double>(copy.upper()));
		DEBUG("hydra.datastructures.hiv","Insert interval " << tmp << " of type " << type << " into: " << *this);

		for(auto it = mIntervals.begin(); it != mIntervals.end(); ++it) {
#ifdef HYPRO_USE_LOGGING
			double tmptp = carl::convert<Number,double>(it->timePoint);
			TRACE("hydra.datastructures.hiv","Consider " << tmptp << ", " << it->type);
#endif
			if(it->timePoint <= copy.lower()) {
				TRACE("hydra.datastructures.hiv","Area not reached, skip.");
				continue;
			}
			if((it != mIntervals.begin() && std::prev(it)->timePoint >= copy.upper())){
				TRACE("hydra.datastructures.hiv","Done.");
				break;
			}

			if(copy.upper() >= it->timePoint && ((it == mIntervals.begin() && copy.lower() == Number(0)) || (it != mIntervals.begin() && std::prev(it)->timePoint >= copy.lower())) && isLess(it->type, type)) {
				TRACE("hydra.datastructures.hiv","Simple override.");
				it->type = type;
			}
			if(copy.lower() <= it->timePoint && (it == mIntervals.begin() || std::prev(it)->timePoint < copy.lower() ) && isLess(it->type, type)) {
				if(copy.lower() > Number(0)) {
					it = mIntervals.insert(it, endPoint<T,Number>(it->type,copy.lower()));
					TRACE("hydra.datastructures.hiv","Left split, it now considers: " << it->timePoint << ", type " << it->type);
				}
			}
			if(copy.upper() < it->timePoint && (it == mIntervals.begin() || std::prev(it)->timePoint < copy.upper() ) && isLess(it->type, type)) {
				it = mIntervals.insert(it, endPoint<T,Number>(type,copy.upper()));
				TRACE("hydra.datastructures.hiv","Right split.");
				++it;
			}
		}

		TRACE("hydra.datastructures.hiv","After plain insertion: " << *this);

		// sanitize
		for(auto it = mIntervals.begin(); it != mIntervals.end(); ) {
			if(std::next(it) != mIntervals.end() && std::next(it)->type == it->type) {
				it = mIntervals.erase(it);
			} else {
				++it;
			}
		}

		DEBUG("hydra.datastructures.hiv","After insertion: " << *this);
		assert(this->isSane());
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::hasEntry(const T& type) const {
		assert(this->isSane());
		for(const auto& item : mIntervals) {
			if(item.type == type)
				return true;
		}
		return false;
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::hasEntry(const carl::Interval<Number>& timeInterval) const {
		assert(this->isSane());
		for(auto t : mOrder) {
			if(hasEntry(timeInterval,t)) {
				return true;
			}
		}
		return false;
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::hasEntry(const carl::Interval<Number>& timeInterval, const T& type) const {
		assert(this->isSane());
		DEBUG("hydra.datastructures.hiv", "hasEntry: " << timeInterval << ", type " << type );
		for(auto it = mIntervals.begin(); it != mIntervals.end(); ++it) {
			TRACE("hydra.datastructures.hiv", "Consider interval" << it->timePoint << ", " << it->type );
			if(it->timePoint < timeInterval.lower()) {
				TRACE("hydra.datastructures.hiv", "continue" );
				continue;
			}

			// special case for first interval since there is no predecessor.
			if(it == mIntervals.begin()) {
				TRACE("hydra.datastructures.hiv", "First interval" );
				if(it->timePoint >= timeInterval.upper()) {
					TRACE("hydra.datastructures.hiv", "Bounds match" );
					if(it->type == type) {
						DEBUG("hydra.datastructures.hiv", "Types match (first interval) - return true." );
						return true;
					}
					return false;
				}
			}

			// the queried interval spans two stored intervals which by construction are of different types.
			if(it != mIntervals.begin() && it->timePoint >= timeInterval.upper() && (it-1)->timePoint > timeInterval.lower() ) {
				DEBUG("hydra.datastructures.hiv", "Is not first and bounds do not match - return false." );
				return false;
			}
			// too far.
			if(it != mIntervals.begin() && (it-1)->timePoint > timeInterval.upper()){
				DEBUG("hydra.datastructures.hiv", "No matching time interval found - return false." );
				return false;
			}

			// at this point the bounds match, now check type.
			if(it->type == type) {
				DEBUG("hydra.datastructures.hiv", "Types match - return true." );
				return true;
			}
		}
		return false;
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::intersectsEntry(const carl::Interval<Number>& timeInterval, const T& type) const {
		assert(this->isSane());
		DEBUG("hydra.datastructures.hiv", "This: " << *this << " intersects: " << timeInterval << ", type " << type );
		for(auto it = mIntervals.begin(); it != mIntervals.end(); ++it) {
			TRACE("hydra.datastructures.hiv", "Consider interval" << it->timePoint << ", " << it->type );
			if(it->timePoint < timeInterval.lower()) {
				TRACE("hydra.datastructures.hiv", "continue" );
				continue;
			}

			// special case for first interval since there is no predecessor.
			if(it == mIntervals.begin()) {
				TRACE("hydra.datastructures.hiv", "First interval" );
				if(timeInterval.lower() <= it->timePoint) {
					TRACE("hydra.datastructures.hiv", "Bounds match" );
					if(it->type == type) {
						DEBUG("hydra.datastructures.hiv", "Types match (first interval) - return true." );
						return true;
					}
				}
			}

			if(it != mIntervals.begin() && timeInterval.intersectsWith(carl::Interval<Number>(std::prev(it,1)->timePoint, it->timePoint)) && it->type == type) {
				DEBUG("hydra.datastructures.hiv", "Bound and type match - return true." );
				return true;
			}

			// too far.
			if(it != mIntervals.begin() && std::prev(it,1)->timePoint > timeInterval.upper()){
				DEBUG("hydra.datastructures.hiv", "No matching time interval found - return false." );
				return false;
			}
		}
		// should only happen when mIntervals is empty (?).
		return false;
	}

	template<typename T, typename Number>
	void HierarchicalIntervalVector<T, Number>::merge(const HierarchicalIntervalVector<T,Number>& rhs) {
		Number prevTimepoint = Number(0);
		for(auto& endPoint : rhs.getIntervals()) {
			this->insertInterval(endPoint.type, carl::Interval<Number>(prevTimepoint, endPoint.timePoint));
			prevTimepoint = endPoint.timePoint;
		}
	}

	template<typename T, typename Number>
	const endPoint<T,Number>& HierarchicalIntervalVector<T, Number>::back() const {
		assert(this->isSane());
		assert(!mIntervals.empty());
		return mIntervals.back();
	}

	template<typename T, typename Number>
	std::size_t HierarchicalIntervalVector<T, Number>::size() const {
		assert(this->isSane());
		return mIntervals.size();
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::empty() const {
		assert(this->isSane());
		return mIntervals.empty();
	}

	template<typename T, typename Number>
	Number HierarchicalIntervalVector<T, Number>::getTimeHorizon() const {
		assert(!mIntervals.empty());
		assert(this->isSane());
		return mIntervals.back().timePoint;
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::isLess(const T& lhs, const T& rhs) const{
		//TRACE("hydra.datastructures.hiv","Compare " << lhs << " and " << rhs << ", for this: " << *this << " with order ");
		//for(auto i : mOrder){
		//	TRACE("hydra.datastructures.hiv",i);
		//}
		assert(std::find(mOrder.begin(),mOrder.end(), lhs) != mOrder.end());
		assert(std::find(mOrder.begin(),mOrder.end(), rhs) != mOrder.end());
		for(std::size_t p = 0; p < mOrder.size(); ++p) {
			if(mOrder.at(p) == rhs) {
				return false;
			}
			if(mOrder.at(p) == lhs) {
				return true;
			}
		}
		// none of the items is in the order.
		assert(false);
		FATAL("hydra.datastructures.hiv","This should not be reachable! Error: the queried items are not in the passed order vector.");
		std::cout << "HierarchicalIntervalVector." << __func__  << ": THIS SHOULD NOT BE REACHABLE!" << std::endl;
		return false;
	}

	template<typename T, typename Number>
	std::size_t HierarchicalIntervalVector<T, Number>::getOrderIndex(const T& type) const {
		for(std::size_t p = 0; p < mOrder.size(); ++p) {
			if(mOrder.at(p) == type) {
				return p;
			}
		}
		return mOrder.size();
	}

	template<typename T, typename Number>
	bool HierarchicalIntervalVector<T, Number>::isSane() const {
		for(auto it = mIntervals.begin(); it != mIntervals.end(); ++it) {
			if(it != mIntervals.begin()) {
				if(it->type == std::prev(it,1)->type) {
					return false;
				}
			}
		}
		return true;
	}

} // hypro
