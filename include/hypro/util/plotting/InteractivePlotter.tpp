/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include "InteractivePlotter.h"

namespace hypro::plotting {

template <typename Representation>
void InteractivePlotter<Representation>::run() {
	auto rtPlt = ReachTreePlotter<Representation>( mRoots );
	while ( true ) {
        int option;
        // print options
        printCurrentOptions();
        // read user input
        std::cin >> option;
        if (option == -1) {
            break;
        }
        // process user input
        if (mCurrent == nullptr) {
            if (option >= mRoots.size() || option < 0) {
                std::cout << "Please pick a valid option." << std::endl;
            } else {
                mCurrent = &mRoots[option];
                addSegments(mCurrent);
                plotCurrent();
                rtPlt.plot({mCurrent});
            }
        } else {
            if (option == mCurrent->getChildren().size()) {
				removeSegments( mCurrent );
				mCurrent = mCurrent->getParent();
				plotCurrent();
				rtPlt.plot( { mCurrent } );
			} else if ( option > mCurrent->getChildren().size() || option < 0 ) {
				std::cout << "Please pick a valid option." << std::endl;
			} else {
				mCurrent = mCurrent->getChildren()[option];
				addSegments( mCurrent );
				plotCurrent();
				rtPlt.plot( { mCurrent } );
			}
		}
	}
}

template <typename Representation>
void InteractivePlotter<Representation>::addSegments( ReachTreeNode<Representation>* node ) {
	Plotter<typename Representation::NumberType>& plt = Plotter<typename Representation::NumberType>::getInstance();

	// set/obtain color
	if ( mLocationColorMapping.find( node->getLocation() ) == std::end( mLocationColorMapping ) ) {
		mLocationColorMapping[node->getLocation()] = plotting::colors[mLocationColorMapping.size() % 10];
	}
	std::size_t color = mLocationColorMapping[node->getLocation()];

	mNodeSegmentMapping[node] = std::vector<std::size_t>{};
	for ( const auto& segment : node->getFlowpipe() ) {
		mNodeSegmentMapping[node].push_back( plt.addObject( segment.projectOn( mSettings.plotDimensions.front() ).vertices(), color ) );
	}
}

template <typename Representation>
void InteractivePlotter<Representation>::removeSegments( ReachTreeNode<Representation>* node ) {
	Plotter<typename Representation::NumberType>& plt = Plotter<typename Representation::NumberType>::getInstance();

	if ( mNodeSegmentMapping.find( node ) != mNodeSegmentMapping.end() ) {
		for ( const auto& id : mNodeSegmentMapping[node] ) {
			plt.removeObject( id );
		}
		mNodeSegmentMapping.erase( node );
	}
}

template <typename Representation>
void InteractivePlotter<Representation>::plotCurrent() {
	Plotter<typename Representation::NumberType>& plt = Plotter<typename Representation::NumberType>::getInstance();
	plt.setFilename( "out" );
	plt.rSettings().overwriteFiles = true;
	plt.plot2d( PLOTTYPE::pdf );

	std::system( "gnuplot out_pdf.plt" );
}

template <typename Representation>
void InteractivePlotter<Representation>::printCurrentOptions() const {
	if ( mCurrent == nullptr ) {
		std::cout << "Select root node (-1 to exit):\n";
		for ( std::size_t i = 0; i < mRoots.size(); ++i ) {
			std::cout << i << ": " << mRoots[i].getLocation()->getName() << "\n";
		}
		std::cout << std::endl;
	} else {
        std::cout << "Current initial set:\n";
        std::cout << mCurrent->getInitialSet() << "\n";
        std::cout << "Select next transition (-1 to exit):\n";
        for (std::size_t i = 0; i < mCurrent->getChildren().size(); ++i) {
            std::cout << i << ": " << mCurrent->getLocation()->getName() << " -> " << mCurrent->getChildren()[i]->getLocation()->getName() << "\n";
            std::cout << "guard:\n"
                      << mCurrent->getChildren()[i]->getTransition()->getGuard() << "\n";
            std::cout << "reset:\n"
                      << mCurrent->getChildren()[i]->getTransition()->getReset() << "\n";
            std::cout << "resulting in new initial set:\n"
                      << mCurrent->getChildren()[i]->getInitialSet() << "\n";
        }
		std::cout << mCurrent->getChildren().size() << ": Ascend" << std::endl;
	}
}

}  // namespace hypro::plotting
