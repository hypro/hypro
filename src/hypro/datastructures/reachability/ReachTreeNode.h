/*
 * File:   ReachTreeNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 10:52 AM
 */
#pragma once

#include "TreeNode.h"
#include "timing/EventTimingContainer.h"
#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/State.h"
#include "../HybridAutomaton/Transition.h"
#include "../HybridAutomaton/Path.h"
#include "../../representations/GeometricObject.h"
#include "../../util/logging/Logger.h"
#include <sstream>
#include <string>

namespace hypro
{
/**
 * Maps a transition to its time intervals where the guard was satisfied. Should be updated during computation.
 */
template<typename Number>
using TTransitionTimings = std::map<Transition<Number>*, std::vector<carl::Interval<tNumber>>>;

template<typename Number>
struct RefinementSetting {
	State_t<Number> initialSet;

	EventTimingContainer<Number> mTimings;
	carl::Interval<tNumber> entryTimestamp = carl::Interval<tNumber>::emptyInterval(); // The (local) timestamp of entry. TODO: Isn't the semantics like "time spent"?
	bool fullyComputed = false;
	bool isDummy = true; // Used in case we skip a certain strategy setting to fill the gaps. This means that the initial
	                      // set is not yet set. TODO: Do we actually need this? Only in case we can overstep certain settings, right?
	bool isEmpty = false;
	bool hitBadStates = false;	/// denotes that this setup lead to an intersection with the bad states. Currently only used for tree
	                          	/// plotting.

	RefinementSetting<Number>() = default;

	RefinementSetting(const Location<Number>* loc)
		: initialSet(State_t<Number>(loc))
		, mTimings()
		, fullyComputed()
		, isDummy(false)
		, isEmpty(false)
	{	}

	RefinementSetting(const State_t<Number>& state)
		: initialSet(state)
		, mTimings()
		, fullyComputed()
		, isDummy(false)
		, isEmpty(false)
	{}

	RefinementSetting(representation_name name, const typename State_t<Number>::repVariant& set, const Location<Number>* loc)
		: initialSet(State_t<Number>(loc))
		, mTimings()
		, fullyComputed()
		, isDummy(false)
		, isEmpty(false)
	{
		mTimings.setLocation(loc);
		TRACE("hydra.datastructures","Create Refinement-Setting for location " << loc->hash() << " with representation " << name);
		switch(name) {
			case representation_name::box: {
				initialSet.setSet(boost::get<Box<Number>>(set));
				break;
			}
			case representation_name::constraint_set: {
				initialSet.setSet(boost::get<ConstraintSet<Number>>(set));
				break;
			}
			case representation_name::polytope_h: {
				initialSet.setSet(boost::get<HPolytope<Number>>(set));
				break;
			}
			case representation_name::polytope_v: {
				initialSet.setSet(boost::get<VPolytope<Number>>(set));
				break;
			}
			#ifdef HYPRO_USE_PPL
			case representation_name::ppl_polytope: {
				initialSet.setSet(boost::get<Polytope<Number>>(set));
				break;
			}
			#endif
			case representation_name::support_function: {
				initialSet.setSet(boost::get<SupportFunction<Number>>(set));
				break;
			}
			case representation_name::taylor_model: {
				assert(false);
				break;
			}
			case representation_name::zonotope: {
				initialSet.setSet(boost::get<Zonotope<Number>>(set));
				break;
			}
            case representation_name::difference_bounds: {
                initialSet.setSet(boost::get<DifferenceBounds<Number>>(set));
                break;
            }
			default:
				assert(false);
		}
	}

