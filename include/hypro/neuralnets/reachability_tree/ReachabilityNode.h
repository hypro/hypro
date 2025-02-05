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
#include "ReachabilitySettings.h"

namespace hypro {
namespace reachability {

// Idea: also the Representation type could be implemented by template classes
// Class for representing using Starsets one Node in the reachability graph.
template <typename Number>
class ReachabilityNode {
  private:
	bool mIsLeaf;	   // data holder to fast check if a node is a leaf node
	bool mIsSafe;	   // data holder to check if a node is a safe node
	bool mIsComputed;  // data holder to check the computation of the node is finished (i.e. it has all its children)

	bool mHasParent;
	ReachabilityNode<Number>* mParent;
	std::vector<ReachabilityNode<Number>*> mChildren;
		
	int mLayerNumber;	// the number of layer in the original NNet
	int mNeuronNumber;	// the number of neuron in the current layer

	NN_REACH_METHOD mMethod;
	Starset<Number> mRepresentation;
	bool mHasCounterExample;
	bool mHasCounterExampleAlpha;
	Point<Number> mCounterExample; // a counterexample, if node is a leaf and unsafe, the empty point otherwise
	Point<Number> mCounterExampleAlpha; // the predicate value corresponding to the counterexample
	hypro::Plotter<Number>& mPlotter;


	// Returns a pair (x,alpha) where x is an counterexample (or the empty point if it does not exist) and alpha is the corresponding predicate value (if it is calculated and the empty point otherwise)
	std::pair<Point<Number>,Point<Number>> _checkSafetyZ3SmallRepresentation(Starset<Number> set,  const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) const;
	std::pair<Point<Number>,Point<Number>> _checkSafetyZ3(Starset<Number> set, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) const;
	std::pair<Point<Number>,Point<Number>> _checkSafetyRandom(Starset<Number> set, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, int iterations) const;

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
	bool hasCounterExample() const;
	Point<Number> getCounterExample() const;
	bool hasCounterExampleAlpha() const;
	Point<Number> getCounterExampleAlpha() const;

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
	bool checkSafeRecursive( Starset<Number> currentSet,  const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, COUNTEREXAMPLE_STRATEGY strategy);
	bool checkSafe(  const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, COUNTEREXAMPLE_STRATEGY strategy = COUNTEREXAMPLE_STRATEGY::Z3_BASIC );

	// utility methods
	void plot( bool holdOn = false, size_t color = 0xCC071E ) const;  // allow to plot only if the representation is two dimensional
																	  // when holdOn is true, we do not create the plot, only add the object to it
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityNode.tpp"