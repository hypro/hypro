#pragma once

#include "../../flags.h"

#include <carl/io/streamingOperators.h>
#include <iostream>
#include <sstream>
#include <thread>

#define COUT( expr ) \
	{ std::cout << expr; }
#define CERR( expr ) \
	{ std::cerr << expr; }

#ifndef HYPRO_LOGGING
// define to be no-ops, note that expr still gets evaluated.
#define DEBUG( channel, expr )
#define TRACE( channel, expr )
#define INFO( channel, expr )
#define WARN( channel, expr )
#define FATAL( channel, expr )

#else

#include "../adaptions_carl/adaptions_logging.h"

namespace hypro {

int initializeLogging( int& i );

static int initvar = initializeLogging( initvar );

}  // namespace hypro

#define TRACE( channel, expr ) \
	{ __CARL_LOG( carl::logging::LogLevel::LVL_TRACE, channel, expr ); }
#define DEBUG( channel, expr ) \
	{ __CARL_LOG( carl::logging::LogLevel::LVL_DEBUG, channel, expr ); }
#define INFO( channel, expr ) \
	{ __CARL_LOG( carl::logging::LogLevel::LVL_INFO, channel, expr ); }
#define WARN( channel, expr ) \
	{ __CARL_LOG( carl::logging::LogLevel::LVL_WARN, channel, expr ); }
#define FATAL( channel, expr ) \
	{ __CARL_LOG( carl::logging::LogLevel::LVL_FATAL, channel, expr ); }

#endif
