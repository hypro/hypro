/*
 * Class that describes one transition of a hybrid automaton.
 * File:   transition.h
 * Author: stefan & ckugler
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Condition.h"
#include "Location.h"
#include "Reset.h"
#include <carl/interval/Interval.h>
#include "Label.h"
#include "HybridAutomaton.h"

namespace hypro
{
enum Aggregation { none=0, boxAgg, parallelotopeAgg };

template<typename Number>
class Location;

/**
 * @brief      Class for transition.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Transition
{
  private:
    Location<Number>* mSource = nullptr; /// Pointer to the source location.
    Location<Number>* mTarget = nullptr; /// Pointer to the target location.
    Condition<Number> mGuard; /// Guard condition enabling the transition if satisfied.
    Reset<Number> mReset; /// Reset function.
    Aggregation mAggregationSetting = Aggregation::none; /// Aggregation settings.
    bool mUrgent = false; /// Flag if transition is urgent.
    Number mTriggerTime = Number(-1); /// Trigger-time: if positive acts as an additional guard.
    std::set<Label> mLabels;

  public:

  	/**
  	 * @brief      Default constructor.
  	 */
    Transition() = default;

    /**
     * @brief      Copy constructor.
     * @param[in]  orig  The original.
     */
    Transition(const Transition<Number>& orig) = default;

    /**
     * @brief      Move constructor.
     * @param[in]  orig  The original.
     */
    Transition(Transition<Number>&& orig) = default;

    /**
     * @brief      Copy assignment operator.
     * @param[in]  orig  The original.
     * @return     A copy of the passed transition.
     */
    Transition& operator=(const Transition<Number>& orig) = default;

    /**
     * @brief      Move assignment operator.
     * @param[in]  orig  The original.
     * @return     Result.
     */
    Transition& operator=(Transition<Number>&& orig) = default;

    /**
     * @brief      Destroys the object.
     */
    ~Transition() {}

    /**
     * @brief      Constructor from source and target location.
     * @param      source  The source
     * @param      target  The target
     */
    Transition(Location<Number>* source, Location<Number>* target)
        : mSource(source), mTarget(target), mGuard(), mReset(), mAggregationSetting(), mUrgent(false)
    {}

    /**
     * @brief      Full constructor for basic transition.
     * @param      source  The source.
     * @param      target  The target.
     * @param[in]  guard   The guard.
     * @param[in]  reset   The reset.
     */
    Transition(Location<Number>* source, Location<Number>* target, const Condition<Number>& guard, const Reset<Number>& reset)
        : mSource(source), mTarget(target), mGuard(guard), mReset(reset), mAggregationSetting(), mUrgent(false)
    {}


    Location<Number>* getSource() const { assert( mSource != nullptr ); return mSource; }
    Location<Number>* getTarget() const { assert( mTarget != nullptr ); return mTarget; }
    const Condition<Number>& getGuard() const { return mGuard; }
    const Reset<Number>& getReset() const { return mReset; }
    Aggregation getAggregation() const { return mAggregationSetting; }
    Number getTriggerTime() const { return mTriggerTime; }
    bool isUrgent() const { return mUrgent; }
    bool isTimeTriggered() const { return mTriggerTime >= 0; }
    bool hasIdentityReset() const { return mReset.isIdentity(); }
    std::set<Label> getLabels() const { return mLabels; }

    void setSource(Location<Number>* source) { mSource = source; }
    void setTarget(Location<Number>* target) { mTarget = target; }
    void setGuard(const Condition<Number>& guard) { mGuard = guard; }
    void setReset(const Reset<Number>& val) { mReset = val; }
    void setAggregation(Aggregation agg) { mAggregationSetting = agg; }
    void setUrgent(bool urgent = true) { mUrgent = urgent; }
    void setTriggerTime(Number t) { mTriggerTime = t; }
    void setLabels(const std::set<Label>& labels) { mLabels = labels; }
    void addLabel(const Label& lab) { mLabels.insert(lab); }

    std::string getDotRepresentation(const std::vector<std::string>& vars) const {
    	std::stringstream o;
    	o << this->getSource()->getId() << " -> " << this->getTarget()->getId();
    	if(getLabels().size() != 0 || (mReset.size() > 0 && !mReset.isIdentity()) || mGuard.size() != 0) {
    		o << "[label=< <TABLE>";
	    	// sync labels
	    	for(const auto& l : getLabels()) {
	    		o << "<TR><TD>" << l << "</TD></TR>";
	    	}
	    	// guard
			o << mGuard.getDotRepresentation(vars);
			// reset
			if(mReset.size() > 0 && !mReset.isIdentity()) {
				const matrix_t<Number>& reset = mReset.getMatrix();
				o << "<TR><TD ROWSPAN=\"" << reset.rows() << "\">";
				for(unsigned i = 0; i < reset.rows(); ++i) {
					o << vars[i] << "' = ";
					bool allZero = true;
					for(unsigned j = 0; j < reset.cols(); ++j) {
						if(reset(i,j) != 0) {
							o << reset(i,j) << "*" << vars[j] << " + ";
							allZero = false;
						}
					}
					if(mReset.getVector()(i) != 0 || allZero) o << " + " << mReset.getVector()(i);
					if(i < reset.rows() -1)
						o << "<BR/>";
				}
				o << "</TD>";
				o << "</TR>";
			}
	    	o << "</TABLE>>];";
    	}
    	o << "\n";
    	return o.str();
    }

	/**
	 * @brief      Determines if this composed of rhs and a potential rest.
	 * @details    Checks whether this transition can be the result of a parallel composition where rhs was part of one composite.
	 *
	 * @param[in]  rhs       The right hand side
	 * @param[in]  rhsVars   The right hand side variables
	 * @param[in]  thisVars  The variables of this
	 *
	 * @return     True if composed of, False otherwise.
	 */
    bool isComposedOf(const Transition<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars) const {
    	// compare source and target location
    	if(this->getSource()->getName().find(rhs.getSource()->getName()) == std::string::npos ||
    		this->getTarget()->getName().find(rhs.getTarget()->getName()) == std::string::npos) {
    		//std::cout << "source or target did not match." << std::endl;
    		return false;
    	}

    	// compare guard constraints. As the order is not fixed, we consider each row, one by one and try to match rows (outer two loops).
    	// This is similar to the invariant comparison in Location.tpp
    	if(rhs.getGuard().size() != 0 ) {
			if(this->getGuard().size() == 0 ) {
				//std::cout << "guards do not match." << std::endl;
				return false;
			}
			//std::cout << "Compare guards " << rhs.getGuard().getMatrix() << " <= " << rhs.getGuard().getVector() << " and " << this->getGuard().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;

			// try to find matching rows.
			for(Eigen::Index rowI = 0; rowI != rhs.getGuard().getMatrix().rows(); ++rowI) {
				//std::cout << "original row " << rowI << std::endl;
				bool foundConstraint = false;
				for(Eigen::Index rowPos = 0; rowPos != this->getGuard().getMatrix().rows(); ++rowPos) {
					bool allMatched = true;
					for(Eigen::Index colI = 0; colI != rhs.getGuard().getMatrix().cols(); ++colI) {
						//std::cout << "original col " << colI << std::endl;
						// find corresponding positions in the current flow matrix
						Eigen::Index colPos = 0;
						while(thisVars[colPos] != rhsVars[colI]) ++colPos;
						//std::cout << "matching col " << colPos << std::endl;
						if(this->getGuard().getMatrix()(rowPos,colPos) != rhs.getGuard().getMatrix()(rowI,colI)) {
							allMatched = false;
							break;
						}
					}
					// also compare constants.
					if(allMatched) {
						if(this->getGuard().getVector()(rowPos) == rhs.getGuard().getVector()(rowI)) {
							//std::cout << "matched row " << rowPos << std::endl;
							foundConstraint = true;
							break;
						}
					}
				}
				if(!foundConstraint) {
					//std::cout << "Cound not find invariant constraint." << std::endl;
					return false;
	 			}
			}
		}

    	// compare reset function:
    	// Find corresponding rows, then compare relevant entries.
		for(Eigen::Index rowI = 0; rowI != rhs.getReset().getMatrix().rows(); ++rowI) {
			Eigen::Index rowPos = 0;
			//std::cout << "Search for: " << rhsVars[rowI] << std::endl;
			while(thisVars[rowPos] != rhsVars[rowI]) ++rowPos;
			for(Eigen::Index colI = 0; colI != rhs.getReset().getMatrix().cols(); ++colI) {
				// find corresponding positions in the current reset matrix
				Eigen::Index colPos = 0;
				while(thisVars[colPos] != rhsVars[colI]) ++colPos;
				//std::cout << "rowPos " << rowPos << ", rowI " << rowI << ", colPos " << colPos << ", colI " << colI << std::endl;
				if(this->getReset().getMatrix()(rowPos,colPos) != rhs.getReset().getMatrix()(rowI,colI)) {
					//std::cout << "reset matrix entries do not match." << std::endl;
					return false;
				}
			}

			// compare constant part (b)
			if(this->getReset().getVector()(rowPos) != rhs.getReset().getVector()(rowI)) {
				//std::cout << "constant parts do not match." << std::endl;
				return false;
			}
		}

    	return true;
    }

    /**
     * @brief      Outstream operator.
     * @param      ostr  The outstream.
     * @param[in]  t     The transition.
     * @return     Reference to the outstream.
     */
    friend std::ostream& operator<<(std::ostream& ostr, const Transition<Number>& t) {
		#ifdef HYPRO_LOGGING
	    ostr << "transition(" << std::endl
	          << "\t Source = " << t.getSource()->getId() << std::endl
	          << "\t Target = " << t.getTarget()->getId() << std::endl
	          << "\t urgent = " << t.isUrgent() << std::endl
	          << "\t Labels = ";
	    for(const auto& label : t.getLabels()) ostr << label;
	    ostr << std::endl;
	    ostr  << "\t Guard = " << t.getGuard() << std::endl
	          << "\t Reset = " << t.getReset() << std::endl
	          << ")";
		#endif
	    return ostr;
    }

    /**
     * @brief      Equality comparison operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True if both transitions are equal, false otherwise.
     */
    friend bool operator==(const Transition<Number>& lhs, const Transition<Number>& rhs) {
    	if( (*lhs.mSource != *rhs.mSource) ||
			(*lhs.mTarget != *rhs.mTarget) ||
			(lhs.mUrgent != rhs.mUrgent) ||
			(lhs.mGuard != rhs.mGuard) ||
			(lhs.mReset != rhs.mReset) ||
      (lhs.mLabels != rhs.mLabels)) {
			return false;
		}

		return true;
    }
};

