/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 22.09.21.
 */

#ifndef HYPRO_REACHTREEPLOTTER_H
#define HYPRO_REACHTREEPLOTTER_H

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
#include "../../datastructures/reachability/ReachTreev2.h"
#include "../../datastructures/reachability/ReachTreev2Util.h"
#include "../../datastructures/reachability/Settings.h"
#include "GraphvizSettings.h"
#include "PlotterUtil.h"

namespace hypro::plotting {

/**
 * @brief Plotter for reachtrees.
 * @details ALlows to plot a complete reachtree or a path to a node. Nodes in the plot can be highlighted.
 * @tparam Representation State set representation type
 */
template <typename Node>
class ReachTreePlotter {
  public:
	ReachTreePlotter( const std::vector<Node>& roots )
		: mRoots( roots )
		, mSettings( { "rt_out", false } ) {}

	/**
	 * @brief Plots the complete reachtree
	 * @param highlights Nodes that should be highlighted in the plot
	 */
	void plot( const std::vector<Node*>& highlights = {} );

	/**
	 * @brief Plots the path to the passed node of a reachtree.
	 * @param node The node
	 * @param highlights Nodes that should be highlighted in the plot
	 */
	void plotPath( const Node* node, const std::vector<Node*>& highlights );

	/**
	 * Returns a reference to the internal plotting settings.
	 * @details Should be used for easy access to the settings.
	 * @return A reference to the internal graphvizSettings
	 */
	graphvizSettings& rSettings() { return mSettings; }

  private:
	/**
	 * @brief Helper function to create a unique name for a node
	 * @details Graphviz requires unique identifiers (names) for nodes within one graph. For every call to plot or plotPath, these are freshly generated.
	 * @param node The node
	 * @param count An internal counter, should be increased for every call, used to ensure uniqueness.
	 * @return
	 */
	std::string createName( const Node* node, std::size_t count ) {
		std::string name = "{ { n_" + std::to_string( count ) + "} | ";
		name += " { location | ";
		if ( node->getParent() == nullptr ) {
			if ( node->getChildren().empty() ) {
				name += "root";
			} else {
				assert( !node->getChildren().empty() );
				assert( node->getChildren().front().getTransition() != nullptr );
				assert( node->getChildren().front().getTransition()->getSource() != nullptr );
				std::string tmp = node->getLocation()->getName();
				name += node->getChildren().front().getTransition()->getSource()->getName();
			}
		} else {
			name += node->getLocation()->getName();
		}
		name += "}";
		name += " | { fp |" + to_string( node->hasFixedPoint() ) + " }";
		name += " | { tl |";
		name += node->hasTimelock() ? "y" : "n";
		name += " }";
		name += "}";
		return name;
	}

	const std::vector<Node>& mRoots;				 ///< Stores the roots of a reachtree, in case the full tree needs to be plotted.
	std::map<const Node*, Agnode_t*> mNodePointers;	 ///< Internal cache for nodes
	graphvizSettings mSettings;						 ///< Settings for plotting
};

}  // namespace hypro::plotting

#include "ReachTreePlotter.tpp"

#endif	// HYPRO_HAS_GRAPHVIZ

#endif	// HYPRO_REACHTREEPLOTTER_H
