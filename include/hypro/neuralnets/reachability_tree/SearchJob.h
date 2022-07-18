/**
 * @file SearchJob.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ReachabilityNode.h"

namespace hypro {
namespace reachability {

template <typename Number>
class SearchJob {
  private:
	ReachabilityNode<Number>* mNode;
	std::list<std::shared_ptr<hypro::LayerBase<Number>>> mAllLayers;
	bool mIsFinalResult = false;

  public:
	SearchJob( ReachabilityNode<Number>* node, const std::list<std::shared_ptr<hypro::LayerBase<Number>>>& allLayers )
		: mNode( node )
		, mAllLayers( allLayers )
		, mIsFinalResult( false ) {}

	SearchJob( ReachabilityNode<Number>* node, const std::list<std::shared_ptr<hypro::LayerBase<Number>>>& allLayers, bool isFinalResult )
		: mNode( node )
		, mAllLayers( allLayers )
		, mIsFinalResult( isFinalResult ) {}

	std::vector<SearchJob<Number>> compute( NN_REACH_METHOD method ) {
		unsigned short int mLayerNum = mNode->layerNumber();
		unsigned short int mIndex = mNode->neuronNumber();
		typename std::list<std::shared_ptr<hypro::LayerBase<Number>>>::iterator it = mAllLayers.begin();
		std::advance(it, mLayerNum);
		std::shared_ptr<hypro::LayerBase<Number>> mLayer = (*it);
		Starset<Number> mSet = mNode->representation();

		std::vector<Starset<Number>> newSets = mLayer->forwardPass( mSet, mIndex, method );
		int N = newSets.size();

		// the new jobs produced by calculating the current job
		std::vector<SearchJob<Number>> newJobs;
		mNode->setIsComputed( true );

		// check if it was the last neuron of the last layer, so this job produces (part of) the final result
		if ( ( mLayer->layerIndex() == mAllLayers.size() - 1 ) && ( ( mLayer->layerType() == NN_LAYER_TYPE::AFFINE ) ||
																	( mLayer->layerType() != NN_LAYER_TYPE::AFFINE ) && ( mIndex == mLayer->layerSize() - 1 ) ) ) {
			// for the last neuron of the last layer all of the computed result sets is a final result
			for ( auto newSet : newSets ) {
				ReachabilityNode<Number>* leafNode = new ReachabilityNode<Number>( newSet, method, mLayerNum + 1, 0 );
				leafNode->setParent( mNode );
				leafNode->setIsLeaf( true );
				newJobs.push_back( SearchJob( leafNode, mAllLayers, true ) );
			}
			return newJobs;
		}

		// find the location of the next neuron
		unsigned short int newLayerNum = 0;
		unsigned short int newIndex = 0;
		ReachabilityNode<Number>* nextNode;

		switch ( mLayer->layerType() ) {
			case NN_LAYER_TYPE::AFFINE:
				newLayerNum = mLayerNum + 1;
				newIndex = 0;
				// create the new jobs
				for ( int i = 0; i < N; ++i ) {
					// this for always should iterate only once
					// TODO: set the pointers to the parent and backward
					nextNode = new ReachabilityNode<Number>( newSets[i], method, newLayerNum, newIndex );
					newJobs.push_back( SearchJob( nextNode, mAllLayers ) );
				}
				break;
			case NN_LAYER_TYPE::RELU:
			case NN_LAYER_TYPE::HARD_TANH:
				if ( mIndex < mLayer->layerSize() - 1 ) {
					// get the next neuron in the current layer
					newLayerNum = mLayerNum;
					newIndex = mIndex + 1;

				} else {
					// get the first neuron of the next layer
					newLayerNum = mLayerNum + 1;
					newIndex = 0;
				}
				// create the new jobs
				for ( int i = 0; i < N; ++i ) {
					nextNode = new ReachabilityNode<Number>( newSets[i], method, newLayerNum, newIndex );
					nextNode->setParent( mNode );
					if ( !mNode->hasPosChild() ) {
						mNode->setPosChild(nextNode);
					}
					if ( !mNode->hasNegChild() ) {
						mNode->setNegChild(nextNode);
					}
					newJobs.push_back( SearchJob( nextNode, mAllLayers ) );
				}

				if ( mLayer->layerType() == NN_LAYER_TYPE::HARD_TANH )
					TRACE( "hypro.neuralnets.reachability_tree.SearchJob", "HARD_TANH layer type not implemented yet." );
				break;
			default:
				TRACE( "hypro.neuralnets.reachability_tree.SearchJob", "Unknown layer type " << layer->layerType() );
		}
		return newJobs;
	}

	bool isFinalResult() const {
		return mIsFinalResult;
	}

	ReachabilityNode<Number>* getNode() const {
		return mNode;
	}
};

}  // namespace reachability
}  // namespace hypro