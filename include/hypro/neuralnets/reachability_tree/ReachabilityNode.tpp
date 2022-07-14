#include "ReachabilityNode.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode() {
	// TODO: Implement this default constructor
	mPlotter = hypro::Plotter<Number>::getInstance();
}

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode( Starset<Number> representation, NN_REACH_METHOD method, int layerNumber, int neuronNumber )
	: mRepresentation( representation )
	, mMethod( method )
	, mLayerNumber( layerNumber )
	, mLayerNumber( neuronNumber )
	, mIsLeaf( false )
	, mIsSafe( false )
	, mHasParent( false )
	, mHasPosChild( false )
	, mHasNegChild( false ) {
	mPlotter = hypro::Plotter<Number>::getInstance();
}

template <typename Number>
bool ReachabilityNode<Number>::isLeaf() const {
	return mIsLeaf;
}

template <typename Number>
void ReachabilityNode<Number>::setIsLeaf( bool isLeaf ) {
	mIsLeaf = isLeaf;
}

template <typename Number>
bool ReachabilityNode<Number>::isSafe() const {
	return mIsSafe;
}

template <typename Number>
void ReachabilityNode<Number>::setIsSafe( bool isSafe ) {
	mIsSafe = isSafe;
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
void plot( bool holdOn, size_t color ) const {
	std::vector<hypro::Point<Number>> vertices = mRepresentation.vertices();
	mPlotter.addObject( vertices, color );
	if ( !holdOn ) {
		mPlotter.plot2d();
	}
}

}  // namespace reachability
}  // namespace hypro
