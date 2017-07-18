
#pragma once

#include "functors.h"
#include "Condition.h"
#include "../../representations/types.h"
#include "../../representations/GeometricObject.h"
//#include "../../util/tuple_expansion/for_each.h"
#include <carl/util/tuple_util.h>
#include <carl/interval/Interval.h>

namespace hypro
{

template<typename Number>
class Location;

template<typename Number, typename Representation, typename ...Rargs>
class State
{
  protected:
    const Location<Number>* mLoc = nullptr; // Todo: Check if the location pointer is really needed.
    std::vector<boost::variant<Representation,Rargs...>> mSets;
    std::vector<representation_name> mTypes;
    carl::Interval<Number> mTimestamp = carl::Interval<Number>::unboundedInterval();
    bool mIsEmpty = false;

  public:
    State() = default;

    State(const State<Number,Representation,Rargs...>& orig) :
    	mLoc(orig.getLocation()),
    	mSets(orig.getSets()),
    	mTypes(orig.getTypes()),
    	mTimestamp(orig.getTimestamp())
    {}

    State(State<Number,Representation,Rargs...>&& orig) :
    	mLoc(orig.getLocation()),
    	mSets(orig.getSets()),
    	mTypes(orig.getTypes()),
    	mTimestamp(orig.getTimestamp())
    {}

    State<Number,Representation,Rargs...>& operator=(const State<Number,Representation,Rargs...>& orig) {
    	mLoc = orig.getLocation();
    	mSets = orig.getSets();
    	mTypes = orig.getTypes();
    	mTimestamp = orig.getTimestamp();
    	return *this;
    }

    State<Number,Representation,Rargs...>& operator=(State<Number,Representation,Rargs...>&& orig) {
    	mLoc = orig.getLocation();
    	mSets = orig.getSets();
    	mTypes = orig.getTypes();
    	mTimestamp = orig.getTimestamp();
    	return *this;
    }

    State(const Location<Number>* _loc) : mLoc(_loc) { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc,
    		const Representation& _rep,
    		const Rargs... sets,
    		const carl::Interval<Number>& _timestamp = carl::Interval<Number>::unboundedInterval())
    	: mLoc(_loc)
    	, mTimestamp(_timestamp)
    {
    	assert(mLoc != nullptr);
    	mSets.push_back(_rep);
    	mTypes.push_back(Representation::type());
    	// parameter pack expansion
    	int dummy[sizeof...(Rargs)] = { (mSets.push_back(sets), 0)... };
    	int dummy2[sizeof...(Rargs)] = { (mTypes.push_back(sets.type()), 0)... };
    }

    const Location<Number>* getLocation() const { assert(mLoc != nullptr); return mLoc; }
    std::size_t getNumberSets() const { assert(mSets.size() == mTypes.size()); return mSets.size(); }

    const auto& getSet(std::size_t i = 0) const;
    auto& rGetSet(std::size_t i = 0);
    representation_name getSetType(std::size_t i = 0) const { return mTypes.at(i); }

    //Representation& rGetSet() { return mSet; }
    const std::vector<boost::variant<Representation,Rargs...>>& getSets() const { return mSets; }
    const carl::Interval<Number>& getTimestamp() const { return mTimestamp; }

    bool isEmpty() const { return mIsEmpty; }
    void setLocation(const Location<Number>* l) { assert(l != nullptr); mLoc = l; }

    template<typename R>
    void setSet(const R& s, std::size_t i = 0) { mSets[i] = s; mTypes[i] = R::type(); }
    void setTimestamp(carl::Interval<Number> t) { mTimestamp = t; }
    void setSets(const std::vector<boost::variant<Representation,Rargs...>>& sets) { mSets = sets; }

    void addTimeToClocks(Number t);
    State<Number,Representation,Rargs...> aggregate(const State<Number,Representation,Rargs...>& in) const;
    std::pair<bool,State<Number,Representation,Rargs...>> intersect(const Condition<Number>& in) const;
    State<Number,Representation,Rargs...> applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, Number timeStepSize ) const;

    friend ostream& operator<<(ostream& out, const State<Number,Representation,Rargs...>& state) {
		#ifdef HYPRO_USE_LOGGING
    	//out << "location: " << state.mLoc->getName() << " at timestamp " << state.mTimestamp << std::endl;
    	//out << "Set: " << convert<Number,double>(Converter<Number>::toBox(state.getSet())) << std::endl;
    	out << "Other sets: " << std::endl;
    	for(int i = 0; i < sizeof...(Rargs); ++i)
    		out << convert<Number,double>(boost::get<Rargs>(mSets)) << std::endl;
    	out << "Clock Set: " << convert<Number,double>(state.mClockAssignment);
		#endif
    	return out;
    }

    friend bool operator==(const State<Number,Representation,Rargs...>& lhs, const State<Number,Representation,Rargs...>& rhs) {
    	// quick checks first
    	if (lhs.getNumberSets() != rhs.getNumberSets() || lhs.mLoc != rhs.mLoc || lhs.mTimestamp != rhs.mTimestamp) {
    		return false;
    	}

    	for(std::size_t i = 0; i < lhs.getNumberSets(); ++i) {
    		if( lhs.getType(i) != rhs.getType(i) || lhs.getSet(i) != rhs.getSet(i)) {
    			return false;
    		}
    	}
    	return true;
    }

    friend bool operator!=(const State<Number,Representation,Rargs...>& lhs, const State<Number,Representation,Rargs...>& rhs) {
    	return !(lhs == rhs);
    }

};
}

#include "State.tpp"
