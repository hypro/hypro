/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/util/logging/Logger.h"

#ifdef HYPRO_LOGGING
namespace hypro {

int initializeLogging( int& i ) {
	carl::logging::logger().configure( "logfile_hypro", "hypro.log" );
	carl::logging::logger().filter("logfile_hypro" )( "hypro", carl::logging::LogLevel::LVL_TRACE )( "hypro.casestudies", carl::logging::LogLevel::LVL_INFO )( "hypro.datastructures",
																																							   carl::logging::LogLevel::LVL_TRACE );

	carl::logging::logger().configure( "pathfile_hypro", "unfinished_paths.log" );
	carl::logging::logger().filter( "pathfile_hypro" )( "benchmark.paths", carl::logging::LogLevel::LVL_TRACE );

	carl::logging::logger().configure( "stdout", std::cout );
	carl::logging::logger().filter( "stdout" )( "hypro", carl::logging::LogLevel::LVL_OFF )
		  //( "hypro.datastructures.hybridAutomaton", carl::logging::LogLevel::LVL_TRACE )
		  //( "hypro.datastructures", carl::logging::LogLevel::LVL_TRACE )
		  //("hypro.representations", carl::logging::LogLevel::LVL_TRACE)
		  //("hypro.datastructures.timing", carl::logging::LogLevel::LVL_TRACE)
		  ;

	carl::logging::logger().resetFormatter();

	// avoid warning of unused variable by casting it to void (thus it is used at least once).
	(void)i;

	return 0;
}

}  // namespace hypro

#endif
