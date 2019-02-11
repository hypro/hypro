#pragma once
#include "../../../util/logging/Logger.h"
#include "../../../types.h"
#include "../../../util/convenienceOperators.h"
#include <carl/interval/Interval.h>
#include <utility>
#include <vector>

namespace hypro {

template<typename T, typename Number>
struct endPoint {
	T type;
	Number timePoint;

	endPoint(const T& t, const Number& n)
		: type(t)
		, timePoint(n)
	{}

	friend bool operator==(const endPoint<T,Number>& lhs, const endPoint<T,Number>& rhs) {
		return (lhs.type == rhs.type
			&& lhs.timePoint == rhs.timePoint);
	}

	friend bool operator!=(const endPoint<T,Number>& lhs, const endPoint<T,Number>& rhs) { return !(lhs == rhs); }
};

template<typename T, typename Number>
class HierarchicalIntervalVector {
private:

	std::vector<T> mOrder;
	std::vector<endPoint<T,Number>> mIntervals;

public:
	HierarchicalIntervalVector() = delete;
	HierarchicalIntervalVector(const std::vector<T>& order) : mOrder(order) {}

	void initialize(const T& baseElement, Number endTime);

	void insertInterval(const T& type, const carl::Interval<Number>& timespan);

	/**
	 * @brief      Determines if it has an entry of the passed type.
	 * @param[in]  type  The type
	 * @return     True if has entry, False otherwise.
	 */
	bool hasEntry(const T& type) const;

	/**
	 * @brief      Determines if it has entry for the exact or a smaller time interval.
	 * @param[in]  timeInterval  The time interval.
	 * @return     True if has entry, False otherwise.
	 */
	bool hasEntry(const carl::Interval<Number>& timeInterval) const;

	/**
	 * @brief      Determines if it has entry where the type matches and the interval is a subset of some contained interval.
	 * @param[in]  timeInterval  The time interval.
	 * @param[in]  type          The type.
	 * @return     True if has entry, False otherwise.
	 */
	bool hasEntry(const carl::Interval<Number>& timeInterval, const T& type) const;

	/**
	 * @brief      Determines if it the interval intersects some contained interval where the type matches.
	 * @param[in]  timeInterval  The time interval.
	 * @param[in]  type       The type.
	 * @return     True if there exists a matching entry, False otherwise.
	 */
	bool intersectsEntry(const carl::Interval<Number>& timeInterval, const T& type) const;

	void merge(const HierarchicalIntervalVector<T,Number>& rhs);

	const endPoint<T,Number>& back() const;

	std::size_t size() const;
	bool empty() const;
	Number getTimeHorizon() const;

	friend std::ostream& operator<<(std::ostream& out, const HierarchicalIntervalVector<T,Number>& in) {
		for(const auto& valuePair : in.mIntervals) {
			out << "(" << carl::convert<Number,double>(valuePair.timePoint) << ", " << valuePair.type << "), ";
		}
		return out;
	}

	friend bool operator==(const HierarchicalIntervalVector<T,Number>& lhs, const HierarchicalIntervalVector<T,Number>& rhs) {
		return (lhs.mOrder == rhs.mOrder
			&& lhs.mIntervals == rhs.mIntervals);
	}

	friend bool operator!=(const HierarchicalIntervalVector<T,Number>& lhs, const HierarchicalIntervalVector<T,Number>& rhs) { return !(lhs == rhs); }

private:
	const std::vector<endPoint<T,Number>>& getIntervals() const { return mIntervals; }
	bool isLess(const T& lhs, const T& rhs) const;
	std::size_t getOrderIndex(const T& type) const;
	bool isSane() const;
};

} // hypro

#include "HierarchicalIntervalVector.tpp"
#include "HIV_util.h"
