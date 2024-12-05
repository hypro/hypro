/**
 * @file AnalysisNode.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../representations/GeometricObjectBase.h"
#include "../../util/logging/Logger.h"
#include "../../util/plotting/Plotter.h"
#include "../reachability/ReachNNMethod.h"

namespace hypro {
namespace reachability {

// Idea: also the Representation type could be implemented by template classes
// Class for representing using Starsets one Node in the reachability graph.
template <typename Number>
class ReachabilityNode {
  private:
	bool mIsLeaf;	   // data holder to fast check if a node is a leaf node
	bool mIsSafe;	   // data holder to check if a node is a safe node
	bool mIsComputed;  // data holder to check the computation of the node is finished (i.e. it has all its childs)

	bool mHasParent;
	ReachabilityNode<Number>* mParent;
	std::vector<ReachabilityNode<Number>*> mChildren;
		
	int mLayerNumber;	// the number of layer in the original NNet
	int mNeuronNumber;	// the number of neuron in the current layer

	NN_REACH_METHOD mMethod;
	Starset<Number> mRepresentation;
	// std::vector<Number> mLowerBounds;  // consider changing this to only lower/upper bound at the given dimension
	// std::vector<Number> mUpperBounds;

	hypro::Plotter<Number>& mPlotter;

  public:
	// constructors and destructor
	ReachabilityNode();
	ReachabilityNode( Starset<Number> representation, NN_REACH_METHOD method, int layerNumber, int neuronNumber );
	// ~ReachabilityNode();

	// getter and setter methods
	bool isLeaf() const;
	void setLeaf( bool isLeaf );
	bool isSafe() const;
	void setSafe( bool isSafe );
	bool isComputed() const;
	void setComputed( bool isComputed );

	bool hasParent() const;
	void setHasParent( bool hasParent );
	bool hasChild(int index) const;
	int getNumberOfChildren() const;

	ReachabilityNode<Number>* getParent() const;
	void setParent( ReachabilityNode<Number>* parent );
	ReachabilityNode<Number>* getChild(int index) const;
	void setChild( int index, ReachabilityNode<Number>* child );
	void addChild(ReachabilityNode<Number>* child );
	void removeAllChildren();
	
	int layerNumber() const;
	int neuronNumber() const;

	NN_REACH_METHOD method() const;
	void setMethod( NN_REACH_METHOD method );

	Starset<Number> representation() const;
	void setRepresentation( const Starset<Number>& representation );

	// functionalities
	bool checkSafeRecursive( Starset<Number> currentSet, int i, const std::vector<HPolytope<Number>>& safeSets ) const;
	bool checkSafe( const std::vector<HPolytope<Number>>& safeSets ) const;

	// utility methods
	void plot( bool holdOn = false, size_t color = 0xCC071E ) const;  // allow to plot only if the representation is two dimensional
																	  // when holdOn is true, we do not create the plot, only add the object to it
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityNode.tpp"