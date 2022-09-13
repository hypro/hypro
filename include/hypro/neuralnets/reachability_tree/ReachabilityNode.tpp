#include "ReachabilityNode.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode()
	: mPlotter( hypro::Plotter<Number>::getInstance() ) {}

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode( Starset<Number> representation, NN_REACH_METHOD method, int layerNumber, int neuronNumber )
	: mRepresentation( representation )
	, mMethod( method )
	, mLayerNumber( layerNumber )
	, mNeuronNumber( neuronNumber )
	, mIsLeaf( false )
	, mIsSafe( false )
	, mIsComputed( false )
	, mHasParent( false )
	, mHasPosChild( false )
	, mHasNegChild( false )
	, mPlotter( hypro::Plotter<Number>::getInstance() ) {}

// template <typename Number>
// ReachabilityNode<Number>::~ReachabilityNode() {
// 	if ( !mIsLeaf ) {
// 		if ( mHasPosChild ) {
// 			mHasPosChild = false;
// 			delete mPosChild;
// 		}
// 		if ( mHasNegChild ) {
// 			mHasNegChild = false;
// 			delete mNegChild;
// 		}
// 	}
// }

template <typename Number>
bool ReachabilityNode<Number>::isLeaf() const {
	return mIsLeaf;
}

template <typename Number>
void ReachabilityNode<Number>::setLeaf( bool isLeaf ) {
	mIsLeaf = isLeaf;
}

template <typename Number>
bool ReachabilityNode<Number>::isSafe() const {
	return mIsSafe;
}

template <typename Number>
void ReachabilityNode<Number>::setSafe( bool isSafe ) {
	mIsSafe = isSafe;
}

template <typename Number>
bool ReachabilityNode<Number>::isComputed() const {
	return mIsComputed;
}

template <typename Number>
void ReachabilityNode<Number>::setComputed( bool isComputed ) {
	mIsComputed = isComputed;
}

template <typename Number>
bool ReachabilityNode<Number>::hasParent() const {
	return mHasParent;
}

template <typename Number>
void ReachabilityNode<Number>::setHasParent( bool hasParent ) {
	mHasParent = hasParent;
}

template <typename Number>
bool ReachabilityNode<Number>::hasPosChild() const {
	return mHasPosChild;
}

template <typename Number>
void ReachabilityNode<Number>::setHasPosChild( bool hasPosChild ) {
	mHasPosChild = hasPosChild;
}

template <typename Number>
bool ReachabilityNode<Number>::hasNegChild() const {
	return mHasNegChild;
}

template <typename Number>
void ReachabilityNode<Number>::setHasNegChild( bool hasNegChild ) {
	mHasNegChild = hasNegChild;
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityNode<Number>::getParent() const {
	return mParent;
}

template <typename Number>
void ReachabilityNode<Number>::setParent( ReachabilityNode<Number>* parent ) {
	mHasParent = true;
	mParent = parent;
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityNode<Number>::getPosChild() const {
	return mPosChild;
}

template <typename Number>
void ReachabilityNode<Number>::setPosChild( ReachabilityNode<Number>* posChild ) {
	mHasPosChild = true;
	mPosChild = posChild;
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityNode<Number>::getNegChild() const {
	return mNegChild;
}

template <typename Number>
void ReachabilityNode<Number>::setNegChild( ReachabilityNode<Number>* negChild ) {
	mHasNegChild = true;
	mNegChild = negChild;
}

template <typename Number>
int ReachabilityNode<Number>::layerNumber() const {
	return mLayerNumber;
}

template <typename Number>
int ReachabilityNode<Number>::neuronNumber() const {
	return mNeuronNumber;
}

template <typename Number>
NN_REACH_METHOD ReachabilityNode<Number>::method() const {
	return mMethod;
}

template <typename Number>
void ReachabilityNode<Number>::setMethod( NN_REACH_METHOD method ) {
	mMethod = method;
}

template <typename Number>
Starset<Number> ReachabilityNode<Number>::representation() const {
	return mRepresentation;
}

template <typename Number>
void ReachabilityNode<Number>::setRepresentation( const Starset<Number>& representation ) {
	mRepresentation = representation;
}

template <typename Number>
bool ReachabilityNode<Number>::checkSafe( const std::vector<HPolytope<Number>>& safeSets ) const {
	for ( auto safeSet : safeSets ) {
		bool safe = true;
		if ( mIsLeaf ) {
			// if the node is a leaf, then we check whether the inner representation (star) is safe
			for ( auto halfspace : safeSet.constraints() ) {
				vector_t<Number> normal = halfspace.normal();
				Number offset = halfspace.offset();
				// intersect the starset with the opposite of the halfspace
				// if the result is not empty, then we know that the starset contains elements that are not in the safe set
				Starset<Number> newSet = mRepresentation.intersectHalfspace( Halfspace<Number>( -normal, -offset ) );
				if ( !newSet.empty() ) {
					safe = false;
					break;
				}
			}
		} else {
			// if the node is not a leaf, then it safetiness depends on the childs
			if ( mHasNegChild )
				safe &= mNegChild->isSafe();
			if ( mHasPosChild )
				safe &= mPosChild->isSafe();
		}

		// since the safeSets is a disjunction of conjunction of constrains, if any of the conjunctions evaluates to true, then the final result is also true
		if ( safe )
			return true;
	}

	return false;
}

template <typename Number>
void ReachabilityNode<Number>::plot( bool holdOn, size_t color ) const {
	// std::cout << mRepresentation << std::endl;
	std::vector<hypro::Point<Number>> vertices = mRepresentation.vertices();
	mPlotter.addObject( vertices, color );
	if ( !holdOn ) {
		mPlotter.plot2d( PLOTTYPE::png );
	}
}

}  // namespace reachability
}  // namespace hypro
