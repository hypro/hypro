/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 22.09.21.
 */

#ifndef HYPRO_REACHTREEPLOTTER_H
#define HYPRO_REACHTREEPLOTTER_H

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

#include <hypro/flags.h>

namespace hypro::plotting {

#ifdef HYPRO_HAS_GRAPHVIZ

template <typename Representation>
class ReachTreePlotter {
  public:
	ReachTreePlotter( const std::vector<ReachTreeNode<Representation>>& roots, PlottingSettings settings )
		: mRoots( roots )
		, mSettings( std::move( settings ) ) {}

	void plot( const std::vector<ReachTreeNode<Representation>*>& highlights = {} );

  private:
	const std::vector<ReachTreeNode<Representation>>& mRoots;
	std::map<const ReachTreeNode<Representation>*, Agnode_t*> mNodePointers;
	PlottingSettings mSettings;
};

}  // namespace hypro::plotting

#include "ReachTreePlotter.tpp"

#endif	// HYPRO_HAS_GRAPHVIZ

#endif	// HYPRO_REACHTREEPLOTTER_H
