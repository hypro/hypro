
#pragma once

#include "Visitors.h"
#include "lib/datastructures/ReachTree/types.h"         //???
#include "lib/utils/types.h"                            //???
#include <carl/interval/Interval.h>
#include "../../representations/GeometricObject.h"

namespace hypro
{

template<typename Number>
class Location;

template<typename Number>
class State
{
public:
	using discreteSetRepresentation = Box<Number>;
	using clockSetRepresentation = Box<Number>;
  protected:
    const Location<Number>* mLoc = nullptr; // Todo: Check if the location pointer is really needed.
    RepresentationVariant mSet;
    representation_name mSetRepresentationName;
    RepresentationVariant mDiscreteAssignment;
    RepresentationVariant mClockAssignment;
    carl::Interval<Number> mTimestamp = carl::Interval<Number>::unboundedInterval();
    bool mHasClocks = false;
    bool mHasDiscreteVariables = false;
    bool mIsEmpty = false;

  public:
    State() = default;

    State(const State<Number>& orig) :
    	mLoc(orig.getLocation()),
    	mSet(orig.getSet()),
    	mSetRepresentationName(orig.getSetRepresentation()),
    	mDiscreteAssignment(orig.getDiscreteAssignment()),
    	mClockAssignment(orig.getClockAssignment()),
    	mTimestamp(orig.getTimestamp()),
    	mHasClocks(orig.hasClockVariables()),
    	mHasDiscreteVariables(orig.hasDiscreteVariables())
    {}

    State(State<Number>&& orig) :
    	mLoc(orig.getLocation()),
    	mSet(orig.getSet()),
    	mSetRepresentationName(orig.getSetRepresentation()),
    	mDiscreteAssignment(orig.getDiscreteAssignment()),
    	mClockAssignment(orig.getClockAssignment()),
    	mTimestamp(orig.getTimestamp()),
    	mHasClocks(orig.hasClockVariables()),
    	mHasDiscreteVariables(orig.hasDiscreteVariables())
    {}

    State<Number>& operator=(const State<Number>& orig) {
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

    State<Number>& operator=(State<Number>&& orig) {
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
    State(const Location<Number>* _loc, const RepresentationVariant& _rep) : mLoc(_loc), mSet(_rep), mDiscreteAssignment() { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc, const RepresentationVariant& _rep, const carl::Interval<Number>& _timestamp) : mLoc(_loc), mSet(_rep), mDiscreteAssignment(), mTimestamp(_timestamp) { assert(mLoc != nullptr); }
    State(const Location<Number>* _loc,
    		const RepresentationVariant& _rep,
    		const RepresentationVariant& discreteAssingment,
    		const RepresentationVariant& clockAssignment,
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
    const RepresentationVariant& getSet() const { return mSet; }
    RepresentationVariant& rGetSet() { return mSet; }
    inline representation_name getSetRepresentation() const { return mSetRepresentationName; }
    const RepresentationVariant& getDiscreteAssignment() const { return mDiscreteAssignment; }
    const RepresentationVariant& getClockAssignment() const { return mClockAssignment; }
    const carl::Interval<Number>& getTimestamp() const { return mTimestamp; }

    bool hasClockVariables() const { return mHasClocks; }
    bool hasDiscreteVariables() const { return mHasDiscreteVariables; }
    bool isEmpty() const { return mIsEmpty; }

    void setLocation<Number>(const Location<Number>* l) { assert(l != nullptr); mLoc = l; }
    void setSet(const RepresentationVariant& s) { mSet = s; }
    void setSetRepresentation(representation_name n) { mSetRepresentationName = n; }
    void setTimestamp(carl::Interval<Number> t) { mTimestamp = t; }
    void setDiscreteAssignment(const RepresentationVariant& d) { mDiscreteAssignment = d; mHasDiscreteVariables = true;}
    void setClockAssignment(const RepresentationVariant& c) { mClockAssignment = c; mHasClocks = true;}

    void addTimeToClocks(Number t);
    State aggregate(const State<Number>& in) const;
    std::pair<bool,State> intersect(const State<Number>& in) const;
    State applyTimeStep(const matrix_t<Number>& trafoMatrix, const vector_t<Number>& trafoVector, Number timeStepSize ) const;

    friend ostream& operator<<(ostream& out, const State<Number>& state) {
		#ifdef HYPRO_USE_LOGGING
    	//out << "location: " << state.mLoc->getName() << " at timestamp " << state.mTimestamp << std::endl;
    	out << "Set: " << convert<Number,double>(boost::get<Box<Number>>(boost::apply_visitor(genericConversionVisitor<RepresentationVariant>(representation_name::box), state.getSet()))) << std::endl;
    	out << "Discrete Set: " << boost::get<discreteSetRepresentation>(state.mDiscreteAssignment) << std::endl;
    	out << "Clock Set: " << boost::get<clockSetRepresentation>(state.mClockAssignment);
		#endif
    	return out;
    }

    friend bool operator==(const State<Number>& lhs, const State<Number>& rhs) {
    	return ( lhs.mLoc == rhs.mLoc &&
    			 lhs.mSet == rhs.mSet &&
    			 lhs.mSetRepresentationName == rhs.mSetRepresentationName &&
    			 lhs.mDiscreteAssignment == rhs.mDiscreteAssignment &&
    			 lhs.mClockAssignment == rhs.mClockAssignment &&
    			 lhs.mTimestamp == rhs.mTimestamp);
    }

    friend bool operator!=(const State<Number>& lhs, const State<Number>& rhs) {
    	return !(lhs == rhs);
    }

};
}

#include "State.tpp"
