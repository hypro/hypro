#include "StructureNode.h"

using std::cout;
using std::endl;
using std::vector;

namespace hypro {
namespace reachability {

template <typename Number>
StructureNode<Number>::StructureNode( const NN_LAYER_TYPE layerType, ReachabilityNode<Number>* rootNode )
	: mParent( nullptr )
	, mIsFinal( false )
	, mOperation( REACHABILITY_OPERATION::INPUT )
	, mNextMethod( rootNode->method() )
	, mLayerType( layerType )
	, mReachNode( rootNode )
	, mChildren() {
	// Do nothing further
}

template <typename Number>
StructureNode<Number>::StructureNode( StructureNode<Number>* parent, const bool isFinal, const REACHABILITY_OPERATION operation, const NN_REACH_METHOD method, const NN_LAYER_TYPE layerType )
	: mParent( parent )
	, mIsFinal( isFinal )
	, mOperation( operation )
	, mNextMethod( method )
	, mLayerType( layerType )
	, mReachNode( nullptr )
	, mChildren() {
	// Do nothing further
}

template <typename Number>
StructureNode<Number>::StructureNode( StructureNode<Number>* node )
	: mParent( node->getParent() )
	, mIsFinal( node->isFinal() )
	, mOperation( node->getOperation() )
	, mNextMethod( node->getNextMethod() )
	, mLayerType( node->getLayerType() )
	, mReachNode( node->getReachabilityNode() )
	, mChildren() {
	assert( mReachNode == nullptr );
	for ( int i = 0; i < node->getNumberOfChildren(); i++ ) {
		mChildren.push_back( new StructureNode<Number>( node->mChildren[i] ) );
	}
}

template <typename Number>
int StructureNode<Number>::maxChildren() const {
	if ( mNextMethod == NN_REACH_METHOD::OVERAPPRX ) {
		return 1;
	}

	switch ( mLayerType ) {
		case NN_LAYER_TYPE::AFFINE:
			return 1;
		case NN_LAYER_TYPE::RELU:
		case NN_LAYER_TYPE::LEAKY_RELU:
		case NN_LAYER_TYPE::STEP_FUNCTION:
			return 2;
		case NN_LAYER_TYPE::HARD_TANH:
		case NN_LAYER_TYPE::HARD_SIGMOID:
			return 3;
		default:
			assert( false && "unknown layer type" );
			break;
	}
	return 0;
}

template <typename Number>
REACHABILITY_OPERATION StructureNode<Number>::getPotentialOperation( const int index ) const {
	switch ( mLayerType ) {
		case NN_LAYER_TYPE::AFFINE:
			return REACHABILITY_OPERATION::AFFINE;
		case NN_LAYER_TYPE::RELU:
			switch ( index ) {
				case 0:
					return REACHABILITY_OPERATION::RELU_POS;
				case 1:
					return REACHABILITY_OPERATION::RELU_NEG;
				default:
					return REACHABILITY_OPERATION::RELU_APPROX;
			}
		case NN_LAYER_TYPE::LEAKY_RELU:
			switch ( index ) {
				case 0:
					return REACHABILITY_OPERATION::LEAKY_RELU_POS;
				case 1:
					return REACHABILITY_OPERATION::LEAKY_RELU_NEG;
				default:
					return REACHABILITY_OPERATION::LEAKY_RELU_APPROX;
			}
		case NN_LAYER_TYPE::HARD_TANH:
			switch ( index ) {
				case 0:
					return REACHABILITY_OPERATION::HARD_TANH_MAX;
				case 1:
					return REACHABILITY_OPERATION::HARD_TANH_MID;
				case 2:
					return REACHABILITY_OPERATION::HARD_TANH_MIN;
				default:
					return REACHABILITY_OPERATION::HARD_TANH_APPROX;
			}
		case NN_LAYER_TYPE::HARD_SIGMOID:
			switch ( index ) {
				case 0:
					return REACHABILITY_OPERATION::HARD_SIGMOID_MAX;
				case 1:
					return REACHABILITY_OPERATION::HARD_SIGMOID_MID;
				case 2:
					return REACHABILITY_OPERATION::HARD_SIGMOID_MIN;
				default:
					return REACHABILITY_OPERATION::HARD_SIGMOID_APPROX;
			}
		case NN_LAYER_TYPE::STEP_FUNCTION:
			switch ( index ) {
				case 0:
					return REACHABILITY_OPERATION::STEP_FUNCTION_MAX;
				case 1:
					return REACHABILITY_OPERATION::STEP_FUNCTION_MIN;
				default:
					return REACHABILITY_OPERATION::STEP_FUNCTION_APPROX;
			}
		default:
			assert( false && "unknown layer type" );
			break;
	}
	return REACHABILITY_OPERATION::DEFAULT;
}

template <typename Number>
void StructureNode<Number>::removeAssociatedReachabilityNodes() {
	mReachNode = nullptr;
	for ( StructureNode<Number>* child : mChildren ) {
		child->removeAssociatedReachabilityNodes();
	}
}

template <typename Number>
void StructureNode<Number>::extendToExactSubtree() {
	assert( mChildren.size() == 1 );
	mNextMethod = NN_REACH_METHOD::EXACT;
	StructureNode<Number>* subRoot = mChildren[0];
	subRoot->removeAssociatedReachabilityNodes();
	subRoot->setOperation( getPotentialOperation( 0 ) );
	for ( int i = 1; i < maxChildren(); i++ ) {
		mChildren.push_back( new StructureNode( subRoot ) );
		mChildren[i]->setOperation( getPotentialOperation( i ) );
	}
}

template <typename Number>
void StructureNode<Number>::correctChildren() {
	if ( mNextMethod == NN_REACH_METHOD::OVERAPPRX ){
		assert(mReachNode->getNumberOfChildren() == 1);
		assert(mChildren.size() == 1);
		mChildren[0]->setReachabilityNode(mReachNode->getChild(0));
		mReachNode->getChild(0)->setStructureNode(mChildren[0]);
		return;
	}
	// Associate child structure nodes and child reachability nodes
	for ( int i = 0; i < mReachNode->getNumberOfChildren(); i++ ) {
		ReachabilityNode<Number>* reachChild = mReachNode->getChild( i );
		// TODO: change the implementation of "normal" safe history and than this
		REACHABILITY_OPERATION operation;
		switch ( reachChild->getHistory().back() ) {
			case 'a':
				operation = REACHABILITY_OPERATION::AFFINE;
				break;
			case '0':
				operation = REACHABILITY_OPERATION::RELU_APPROX;
				break;
			case '1':
				operation = REACHABILITY_OPERATION::RELU_POS;
				break;
			case '2':
				operation = REACHABILITY_OPERATION::RELU_NEG;
				break;
			default:
				assert( false && "something went wrong!" );
		}

		for ( StructureNode<Number>* strucChild : mChildren ) {
			if ( strucChild->getOperation() == operation ) {
				strucChild->setReachabilityNode( reachChild );
				reachChild->setStructureNode( strucChild );
				break;
			}
		}
	}

	// Remove unused structure nodes
	vector<StructureNode<Number>*> removeChildren;
	for ( int i = 0; i < mChildren.size(); i++ ) {
		if ( mChildren[i]->getReachabilityNode() == nullptr ) {
			removeChildren.push_back( mChildren[i] );
		}
	}
	for ( StructureNode<Number>* child : removeChildren ) {
		removeChild( child );
	}
}

// Getters and Setters

template <typename Number>
StructureNode<Number>* StructureNode<Number>::getParent() const {
	return mParent;
}

template <typename Number>
void StructureNode<Number>::setParent( StructureNode<Number>* parent ) const {
	mParent = parent;
}

template <typename Number>
int StructureNode<Number>::getNumberOfChildren() const {
	return mChildren.size();
}

template <typename Number>
StructureNode<Number>* StructureNode<Number>::getChild( const int index ) const {
	assert( 0 <= index && index < mChildren.size() );
	return mChildren[index];
}

template <typename Number>
void StructureNode<Number>::addChild( StructureNode<Number>* child ) {
	mChildren.push_back( child );
}

template <typename Number>
void StructureNode<Number>::removeChild( StructureNode<Number>* child ) {
	int i;
	for ( i = 0; i < mChildren.size(); i++ ) {
		if ( mChildren[i] == child ) {
			break;
		}
	}
	if ( i < mChildren.size() ) {
		mChildren.erase( mChildren.begin() + i );
	}
}

template <typename Number>
bool StructureNode<Number>::isFinal() const {
	return mIsFinal;
}

template <typename Number>
void StructureNode<Number>::setIsFinal( const bool isFinal ) {
	mIsFinal = isFinal;
}

template <typename Number>
REACHABILITY_OPERATION StructureNode<Number>::getOperation() const {
	return mOperation;
}

template <typename Number>
void StructureNode<Number>::setOperation( const REACHABILITY_OPERATION operation ) {
	mOperation = operation;
}

template <typename Number>
NN_REACH_METHOD StructureNode<Number>::getNextMethod() const {
	return mNextMethod;
}

template <typename Number>
void StructureNode<Number>::setNextMethod( const NN_REACH_METHOD nextMethod ) {
	mNextMethod = nextMethod;
}

template <typename Number>
NN_LAYER_TYPE StructureNode<Number>::getLayerType() const {
	return mLayerType;
}

template <typename Number>
void StructureNode<Number>::setLayerType( const NN_LAYER_TYPE layerType ) {
	mLayerType = layerType;
}

template <typename Number>
ReachabilityNode<Number>* StructureNode<Number>::getReachabilityNode() const {
	return mReachNode;
}

template <typename Number>
void StructureNode<Number>::setReachabilityNode( ReachabilityNode<Number>* node ) {
	mReachNode = node;
}

}  // namespace reachability
}  // namespace hypro