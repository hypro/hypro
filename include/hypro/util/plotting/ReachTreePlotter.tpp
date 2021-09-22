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
	graph = agopen( "out.gv", Agstrictdirected, 0 );
	gvLayout( gvc, graph, "dot" );

	// set default node properties
	// agattr(graph, AGNODE, std::string("shape").data(), std::string("point").data());
	// agattr(graph, AGNODE, std::string("label").data(), std::string("test").data());

	// insert nodes
	std::size_t count{ 0 };
	for ( auto& root : mRoots ) {
		for ( auto& node : preorder( root ) ) {
			auto name = "n_" + std::to_string( count++ );
			char* cstr = new char[name.length() + 1];
			strcpy( cstr, name.c_str() );
			mNodePointers[&node] = agnode( graph, cstr, 0 );
			// agsafeset(mNodePointers[&node], std::string("label").data(), node.getLocation()->getName().data(), std::string().data());
			std::cout << "created node " << cstr << " (" << mNodePointers.size() << ")" << std::endl;
			if ( node.getParent() != nullptr ) {
				agedge( graph, mNodePointers[node.getParent()], mNodePointers[&node], "", 0 );
				std::cout << "created edge" << std::endl;
			}
		}
	}

	// drawing
	gvRenderFilename( gvc, graph, "png", "rt_out.png" );
	gvRenderFilename( gvc, graph, "dot", "rt_out.dot" );
	gvFreeLayout( gvc, graph );

	// cleanup
	agclose( graph );
	gvFreeContext( gvc );
}

}  // namespace hypro::plotting
