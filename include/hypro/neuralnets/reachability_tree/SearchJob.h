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

namespace hypro {
namespace reachability {

template <typename Number>
class SearchJob {
  private:
	Starset<Number> mSet;  // TODO: consider using pointer to the set instead of copying
	std::shared_ptr<LayerBase<Number>> mLayer;
	std::list<std::shared_ptr<hypro::LayerBase<Number>>> mAllLayers;
	unsigned short int mIndex;
	bool mIsFinalResult = false;
	std::vector<Starset<Number>> mFinalResult;

  public:
	SearchJob( const Starset<Number>& set, std::shared_ptr<LayerBase<Number>> layer, const std::list<std::shared_ptr<hypro::LayerBase<Number>>>& allLayers, unsigned short int index )
		: mSet( set )
		, mLayer( layer )
		, mAllLayers( allLayers )
		, mIndex( index ) {}

	SearchJob( const Starset<Number>& set, std::shared_ptr<LayerBase<Number>> layer, const std::list<std::shared_ptr<hypro::LayerBase<Number>>>& allLayers, unsigned short int index, bool isFinalResult, const std::vector<Starset<Number>>& finalResult )
		: mSet( set )
		, mLayer( layer )
		, mAllLayers( allLayers )
		, mIndex( index )
		, mIsFinalResult( isFinalResult )
		, mFinalResult( finalResult ) {}

	std::vector<SearchJob<Number>> compute( NN_REACH_METHOD method ) {
		std::vector<SearchJob<Number>> newJobs;
		std::vector<Starset<Number>> newSets = mLayer->forwardPass( mSet, mIndex, method );
		int N = newSets.size();

		// check if it was the last neuron of the last layer, so this job produces (part of) the final result
		if ( ( mLayer->layerIndex() == mAllLayers.size() - 1 ) && ( ( mLayer->layerType() == NN_LAYER_TYPE::AFFINE ) ||
																	( mLayer->layerType() != NN_LAYER_TYPE::AFFINE ) && ( mIndex == mLayer->layerSize() - 1 ) ) ) {
			newJobs.push_back( SearchJob( mSet, mLayer, mAllLayers, mIndex, true, newSets ) );
			return newJobs;
		}

		// set the new layer to the current layer
		typename std::list<std::shared_ptr<hypro::LayerBase<Number>>>::iterator it = mAllLayers.begin();
		std::advance( it, mLayer->layerIndex() + 1 );
		std::shared_ptr<LayerBase<Number>> newLayer = ( *it );
		unsigned short int newIndex = 0;

		switch ( mLayer->layerType() ) {
			case NN_LAYER_TYPE::AFFINE:
				// create the new jobs
				for ( int i = 0; i < N; ++i ) {
					newJobs.push_back( SearchJob( newSets[i], newLayer, mAllLayers, newIndex ) );
				}
				break;
			case NN_LAYER_TYPE::RELU:
			case NN_LAYER_TYPE::HARD_TANH:
				if ( mIndex < mLayer->layerSize() - 1 ) {
					// get the current layer if it is not the last neuron in the layer
					std::advance( it, -1 );
					newLayer = ( *it );
					newIndex = mIndex + 1;

				} else {
					// if it is the last neuron in the layer
					newIndex = 0;
				}
				// create the new jobs
				for ( int i = 0; i < N; ++i ) {
					newJobs.push_back( SearchJob( newSets[i], newLayer, mAllLayers, newIndex ) );
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

	std::vector<Starset<Number>> finalResult() const {
		if ( mIsFinalResult )
			return mFinalResult;
		return std::vector<Starset<Number>>();
	}
};

}  // namespace reachability
}  // namespace hypro