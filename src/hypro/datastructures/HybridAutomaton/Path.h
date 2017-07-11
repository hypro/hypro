#pragma once

#include "Transition.h"
#include <deque>


namespace hypro {

	template <typename Number>
	struct TPathElement {
		Transition<Number>* transition = nullptr;
		carl::Interval<Number> timeInterval = carl::Interval<Number>::unboundedInterval();

		TPathElement(Transition<Number>* t, const carl::Interval<Number>& enabledTime)
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

		friend std::ostream& operator<<(std::ostream& out, const TPathElement<Number>& pathElem) {
#ifdef HYDRA_USE_LOGGING
			if(pathElem.isDiscreteStep())
				out << pathElem.transition->getSource()->getId() << " -> " << pathElem.transition->getTarget()->getId() << " " << pathElem.timeInterval;
			else
				out << pathElem.timeInterval;
#endif
			return out;
		}

		friend bool operator==(const TPathElement<Number>& lhs, const TPathElement<Number>& rhs) {
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

		friend bool operator!=(const TPathElement<Number>& lhs, const TPathElement<Number>& rhs) {
			return !(lhs==rhs);
		}
	};

	/**
	 * @brief      Class to define a path in some hybrid automaton.
	 */
	template<typename Number>
	class Path {
		public:

			Path() = default;

			void add(const TPathElement<Number>& elem);
			void addTransition<Number>(Transition<Number>* t, const carl::Interval<Number>& enabledTime);
			void addTimeStep(const carl::Interval<Number>& timeStep);

			std::pair<Transition<Number>*, carl::Interval<Number>> getTransition<Number>ToJumpDepth(unsigned depth) const;

			static bool sharePrefix(const Path<Number>& lhs, const Path<Number>& rhs);
			bool sharesPrefix(const Path<Number>& rhs) const;
			Path sharedPrefix(const Path<Number>& rhs) const;
			bool isEmpty() const { return (mPath.size() == 0); }
			Number maximalTimeSpan(std::deque<TPathElement>::const_iterator start, std::deque<TPathElement>::const_iterator end) const;
			std::vector<Transition<Number>*> getTransition<Number>Sequence(std::deque<TPathElement>::const_iterator start, std::deque<TPathElement>::const_iterator end) const;
			bool hasChatteringZeno() const;

			// comparison - read as "is longer than"
			bool operator>(const Path<Number>& r) const;
			bool operator>(unsigned r) const;

			// Iterator
			typedef std::deque<TPathElement<Number>>::iterator TIterator;
			TIterator begin ();
			TIterator end();

			// legacy operations - replace them
			std::size_t size() const;
			TPathElement<Number> at(int index) const;
			void pop_front();
			void push_front(const TPathElement<Number>& elem);

			friend std::ostream& operator<<(std::ostream& _out, const Path<Number>& path) {
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

			bool operator==(const Path<Number>& rhs) const {
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

			bool operator!=(const Path<Number>& rhs) const {
				return !(*this == rhs);
			}

		private:
			std::deque<TPathElement<Number>> mPath; // why is this a deque? - shouldn't it be more of a double-linked list?
			// or even better: define this recursively. A path is empty or a subpath
			// Stefan: This is historic :).
			bool chatteringZeno = false;

	};

} // namespace hydra

#include "Path.tpp"
