/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 04.07.22.
 */

#ifndef HYPRO_HYBRIDAUTOMATONPLOTTER_H
#define HYPRO_HYBRIDAUTOMATONPLOTTER_H

#include <hypro/flags.h>

#ifdef HYPRO_HAS_GRAPHVIZ

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "GraphvizSettings.h"
#include "PlotterUtil.h"

namespace hypro::plotting {

template <typename Number>
class HybridAutomatonPlotter {
  public:
	HybridAutomatonPlotter( const HybridAutomaton<Number>& automaton )
		: mAutomaton( automaton )
		, mSettings( { "ha_out", false } ) {}

	/**
	 * @brief Plots the complete hybrid automaton
	 * @param highlights Locations that should be highlighted in the plot
	 */
	void plot( const std::vector<Location<Number>*>& highlights = {} );

	/**
	 * Returns a reference to the internal plotting settings.
	 * @details Should be used for easy access to the settings.
	 * @return A reference to the internal graphvizSettings
	 */
	graphvizSettings& rSettings() { return mSettings; }

  private:
	const HybridAutomaton<Number>& mAutomaton;						 ///< The hybrid automaton to be plotted
	std::map<const Location<Number>*, Agnode_t*> mLocationPointers;	 ///< Internal cache for locations
	graphvizSettings mSettings;										 ///< Settings for plotting
};

template <typename Number>
void plot( const HybridAutomaton<Number>& automaton, std::string filename = "ha_out" ) {
	auto plt = HybridAutomatonPlotter<Number>( automaton );
	plt.rSettings().filename = filename;
	plt.plot();
}

}  // namespace hypro::plotting

#include "HybridAutomatonPlotter.tpp"

#endif	// HYPRO_HAS_GRAPHVIZ

#endif	// HYPRO_HYBRIDAUTOMATONPLOTTER_H