template<typename Number, typename State>
Transition<Number>* parallelCompose(const Transition<Number>* lhsT
                                , const Transition<Number>* rhsT
                                , const std::vector<std::string>& lhsVar
                                , const std::vector<std::string>& rhsVar
                                , const std::vector<std::string>& haVar
                                , const HybridAutomaton<Number, State> ha
                                , const std::set<Label> lhsLabels
                                , const std::set<Label> rhsLabels) {

    assert(haVar.size() >= lhsVar.size());
    assert(haVar.size() >= rhsVar.size());

    //std::cout << "Parallel composition of transitions " << lhsT->getSource()->getName() << " -> " << lhsT->getTarget()->getName() << " and " << rhsT->getSource()->getName() << " -> " << rhsT->getTarget()->getName() << std::endl;

    Transition<Number>* t = new Transition<Number>();

    //set label
    if (lhsT->getLabels() == rhsT->getLabels()) {
        //std::cout << "a" << std::endl;
        t->setLabels(lhsT->getLabels());
    } else if(!(lhsT->getLabels().empty()) and rhsLabels.set::count(*(lhsT->getLabels().begin()))==0 and rhsT->getLabels().empty()) {
        //std::cout << "b" << std::endl;
        t->setLabels(lhsT->getLabels());
    } else if(!(rhsT->getLabels().empty()) and lhsLabels.set::count(*(rhsT->getLabels().begin()))==0 and lhsT->getLabels().empty()) {
        //std::cout << "c" << std::endl;
        t->setLabels(rhsT->getLabels());
    } else {
        //std::cout << "d" << std::endl;
        delete t;
        return nullptr;
    }

    // quick test for shared resets - should be equal, otherwise do not parallel compose.
    // mapping from resultIndex to pair lhsIndex, rhsIndex of the shared variables.
    std::map<unsigned, std::pair<unsigned,unsigned>> sharedVars;
    unsigned idx = 0;
    for(const auto& var : haVar) {
    	// identify a shared variable dimension.
    	if(std::find(lhsVar.begin(), lhsVar.end(), var) != lhsVar.end() && std::find(rhsVar.begin(), rhsVar.end(), var) != rhsVar.end()) {
    		unsigned lhsIdx = 0;
    		unsigned rhsIdx = 0;
    		while(lhsVar[lhsIdx] != var) ++ lhsIdx;
    		while(rhsVar[rhsIdx] != var) ++ rhsIdx;
    		sharedVars[idx] = std::make_pair(lhsIdx,rhsIdx);
    		//std::cout << "Shared variable " << var << " at pos " << idx << " with original positions " << lhsIdx << ", " << rhsIdx << std::endl;
    	}
    	++idx;
    }
    for(const auto& varTuple : sharedVars) {
    	for(const auto& other : sharedVars) {
    		assert(lhsT->getReset().size() != 0);
    		assert(rhsT->getReset().size() != 0);
    		//std::cout << "Compare resets: " << lhsT->getReset().getMatrix() << " and " << rhsT->getReset().getMatrix() << std::endl;
    		//std::cout << "Compare resets: " << lhsT->getReset().getVector() << " and " << rhsT->getReset().getVector() << std::endl;
    		if(lhsT->getReset().getMatrix()(varTuple.second.first,other.second.first) != rhsT->getReset().getMatrix()(varTuple.second.second,other.second.second)
    			|| lhsT->getReset().getVector()(varTuple.second.first) != rhsT->getReset().getVector()(varTuple.second.second) ) {
    			//std::cout << "Delete." << std::endl;
    			delete t;
    			return nullptr;
    		}
    	}
    }

    //set target and source
    Location<Number>* source = ha.getLocation(lhsT->getSource()->getName()+'_'+rhsT->getSource()->getName());
    Location<Number>* target = ha.getLocation(lhsT->getTarget()->getName()+'_'+rhsT->getTarget()->getName());
    assert(source != nullptr);
    assert(target != nullptr);
    t->setTarget(target);
    t->setSource(source);

    //set urgent
    // Todo: is it not the case that a composed transition is urgent as soon as one of its participating transitions is urgent?
    t->setUrgent(lhsT->isUrgent() || rhsT->isUrgent());

    //set guard
    Condition<Number> haGuard = combine(lhsT->getGuard(), rhsT->getGuard(), haVar, lhsVar, rhsVar);
    t->setGuard(haGuard);

    //set reset
    //std::cout << "Reset, combine matrices: " << std::endl;
    Reset<Number> haReset = combine(lhsT->getReset(), rhsT->getReset(), haVar, lhsVar, rhsVar);
    //std::cout << "New reset function: " << haReset << std::endl;

    t->setReset(haReset);

    //set aggregation
    t->setAggregation(lhsT->getAggregation());

    return t;
}

}  // namespace hypro
