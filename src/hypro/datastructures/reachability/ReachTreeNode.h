/*
 * File:   ReachTreeNode.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 10:52 AM
 */
#pragma once

#include "../../representations/GeometricObjectBase.h"
#include "../../util/logging/Logger.h"
#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/Path.h"
#include "../HybridAutomaton/State.h"
#include "../HybridAutomaton/Transition.h"
#include "SettingsProvider.h"
#include "TreeNode.h"
#include "timing/EventTimingContainer.h"

#include <sstream>
#include <string>

namespace hypro {
/**
 * Maps a transition to its time intervals where the guard was satisfied. Should be updated during computation.
 */
template <typename Number>
using TTransitionTimings = std::map<Transition<Number>*, std::vector<carl::Interval<tNumber>>>;

template <typename State>
struct RefinementSetting {
	using Number = typename State::NumberType;

	State initialSet;

	EventTimingContainer<Number> mTimings;
	carl::Interval<tNumber> entryTimestamp = carl::Interval<tNumber>::emptyInterval();	// The (local) timestamp of entry. TODO: Isn't the semantics like "time spent"?
	bool fullyComputed = false;
	bool isDummy = true;  // Used in case we skip a certain strategy setting to fill the gaps. This means that the initial
						  // set is not yet set. TODO: Do we actually need this? Only in case we can overstep certain settings, right?
	bool isEmpty = false;
	bool hitBadStates = false;	/// denotes that this setup lead to an intersection with the bad states. Currently only used for tree
								/// plotting.

	RefinementSetting() = default;
	RefinementSetting( const RefinementSetting<State>& orig ) = default;
	RefinementSetting( RefinementSetting<State>&& orig ) = default;

	explicit RefinementSetting( const Location<Number>* loc )
		: initialSet( State( loc ) )
		, mTimings()
		, fullyComputed()
		, isDummy( false )
		, isEmpty( false ) {}

	explicit RefinementSetting( const State& state )
		: initialSet( state )
		, mTimings()
		, fullyComputed()
		, isDummy( false )
		, isEmpty( false ) {}

	RefinementSetting( const State& set, const Location<Number>* )
		: initialSet( set )
		, mTimings()
		, fullyComputed()
		, isDummy( false )
		, isEmpty( false ) {}

	/*
	RefinementSetting& operator=( const RefinementSetting& orig ) {
		initialSet = orig.initialSet;
		mTimings = orig.mTimings;
		entryTimestamp = orig.entryTimestamp;
		fullyComputed = orig.fullyComputed;
		isDummy = orig.isDummy;
		isEmpty = orig.isEmpty;
		hitBadStates = orig.hitBadStates;
		return *this;
	}
	*/
	RefinementSetting& operator=( const RefinementSetting& original ) = default;

	friend std::ostream& operator<<( std::ostream& out, const RefinementSetting& in ) {
		if ( in.isDummy ) {
			out << "Dummy.";
		} else {
			out << "Rep: " << in.initialSet.getSetType() << ", entry Time: " << in.entryTimestamp << ", fully computed: " << in.fullyComputed << ", isDummy: " << in.isDummy << ", isEmpty: " << in.isEmpty;
		}
		return out;
	}

	friend bool operator==( const RefinementSetting& lhs, const RefinementSetting& rhs ) {
		if ( ( lhs.fullyComputed != rhs.fullyComputed ) ||
			 ( lhs.isEmpty != rhs.isEmpty ) ||
			 ( lhs.isDummy != rhs.isDummy ) ||
			 ( lhs.hitBadStates != rhs.hitBadStates ) ||
			 ( lhs.entryTimestamp != rhs.entryTimestamp ) ||
			 ( lhs.mTimings != rhs.mTimings ) ||
			 ( lhs.initialSet != rhs.initialSet ) ) {
			return false;
		}
		return true;
	}

	friend bool operator!=( const RefinementSetting& lhs, const RefinementSetting& rhs ) {
		return !( lhs == rhs );
	}
};

template <typename State>
class ReachTreeNode : public TreeNode<ReachTreeNode<State>> {
	using Number = typename State::NumberType;

  protected:
	Path<Number, tNumber> mPath;						 /// path cache.
	std::vector<RefinementSetting<State>> mRefinements;	 /// ordered list of applied refinements.

	mutable std::mutex mutex;

  public:
	using Node_t = typename TreeNode<ReachTreeNode<State>>::Node_t;
	using const_Node_t = typename TreeNode<ReachTreeNode<State>>::const_Node_t;
	using NodeList_t = typename TreeNode<ReachTreeNode<State>>::NodeList_t;

	//ReachTreeNode() = default;
	ReachTreeNode( const ReachTreeNode<State>& orig )
		: TreeNode<ReachTreeNode<State>>( orig )
		, mPath( orig.getPath() )
		, mRefinements( orig.getRefinements() ) {}

