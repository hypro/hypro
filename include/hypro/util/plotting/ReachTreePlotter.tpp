/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "ReachTreePlotter.h"

namespace hypro::plotting {

template <typename Representation>
void ReachTreePlotter<Representation>::plot( const std::vector<ReachTreeNode<Representation>*>& highlights ) {
	// graph and context variables
	Agraph_t* graph;
	GVC_t* gvc;

	// setup
	gvc = gvContext();
	graph = agopen( "reachTree", Agstrictdirected, 0 );
	gvLayout( gvc, graph, "dot" );

	// set default node properties
	agattr( graph, AGNODE, std::string( "fillcolor" ).data(), std::string( "lightgrey" ).data() );
	agattr( graph, AGNODE, std::string( "style" ).data(), std::string( "filled" ).data() );
	// agattr(graph, AGNODE, std::string("label").data(), std::string("test").data());

	// insert nodes
	std::size_t count{ 0 };
	for ( const ReachTreeNode<Representation>& root : mRoots ) {
		for ( const ReachTreeNode<Representation>& node : preorder( root ) ) {
			std::string name = "n_" + std::to_string( count++ );
			auto nptr = agnode( graph, name.data(), 1 );
			mNodePointers[&node] = nptr;
			// color node, if it needs highlighting
			if ( std::find( std::begin( highlights ), std::end( highlights ), &node ) != std::end( highlights ) ) {
				agsafeset( nptr, std::string( "fillcolor" ).data(), std::string( "yellow" ).data(), std::string().data() );
			}
			if ( node.getParent() != nullptr ) {
				assert( mNodePointers.find( node.getParent() ) != mNodePointers.end() );
				agedge( graph, mNodePointers[node.getParent()], nptr, "", 1 );
			}
		}
	}

	// drawing
	gvLayoutJobs( gvc, graph );
	gvRenderFilename( gvc, graph, "png", "rt_out.png" );
	gvRenderFilename( gvc, graph, "dot", "rt_out.dot" );
	gvFreeLayout( gvc, graph );

	// cleanup
	agclose( graph );
	gvFreeContext( gvc );
}

}  // namespace hypro::plotting
