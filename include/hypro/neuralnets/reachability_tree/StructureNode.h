#pragma once
#include "../../representations/GeometricObjectBase.h"
#include "../reachability/ReachNNMethod.h"
#include "../network/layers/NNLayerType.h"
#include "./ReachabilityNode.h"
#include "./ReachabilityOperations.h"

namespace hypro {
namespace reachability {

template <typename Number>
class ReachabilityNode;

template <typename Number>
class StructureNode {
  private:
	// structural tree
	StructureNode<Number>* mParent;
	std::vector<StructureNode<Number>*> mChildren;

	// information
	bool mIsFinal;						   // true iff the root corresponds to the output of the FNN
	REACHABILITY_OPERATION mOperation;	   // operation applied to the parent to calculate this node
	NN_REACH_METHOD mNextMethod;		   // the method by which children are computed
	NN_LAYER_TYPE mLayerType;			   // the type of layer this node is part of
	ReachabilityNode<Number>* mReachNode;  // reachability node containing actual computation corresponding to this structural node

	// Private Utility Methods
	/**
	 * @return the maximal amount of children given by the method and layer type
	 */
	int maxChildren() const;

	REACHABILITY_OPERATION getPotentialOperation( const int index ) const;

  public:
	/**
	 * @brief Constructor for the root node
	 */
	StructureNode( const NN_LAYER_TYPE layerType, ReachabilityNode<Number>* rootNode );

	/**
	 * @brief Constructor for non-root node
	 */
	StructureNode( StructureNode<Number>* parent, const bool isFinal, const REACHABILITY_OPERATION operation, const NN_REACH_METHOD method, const NN_LAYER_TYPE layerType );

	/**
	 * @brief Copy node and all of its children
	 */
	StructureNode( StructureNode<Number>* node );

	// Public Utility Methods
	/**
	 * @brief Sets mReachNode to null for this node and all descendence
	 */
	void removeAssociatedReachabilityNodes();

	/**
	 * @brief Copies the structural subtree of the only child the maximal amount of children times as new subtrees
	 */
	void extendToExactSubtree();

	/**
	 * @brief Associates structure node children with reachability node children and removes the rest
	 */
	void correctChildren();

	// Getters and Setters
	StructureNode<Number>* getParent() const;
	void setParent( StructureNode<Number>* parent ) const;

	int getNumberOfChildren() const;
	StructureNode<Number>* getChild( const int index ) const;
	void addChild( StructureNode<Number>* child );
	void removeChild( StructureNode<Number>* child );

	bool isFinal() const;
	void setIsFinal( const bool isFinal );

	REACHABILITY_OPERATION getOperation() const;
	void setOperation( const REACHABILITY_OPERATION operation );

	NN_REACH_METHOD getNextMethod() const;
	void setNextMethod( const NN_REACH_METHOD nextMethod );

	NN_LAYER_TYPE getLayerType() const;
	void setLayerType( const NN_LAYER_TYPE layerType );

	ReachabilityNode<Number>* getReachabilityNode() const;
	void setReachabilityNode( ReachabilityNode<Number>* node );
};
}  // namespace reachability
}  // namespace hypro

#include "StructureNode.tpp"