	RefinementSetting& operator=(const RefinementSetting& orig) {
		initialSet = orig.initialSet;
		mTimings = orig.mTimings;
		entryTimestamp = orig.entryTimestamp;
		fullyComputed = orig.fullyComputed;
		isDummy = orig.isDummy;
		isEmpty = orig.isEmpty;
		hitBadStates = orig.hitBadStates;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const RefinementSetting& in) {
		if(in.isDummy){
			out << "Dummy.";
		} else {
			out << "Rep: " << in.initialSet.getSetType() << ", entry Time: " << in.entryTimestamp << ", fully computed: " << in.fullyComputed << ", isDummy: " << in.isDummy << ", isEmpty: " << in.isEmpty;
		}
		return out;
	}

	friend bool operator==( const RefinementSetting& lhs, const RefinementSetting& rhs ) {
		if((lhs.fullyComputed != rhs.fullyComputed) ||
			(lhs.isEmpty != rhs.isEmpty) ||
			(lhs.isDummy != rhs.isDummy) ||
			(lhs.hitBadStates != rhs.hitBadStates) ||
			(lhs.entryTimestamp != rhs.entryTimestamp) ||
			(lhs.mTimings != rhs.mTimings) ||
			(lhs.initialSet != rhs.initialSet)
			) {
			return false;
		}
		return true;
	}

	friend bool operator!=( const RefinementSetting& lhs, const RefinementSetting& rhs ) {
		return !(lhs == rhs);
	}

};


template<typename Number>
class ReachTreeNode : public TreeNode<ReachTreeNode<Number>>
{
  protected:
  	Path<Number,tNumber> mPath; /// path cache.
  	std::vector<RefinementSetting<Number>> mRefinements; /// ordered list of applied refinements.

    mutable std::mutex mutex;

  public:

  	using Node_t = typename TreeNode<ReachTreeNode<Number>>::Node_t;
  	using const_Node_t = typename TreeNode<ReachTreeNode<Number>>::const_Node_t;
  	using NodeList_t = typename TreeNode<ReachTreeNode<Number>>::NodeList_t;

    //ReachTreeNode() = default;
    ReachTreeNode(const ReachTreeNode<Number>& orig)
    	: TreeNode<ReachTreeNode<Number>>(orig)
    	, mPath(orig.getPath())
    	, mRefinements(orig.getRefinements())
    	//, mTransitionTimings(orig.getTransitionTimings())
    {}

    //ReachTreeNode(ReachTreeNode&& orig) = delete;
    //ReachTreeNode& operator=(const ReachTreeNode& orig) = delete;
    //ReachTreeNode& operator=(ReachTreeNode&& orig) = delete;

    ~ReachTreeNode() {}

    /**
     * @brief      Copy constructor.
     * @param[in]  _in   The original node.
     */


    ReachTreeNode()
        : TreeNode<ReachTreeNode<Number>>()
        , mPath()
        , mRefinements()
        //, mTransitionTimings()
    {
    }

    ReachTreeNode(const State_t<Number>& state, unsigned level = 0)
    	: TreeNode<ReachTreeNode<Number>>()
    	, mPath()
    	, mRefinements()
    	//, mTransitionTimings()
    {
    	assert(!state.getTimestamp().isEmpty());
    	mRefinements[level] = RefinementSetting<Number>(state.getSetType() ,state.getSet(), state.getLocation());
    	mRefinements[level].entryTimestamp = state.getTimestamp();
    	mRefinements[level].initialSet = state;
    }

    ReachTreeNode(const State_t<Number>& state, unsigned level, ReachTreeNode<Number>* parent)
    	: TreeNode<ReachTreeNode<Number>>()
    	, mPath()
    	, mRefinements()
    	//, mTransitionTimings()
    {
    	assert(!state.getTimestamp().isEmpty());
    	assert(state.getNumberSets() > 0);
    	//std::cout << "Create ReachTreeNode, access to state set of type " << state.getSetType() << std::endl;
    	auto tmp = RefinementSetting<Number>(state.getSetType(),state.getSet(), state.getLocation());
    	while(mRefinements.size() < level) {
    		mRefinements.push_back(RefinementSetting<Number>());
    	}
    	mRefinements.push_back(tmp);
    	mRefinements[level].entryTimestamp = state.getTimestamp();
    	mRefinements[level].initialSet = state;
    	this->setParent(parent);
    }

