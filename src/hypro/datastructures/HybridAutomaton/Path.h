#pragma once

#include "lib/datastructures/HybridAutomaton/Transition.h"
#include <deque>


namespace hydra {

	struct TPathElement {
		Transition* transition = nullptr;
		carl::Interval<Number> timeInterval = carl::Interval<Number>::unboundedInterval();

		TPathElement(Transition* t, const carl::Interval<Number>& enabledTime)
			: transition(t)
			, timeInterval(enabledTime)
		{}

		TPathElement(const carl::Interval<Number>& timeStep)
			: transition(nullptr)
			, timeInterval(timeStep)
		{}

		bool isDiscreteStep() const {
			return (transition != nullptr);
		}

		friend std::ostream& operator<<(std::ostream& out, const TPathElement& pathElem) {
#ifdef HYDRA_USE_LOGGING
			if(pathElem.isDiscreteStep())
				out << pathElem.transition->getSource()->getId() << " -> " << pathElem.transition->getTarget()->getId() << " " << pathElem.timeInterval;
			else
				out << pathElem.timeInterval;
#endif
			return out;
		}

		friend bool operator==(const TPathElement& lhs, const TPathElement& rhs) {
			if(lhs.isDiscreteStep() != rhs.isDiscreteStep()) {
				return false;
			}

			if(lhs.isDiscreteStep()) {
				assert(rhs.isDiscreteStep());
				return (lhs.transition == rhs.transition && lhs.timeInterval == rhs.timeInterval);
			}
			assert(!rhs.isDiscreteStep());
			return (lhs.timeInterval == rhs.timeInterval);
		}

		friend bool operator!=(const TPathElement& lhs, const TPathElement& rhs) {
			return !(lhs==rhs);
		}
	};

	/**
	 * @brief      Class to define a path in some hybrid automaton.
	 */
	class Path {
		public:

			Path() = default;

			void add(const TPathElement& elem);
			void addTransition(Transition* t, const carl::Interval<Number>& enabledTime);
			void addTimeStep(const carl::Interval<Number>& timeStep);

			std::pair<Transition*, carl::Interval<Number>> getTransitionToJumpDepth(unsigned depth) const;

			static bool sharePrefix(const Path& lhs, const Path& rhs);
			bool sharesPrefix(const Path& rhs) const;
			Path sharedPrefix(const Path& rhs) const;
			bool isEmpty() const { return (mPath.size() == 0); }
			Number maximalTimeSpan(std::deque<TPathElement>::const_iterator start, std::deque<TPathElement>::const_iterator end) const;
			std::vector<Transition*> getTransitionSequence(std::deque<TPathElement>::const_iterator start, std::deque<TPathElement>::const_iterator end) const;
			bool hasChatteringZeno() const;

			// comparison - read as "is longer than"
			bool operator>(const Path& r) const;
			bool operator>(unsigned r) const;

			// Iterator
			typedef std::deque<TPathElement>::iterator TIterator;
			TIterator begin ();
			TIterator end();

			// legacy operations - replace them
			std::size_t size() const;
			TPathElement at(int index) const;
			void pop_front();
			void push_front(const TPathElement& elem);

			friend std::ostream& operator<<(std::ostream& _out, const Path& path) {
#ifdef HYDRA_USE_LOGGING
				if(!path.isEmpty()) {
					_out << path.at(0);
					for(std::size_t i = 1; i < path.size(); ++i) {
						_out << ", " << path.at(i);
					}
				}
#endif
				return _out;
			}

			bool operator==(const Path& rhs) const {
				if(this->size() != rhs.size()) {
					return false;
				}
				for(std::size_t i = 0; i < this->size(); ++i) {
					if(this->at(i) != rhs.at(i)) {
						return false;
					}
				}
				return true;
			}

			bool operator!=(const Path& rhs) const {
				return !(*this == rhs);
			}

		private:
			std::deque<TPathElement> mPath; // why is this a deque? - shouldn't it be more of a double-linked list?
			// or even better: define this recursively. A path is empty or a subpath
			// Stefan: This is historic :).
			bool chatteringZeno = false;

	};

} // namespace hydra
