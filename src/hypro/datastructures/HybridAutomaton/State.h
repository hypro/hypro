
#pragma once

#include "Visitors.h"
#include <carl/interval/Interval.h>
#include "../../representations/GeometricObject.h"
#include "../../representations/types.h"

namespace hypro
{

template<typename Number>
class Location;

template<typename Number, typename Representation>
class State
{
public:
	typedef Box<Number> discreteSetRepresentation;
	typedef Box<Number> clockSetRepresentation;
  protected:
    const Location<Number>* mLoc = nullptr; // Todo: Check if the location pointer is really needed.
    Representation mSet;
    representation_name mSetRepresentationName;
    discreteSetRepresentation mDiscreteAssignment;
    clockSetRepresentation mClockAssignment;
    carl::Interval<Number> mTimestamp = carl::Interval<Number>::unboundedInterval();
    bool mHasClocks = false;
    bool mHasDiscreteVariables = false;
    bool mIsEmpty = false;

  public:
    State() = default;

    State(const State<Number,Representation>& orig) :
    	mLoc(orig.getLocation()),
    	mSet(orig.getSet()),
    	mSetRepresentationName(orig.getSetRepresentation()),
    	mDiscreteAssignment(orig.getDiscreteAssignment()),
    	mClockAssignment(orig.getClockAssignment()),
    	mTimestamp(orig.getTimestamp()),
    	mHasClocks(orig.hasClockVariables()),
    	mHasDiscreteVariables(orig.hasDiscreteVariables())
    {}

    State(State<Number,Representation>&& orig) :
    	mLoc(orig.getLocation()),
    	mSet(orig.getSet()),
    	mSetRepresentationName(orig.getSetRepresentation()),
    	mDiscreteAssignment(orig.getDiscreteAssignment()),
    	mClockAssignment(orig.getClockAssignment()),
    	mTimestamp(orig.getTimestamp()),
    	mHasClocks(orig.hasClockVariables()),
    	mHasDiscreteVariables(orig.hasDiscreteVariables())
    {}

    State<Number,Representation>& operator=(const State<Number,Representation>& orig) {
    	mLoc = orig.getLocation();
    	mSet = orig.getSet();
    	mSetRepresentationName = orig.getSetRepresentation();
    	mDiscreteAssignment = orig.getDiscreteAssignment();
    	mClockAssignment = orig.getClockAssignment();
    	mTimestamp = orig.getTimestamp();
    	mHasClocks = orig.hasClockVariables();
    	mHasDiscreteVariables = orig.hasDiscreteVariables();
    	return *this;
    }

    State<Number,Representation>& operator=(State<Number,Representation>&& orig) {
    	mLoc = orig.getLocation();
    	mSet = orig.getSet();
    	mSetRepresentationName = orig.getSetRepresentation();
    	mDiscreteAssignment = orig.getDiscreteAssignment();
    	mClockAssignment = orig.getClockAssignment();
    	mTimestamp = orig.getTimestamp();
    	mHasClocks = orig.hasClockVariables();
    	mHasDiscreteVariables = orig.hasDiscreteVariables();
    	return *this;
    }

    State(const Location<Number>* _loc) : mLoc(_loc), mSet(), mDiscreteAssignment() { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc, const Representation& _rep) : mLoc(_loc), mSet(_rep), mDiscreteAssignment() { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc, const Representation& _rep, const carl::Interval<Number>& _timestamp) : mLoc(_loc), mSet(_rep), mDiscreteAssignment(), mTimestamp(_timestamp) { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc,
    		const Representation& _rep,
    		const discreteSetRepresentation& discreteAssingment,
    		const clockSetRepresentation& clockAssignment,
    		const carl::Interval<Number>& _timestamp)
    	: mLoc(_loc)
    	, mSet(_rep)
    	, mDiscreteAssignment(discreteAssingment)
    	, mClockAssignment(clockAssignment)
    	, mTimestamp(_timestamp)
    	, mHasClocks(true)
    	, mHasDiscreteVariables(true)
    {
    	assert(mLoc != nullptr);
    }

    const Location<Number>* getLocation() const { assert(mLoc != nullptr); return mLoc; }
    const Representation& getSet() const { return mSet; }
    Representation& rGetSet() { return mSet; }
    inline representation_name getSetRepresentation() const { return mSetRepresentationName; }
    const discreteSetRepresentation& getDiscreteAssignment() const { return mDiscreteAssignment; }
    const clockSetRepresentation& getClockAssignment() const { return mClockAssignment; }
    const carl::Interval<Number>& getTimestamp() const { return mTimestamp; }

    bool hasClockVariables() const { return mHasClocks; }
    bool hasDiscreteVariables() const { return mHasDiscreteVariables; }
    bool isEmpty() const { return mIsEmpty; }

    void setLocation(const Location<Number>* l) { assert(l != nullptr); mLoc = l; }
    void setSet(const Representation& s) { mSet = s; }
    void setSetRepresentation(representation_name n) { mSetRepresentationName = n; }
    void setTimestamp(carl::Interval<Number> t) { mTimestamp = t; }
    void setDiscreteAssignment(const discreteSetRepresentation& d) { mDiscreteAssignment = d; mHasDiscreteVariables = true;}
    void setClockAssignment(const clockSetRepresentation& c) { mClockAssignment = c; mHasClocks = true;}

    void addTimeToClocks(Number t);
    State<Number,Representation> aggregate(const State<Number,Representation>& in) const;
    std::pair<bool,State<Number,Representation>> intersect(const State<Number,Representation>& in) const;
    State<Number,Representation> applyTimeStep(const matrix_t<Number>& trafoMatrix, const vector_t<Number>& trafoVector, Number timeStepSize ) const;

    friend ostream& operator<<(ostream& out, const State<Number,Representation>& state) {
		#ifdef HYPRO_USE_LOGGING
    	//out << "location: " << state.mLoc->getName() << " at timestamp " << state.mTimestamp << std::endl;
    	out << "Set: " << convert<Number,double>(Converter<Number>::toBox(state.getSet())) << std::endl;
    	out << "Discrete Set: " << convert<Number,double>(state.mDiscreteAssignment) << std::endl;
    	out << "Clock Set: " << convert<Number,double>(state.mClockAssignment);
		#endif
    	return out;
    }

    friend bool operator==(const State<Number,Representation>& lhs, const State<Number,Representation>& rhs) {
    	return ( lhs.mLoc == rhs.mLoc &&
    			 lhs.mSet == rhs.mSet &&
    			 lhs.mSetRepresentationName == rhs.mSetRepresentationName &&
    			 lhs.mDiscreteAssignment == rhs.mDiscreteAssignment &&
    			 lhs.mClockAssignment == rhs.mClockAssignment &&
    			 lhs.mTimestamp == rhs.mTimestamp);
    }

    friend bool operator!=(const State<Number,Representation>& lhs, const State<Number,Representation>& rhs) {
    	return !(lhs == rhs);
    }

};
}

#include "State.tpp"