    std::mutex& getMutex() const { return mutex; }

    const Path<Number,tNumber>& getPath() const { return mPath; }

    const typename State_t<Number>::repVariant& getSetAtLevel(unsigned level) const;

    const State_t<Number>& getStateAtLevel(unsigned level) const;

    /**
     * @brief      Gets the timestamp of entry (i.e. global timestamp) for a certain level.
     * @param[in]  level  The level.
     * @return     The timestamp.
     */
    const carl::Interval<tNumber>& getTimestamp(unsigned level) const;

    //const Location<Number>* getLocation() const { return mLoc; }

    const std::vector<RefinementSetting<Number>>& getRefinements() const { return mRefinements; }

    std::vector<RefinementSetting<Number>>& rGetRefinements() { return mRefinements; }

    //TTransitionTimings getTransitionTimings() const { return mTransitionTimings; }

    //std::vector<carl::Interval<Number>> getTimeIntervals(Transition<Number>* t) const;

    unsigned getLatestBTLevel() const;
    unsigned getLatestFullyComputedLevel() const;

    void getLevelCnt(std::vector<std::size_t>& levels) const;

    std::vector<ReachTreeNode<Number>*> getChildrenForTransition(Transition<Number>* transition) const;

    bool isFullyComputedOnSomeLevel() const;

    void updateContent(ReachTreeNode<Number>* updatedNode);

    void addRefinement(const RefinementSetting<Number>& ref);

    void setNewRefinement(unsigned level, const RefinementSetting<Number>& ref);

    void clearRefinements() { mRefinements.clear(); }

    void convertRefinement(unsigned fromLevel, unsigned toLevel, const StrategyNode& toSettings);

    //void setInitSet(const typename State_t<Number>::repVariant& _initSet);

    void setTimestamp( unsigned level, const carl::Interval<tNumber>& timeInterval);

    //void addTransitionInterval(Transition<Number>* _trans, const carl::Interval<Number>& _timeInterval);

    void addTransitionToPath(Transition<Number>* trans, const carl::Interval<tNumber>& enabledTime) { mPath.addTransition(trans, enabledTime); }
    void addTimeStepToPath(const carl::Interval<tNumber>& timeStep) { mPath.addTimeStep(timeStep); }

    void refineIntervals();

    bool hasFixedPoint(const State_t<Number>& s, typename ReachTreeNode<Number>::Node_t skip) const;

    void setParent(ReachTreeNode<Number>* parent);

    std::size_t getDotRepresentation(std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels) const;

	template<typename N>
    friend std::ostream& operator<< (std::ostream &out, const ReachTreeNode<N> &reachTreeNode);

	template<typename N>
    friend bool operator<(const ReachTreeNode<N>& lhs, const ReachTreeNode<N>& rhs) {
    	return (lhs.getDepth() < rhs.getDepth());
    }

	template<typename N>
    friend bool operator==(const ReachTreeNode<N>& lhs, const ReachTreeNode<N>& rhs) {
    	// properties of tree node
    	if(lhs.mDepth != rhs.mDepth ||
    	    lhs.mParent != rhs.mParent ||
    	    lhs.mChildren.size() != rhs.mChildren.size())
    	{
    		return false;
    	}

    	if(lhs.mPath != rhs.mPath) {
    		return false;
    	}

    	if(lhs.mRefinements.size() != rhs.mRefinements.size()) {
    		return false;
    	}

    	for(std::size_t i = 0; i < lhs.mRefinements.size(); ++i) {
    		if(lhs.mRefinements[i] != rhs.mRefinements[i]) {
    			return false;
    		}
    	}
    	return true;
    }
};

} // hypro

#include "ReachTreeNode.tpp"