	//ReachTreeNode(ReachTreeNode&& orig) = delete;
	//ReachTreeNode& operator=(const ReachTreeNode& orig) = delete;
	//ReachTreeNode& operator=(ReachTreeNode&& orig) = delete;

	~ReachTreeNode() {}

	ReachTreeNode()
		: TreeNode<ReachTreeNode<State>>()
		, mPath()
		, mRefinements()
	//, mTransitionTimings()
	{
	}

	ReachTreeNode( const State& state, unsigned level = 0 )
		: TreeNode<ReachTreeNode<State>>()
		, mPath()
		, mRefinements()
	//, mTransitionTimings()
	{
		assert( !state.getTimestamp().isEmpty() );
		assert( level <= mRefinements.size() );
		//mRefinements.insert(mRefinements.begin()+level, RefinementSetting<State>( state, state.getLocation() ));
		//mRefinements[level] = RefinementSetting<State>( state, state.getLocation() );
		// append or update
		if ( level == mRefinements.size() ) {
			mRefinements.push_back( RefinementSetting<State>( state, state.getLocation() ) );
		} else {
			mRefinements[level] = RefinementSetting<State>( state, state.getLocation() );
		}

		mRefinements[level].entryTimestamp = state.getTimestamp();
		mRefinements[level].initialSet = state;
	}

	ReachTreeNode( const State& state, unsigned level, ReachTreeNode<State>* parent )
		: TreeNode<ReachTreeNode<State>>()
		, mPath()
		, mRefinements()
	//, mTransitionTimings()
	{
		assert( !state.getTimestamp().isEmpty() );
		assert( state.getNumberSets() > 0 );
		//std::cout << "Create ReachTreeNode, access to state set of type " << state.getSetType() << std::endl;
		auto tmp = RefinementSetting<State>( state, state.getLocation() );
		while ( mRefinements.size() < level ) {
			mRefinements.push_back( RefinementSetting<State>() );
		}
		mRefinements.push_back( tmp );
		mRefinements[level].entryTimestamp = state.getTimestamp();
		mRefinements[level].initialSet = state;
		this->setParent( parent );
	}

	std::mutex& getMutex() const { return mutex; }

	const Path<Number, tNumber>& getPath() const { return mPath; }

	const typename State::repVariant& getSetAtLevel( unsigned level ) const;

	const State& getStateAtLevel( unsigned level ) const;

	const State& getState() const { return getStateAtLevel( 0 ); };

	/**
     * @brief      Gets the timestamp of entry (i.e. global timestamp) for a certain level.
     * @param[in]  level  The level.
     * @return     The timestamp.
     */
	const carl::Interval<tNumber>& getTimestamp( unsigned level ) const;

	//const Location<Number>* getLocation() const { return mLoc; }

	const std::vector<RefinementSetting<State>>& getRefinements() const { return mRefinements; }

	std::vector<RefinementSetting<State>>& rGetRefinements() { return mRefinements; }

	//TTransitionTimings getTransitionTimings() const { return mTransitionTimings; }

	//std::vector<carl::Interval<Number>> getTimeIntervals(Transition<Number>* t) const;

	unsigned getLatestBTLevel() const;
	unsigned getLatestFullyComputedLevel() const;

	void getLevelCnt( std::vector<std::size_t>& levels ) const;

	std::vector<ReachTreeNode<State>*> getChildrenForTransition( Transition<Number>* transition ) const;

	bool isFullyComputedOnSomeLevel() const;

	void updateContent( ReachTreeNode<State>* updatedNode );

	void addRefinement( const RefinementSetting<State>& ref );

	void setNewRefinement( unsigned level, const RefinementSetting<State>& ref );

	void clearRefinements() { mRefinements.clear(); }

	void convertRefinement( unsigned fromLevel, unsigned toLevel );

	//void setInitSet(const typename State::repVariant& _initSet);

	void setTimestamp( unsigned level, const carl::Interval<tNumber>& timeInterval );

	//void addTransitionInterval(Transition<Number>* _trans, const carl::Interval<Number>& _timeInterval);

	void addTransitionToPath( Transition<Number>* trans, const carl::Interval<tNumber>& enabledTime ) { mPath.addTransition( trans, enabledTime ); }
	void addTimeStepToPath( const carl::Interval<tNumber>& timeStep ) { mPath.addTimeStep( timeStep ); }

	void refineIntervals();

	bool hasFixedPoint( const State& s, typename ReachTreeNode<State>::Node_t skip ) const;

	void setParent( ReachTreeNode<State>* parent );

	std::size_t getDotRepresentation( std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels ) const;

	template <typename S>
	friend std::ostream& operator<<( std::ostream& out, const ReachTreeNode<S>& reachTreeNode );

	template <typename S>
	friend bool operator<( const ReachTreeNode<S>& lhs, const ReachTreeNode<S>& rhs );

	template <typename S>
	friend bool operator==( const ReachTreeNode<S>& lhs, const ReachTreeNode<S>& rhs );
};

}  // namespace hypro

#include "ReachTreeNode.tpp"
