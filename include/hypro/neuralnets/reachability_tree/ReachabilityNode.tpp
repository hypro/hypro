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
	, mChildren(std::vector<ReachabilityNode<Number>*>())
	, mPlotter( hypro::Plotter<Number>::getInstance() )
	, mCounterExample(Point<Number>()) {}

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
bool ReachabilityNode<Number>::hasChild(int index) const{
	return 0 <= index && index < mChildren.size();
}

template <typename Number>
int ReachabilityNode<Number>::getNumberOfChildren() const{
	return mChildren.size();
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
ReachabilityNode<Number>* ReachabilityNode<Number>::getChild(int index) const {
	assert(0 <= index && index < mChildren.size());
	return mChildren[index];
}

template <typename Number>
void ReachabilityNode<Number>::setChild( int index, ReachabilityNode<Number>* child ){
	assert(0 <= index && index < mChildren.size());
	mChildren[index] = child;
}

template <typename Number>
void ReachabilityNode<Number>::addChild(ReachabilityNode<Number>* child ){
	mChildren.push_back(child);
}

template <typename Number>
void ReachabilityNode<Number>::removeAllChildren(){
	mChildren.clear();
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
bool ReachabilityNode<Number>::hasCounterExample() const{
	return mCounterExample.dimension() > 0;
} 
template <typename Number>
Point<Number> ReachabilityNode<Number>::getCounterExample() const{
	return mCounterExample;
}

template <typename Number>
bool ReachabilityNode<Number>::checkSafeRecursive( Starset<Number> currentSet, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) {
	EvaluationResult<Number> result = z3GetCounterexample( currentSet.shape(), currentSet.limits(), currentSet.generator(), currentSet.center(), safeSetMatrices, safeSetVectors);
	
	if(result.errorCode == SOLUTION::FEAS){
		mCounterExample = Point<Number>(currentSet.generator() * result.optimumValue + currentSet.center());
		return false;
	}

	assert(result.errorCode == SOLUTION::INFEAS && "leaf not safe and not unsafe");
	return true;
}

template <typename Number>
bool ReachabilityNode<Number>::checkSafe( const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) {
	// if the node is a leaf, we should check if the representation is only in the safe region (which is a non-convex set, DNF)
	if ( mIsLeaf) {
		return hasCounterExample() ? false : checkSafeRecursive( mRepresentation, safeSetMatrices, safeSetVectors );
	} 

	// if the node is not a leaf, then it safetiness depends on the children
	for (ReachabilityNode<Number>* child : mChildren){
		if(!(child->checkSafe(safeSetMatrices, safeSetVectors))){
			return false;
		}
	}

	return true;
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
