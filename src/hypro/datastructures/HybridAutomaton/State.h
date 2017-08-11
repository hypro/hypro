
#pragma once

#include "functors.h"
#include "Condition.h"
#include "../../representations/types.h"
#include "../../representations/GeometricObject.h"
#include "../HybridAutomaton/Visitors.h"
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
	private:
		using repVariant = boost::variant<Representation,Rargs...>;

  protected:
    const Location<Number>* mLoc = nullptr; // Todo: Check if the location pointer is really needed.
    std::vector<repVariant> mSets;
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

    const boost::variant<Representation,Rargs...>& getSet(std::size_t i = 0) const;
    boost::variant<Representation,Rargs...>& rGetSet(std::size_t i = 0);
    representation_name getSetType(std::size_t i = 0) const { return mTypes.at(i); }

    //Representation& rGetSet() { return mSet; }
    const std::vector<boost::variant<Representation,Rargs...>>& getSets() const { return mSets; }
    const std::vector<representation_name>& getTypes() const { return mTypes; }
    const carl::Interval<Number>& getTimestamp() const { return mTimestamp; }

    bool isEmpty() const { return mIsEmpty; }
    void setLocation(const Location<Number>* l) { assert(l != nullptr); mLoc = l; }

    template<typename R>
    void setSet(const R& s, std::size_t i = 0);
    void setSetType(representation_name type, std::size_t I = 0) { assert(mSets.size() < I && mTypes.size() < I);  mTypes[I] = type; }
    void setTimestamp(carl::Interval<Number> t) { mTimestamp = t; }
    void setSets(const std::vector<boost::variant<Representation,Rargs...>>& sets) { mSets = sets; }
    /**
	 * @brief      Sets the set.
	 * @details    Does not update the type for the respective position - can be used if type does not change to avoid unpacking.
	 *
	 * @param[in]  in    The set as a boost::variant.
	 * @param[in]  I     The position in the sets vector.
	 */
	void setSetDirect(const repVariant& in, std::size_t I = 0) {
		assert(I < mSets.size());
		mSets[I] = in;
	}

    void addTimeToClocks(Number t);
    State<Number,Representation,Rargs...> aggregate(const State<Number,Representation,Rargs...>& in) const;
    std::pair<bool,State<Number,Representation,Rargs...>> satisfies(const Condition<Number>& in) const;
    std::pair<bool,State<Number,Representation,Rargs...>> partiallySatisfies(const Condition<Number>& in, std::size_t I) const;
    State<Number,Representation,Rargs...> applyTimeStep(const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, Number timeStepSize ) const;
    State<Number,Representation,Rargs...> partiallyApplyTimeStep(const ConstraintSet<Number>& flow, Number timeStepSize, std::size_t I ) const;
    State<Number,Representation,Rargs...> applyTransformation(const std::vector<ConstraintSet<Number>>& trafos ) const;
    State<Number,Representation,Rargs...> partiallyApplyTransformation(const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const;
    State<Number,Representation,Rargs...> partiallyApplyTransformation(const ConstraintSet<Number>& trafo, std::size_t I ) const;

    friend ostream& operator<<(ostream& out, const State<Number,Representation,Rargs...>& state) {
		#ifdef HYPRO_LOGGING
    	out << "location: " << state.getLocation()->getName() << " at timestamp " << state.getTimestamp() << std::endl;
    	//out << "Set: " << convert<Number,double>(Converter<Number>::toBox(state.getSet())) << std::endl;
    	out << "Set: " << boost::apply_visitor(genericConversionVisitor<repVariant,Number>(representation_name::box), state.getSet()) << std::endl;
    	if(state.getNumberSets() > 1) {
    		out << "Other sets: " << std::endl;
	    	for(std::size_t i = 0; i < sizeof...(Rargs); ++i)
	    		out << state.getSet(i) << std::endl;
    	}
		#endif
    	return out;
    }

    friend bool operator==(const State<Number,Representation,Rargs...>& lhs, const State<Number,Representation,Rargs...>& rhs) {
    	// quick checks first
    	if (lhs.getNumberSets() != rhs.getNumberSets() || lhs.mLoc != rhs.mLoc || lhs.mTimestamp != rhs.mTimestamp) {
    		return false;
    	}

    	for(std::size_t i = 0; i < lhs.getNumberSets(); ++i) {
    		if( lhs.getSetType(i) != rhs.getSetType(i)) {
    			return false;
    		}
    		if(!boost::apply_visitor(genericCompareVisitor(), lhs.getSet(i), rhs.getSet(i))) {
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
