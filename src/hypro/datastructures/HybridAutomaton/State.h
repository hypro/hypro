
#pragma once

#include "../../representations/types.h"
#include "../../representations/GeometricObject.h"
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
    std::vector<boost::variant<Representation,Rargs...>> mSets; // Todo: Initialize to right size.
    carl::Interval<Number> mTimestamp = carl::Interval<Number>::unboundedInterval();
    bool mIsEmpty = false;

  public:
    State() = default;

    State(const State<Number,Representation,Rargs...>& orig) :
    	mLoc(orig.getLocation()),
    	mSets(orig.getSets()),
    	mTimestamp(orig.getTimestamp())
    {}

    State(State<Number,Representation,Rargs...>&& orig) :
    	mLoc(orig.getLocation()),
    	mSets(orig.getSets()),
    	mTimestamp(orig.getTimestamp())
    {}

    State<Number,Representation,Rargs...>& operator=(const State<Number,Representation,Rargs...>& orig) {
    	mLoc = orig.getLocation();
    	mSets = orig.getSets();
    	mTimestamp = orig.getTimestamp();
    	return *this;
    }

    State<Number,Representation,Rargs...>& operator=(State<Number,Representation,Rargs...>&& orig) {
    	mLoc = orig.getLocation();
    	mSets = orig.getSets();
    	mTimestamp = orig.getTimestamp();
    	return *this;
    }

    State(const Location<Number>* _loc) : mLoc(_loc) { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc, const Representation& _rep) : mLoc(_loc), mSets() { mSets.push_back(_rep); assert(mLoc != nullptr); }
    State(const Location<Number>* _loc,
    		const Representation& _rep,
    		const Rargs... sets,
    		const carl::Interval<Number>& _timestamp)
    	: mLoc(_loc)
    	, mTimestamp(_timestamp)
    {
    	mSets.push_back(boost::variant<Representation,Rargs...>(sets...));
    	assert(mLoc != nullptr);
    }

    const Location<Number>* getLocation() const { assert(mLoc != nullptr); return mLoc; }
    //const Representation& getSet() const { return mSet; }
    //Representation& rGetSet() { return mSet; }
    const std::vector<boost::variant<Representation,Rargs...>>& getSets() const { return mSets; }
    const carl::Interval<Number>& getTimestamp() const { return mTimestamp; }

    bool isEmpty() const { return mIsEmpty; }

    void setLocation(const Location<Number>* l) { assert(l != nullptr); mLoc = l; }
    //void setSet(const Representation& s) { mSet = s; }
    void setTimestamp(carl::Interval<Number> t) { mTimestamp = t; }
    void setSets(const std::vector<boost::variant<Representation,Rargs...>>& sets) { mSets = sets; }

    void addTimeToClocks(Number t);
    State<Number,Representation,Rargs...> aggregate(const State<Number,Representation,Rargs...>& in) const;
    std::pair<bool,State<Number,Representation,Rargs...>> intersect(const State<Number,Representation,Rargs...>& in) const;
    State<Number,Representation,Rargs...> applyTimeStep(const matrix_t<Number>& trafoMatrix, const vector_t<Number>& trafoVector, Number timeStepSize ) const;

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
    	return ( lhs.mLoc == rhs.mLoc &&
    			 //lhs.mSet == rhs.mSet && // TODO: Add expansion to varyadic template sets.
    			 lhs.mTimestamp == rhs.mTimestamp);
    }

    friend bool operator!=(const State<Number,Representation,Rargs...>& lhs, const State<Number,Representation,Rargs...>& rhs) {
    	return !(lhs == rhs);
    }

};
}

#include "State.tpp"
