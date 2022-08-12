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

#include "HybridAutomatonPlotter.h"

namespace hypro::plotting {

template <typename Number>
void HybridAutomatonPlotter<Number>::plot( const std::vector<Location<Number>*>& highlights ) {
	// graph and context variables
	Agraph_t* graph;
	GVC_t* gvc;

	// setup
	gvc = gvContext();
	graph = agopen( std::string( "hybridAutomaton" ).data(), Agstrictdirected, 0 );
	gvLayout( gvc, graph, "dot" );

	// set default node properties
	agattr( graph, AGNODE, std::string( "fillcolor" ).data(), std::string( "lightgrey" ).data() );
	agattr( graph, AGNODE, std::string( "style" ).data(), std::string( "filled" ).data() );
	agattr( graph, AGNODE, std::string( "shape" ).data(), std::string( "rect" ).data() );

	// insert locations
	for ( Location<Number>* locPtr : mAutomaton.getLocations() ) {
		std::string name = locPtr->printContent();

		auto nptr = agnode( graph, name.data(), 1 );
		mLocationPointers[locPtr] = nptr;
		// color node, if it needs highlighting
		if ( std::find( std::begin( highlights ), std::end( highlights ), locPtr ) != std::end( highlights ) ) {
			agsafeset( nptr, std::string( "fillcolor" ).data(), std::string( "yellow" ).data(), std::string().data() );
		}
	}
	// insert transitions
	for ( Location<Number>* locPtr : mAutomaton.getLocations() ) {
		for ( const auto& traSharedPtr : locPtr->getTransitions() ) {
			assert( mLocationPointers.find( traSharedPtr.get()->getSource() ) != mLocationPointers.end() );
			assert( mLocationPointers.find( traSharedPtr.get()->getTarget() ) != mLocationPointers.end() );
			// guard-string
			std::string guard, reset;
			{
				const Condition<Number>& g = traSharedPtr.get()->getGuard();
				if ( g.isTrue() ) {
					guard = "true";
				} else {
					std::stringstream ss;
					ss << g;
					guard = ss.str();
				}
			}
			{
				std::stringstream ss;
				ss << traSharedPtr.get()->getReset();
				reset = ss.str();
			}
			auto edge = agedge( graph, mLocationPointers[traSharedPtr.get()->getSource()], mLocationPointers[traSharedPtr.get()->getTarget()], std::string().data(), 1 );
			std::string labels;
			{
				std::stringstream ss;
				for ( const auto& l : traSharedPtr.get()->getLabels() ) {
					ss << l << ", ";
				}
				labels = ss.str();
			}
			agsafeset( edge, std::string( "label" ).data(), std::string( labels + "\n" + guard + "\n" + reset ).data(), std::string().data() );
		}
	}

	// determine filename
	std::size_t cnt = 0;
	std::string filename = mSettings.filename;
	if ( !mSettings.overwriteFiles ) {
		while ( file_exists( filename + ".png" ) || file_exists( filename + ".dot" ) ) {
			std::stringstream ss;
			ss << mSettings.filename << "-" << cnt;
			filename = ss.str();
			++cnt;
		}
	}

	// drawing
	gvLayoutJobs( gvc, graph );
	gvRenderFilename( gvc, graph, "png", ( filename + ".png" ).c_str() );
	gvRenderFilename( gvc, graph, "dot", ( filename + ".dot" ).c_str() );
	gvFreeLayout( gvc, graph );

	// cleanup
	agclose( graph );
	gvFreeContext( gvc );
}

}  // namespace hypro::plotting