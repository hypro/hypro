/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 23.03.22.
 */

#include "include/hypro/datastructures/HybridAutomaton/output/Flowstar.h"

namespace hypro {

std::string toFlowstarFormat( const ReachabilitySettings& settings,
							  const std::map<Eigen::Index, std::string>&,
							  const std::string& prefix ) {
	std::stringstream res;

	res << prefix << "setting";
	res << prefix << "{";
	res << prefix << "\tfixed steps " << settings.timeStep;
	res << prefix << "\ttime " << settings.timeBound;
	/*
	if ( !settings.plotDimensions.empty() ) {
		for ( const auto& dims : settings.plotDimensions ) {
			assert( dims.size() == 2 );
			res << prefix << "\tgnuplot octagon " << varNameMap.at( dims[0] ) << "," << varNameMap.at( dims[1] );
		}
	}
	*/
	res << prefix << "\toutput " << settings.fileName;
	res << prefix << "\tmax jumps " << settings.jumpDepth;
	res << prefix << "}";

	return res.str();
}

}  // namespace hypro