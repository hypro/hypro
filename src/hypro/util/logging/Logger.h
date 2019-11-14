#pragma once

#include "../../flags.h"

#include <carl/io/streamingOperators.h>
#include <iostream>
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

#include <carl/core/carlLogging.h>

namespace hypro {

int initializeLogging( int& i );

static int initvar = initializeLogging( initvar );

}  // namespace hypro

#define __HYPRO_LOG( lvl, channel, expr )                                                                                        \
	{                                                                                                                            \
		std::stringstream __ss;                                                                                                  \
		__ss << std::this_thread::get_id() << " " << expr;                                                                       \
		carl::logging::Logger::getInstance().log( lvl, channel, __ss, carl::logging::RecordInfo{__FILE__, __func__, __LINE__} ); \
	}

#define TRACE( channel, expr ) \
	{ __HYPRO_LOG( carl::logging::LogLevel::LVL_TRACE, channel, expr ); }
#define DEBUG( channel, expr ) \
	{ __HYPRO_LOG( carl::logging::LogLevel::LVL_DEBUG, channel, expr ); }
#define INFO( channel, expr ) \
	{ __HYPRO_LOG( carl::logging::LogLevel::LVL_INFO, channel, expr ); }
#define WARN( channel, expr ) \
	{ __HYPRO_LOG( carl::logging::LogLevel::LVL_WARN, channel, expr ); }
#define FATAL( channel, expr ) \
	{ __HYPRO_LOG( carl::logging::LogLevel::LVL_FATAL, channel, expr ); }

#endif
