/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <hypro/flags.h>
#include <hypro/types.h>
#include <iostream>
#include <sstream>
#include <thread>

#define COUT(expr) \
    { std::cout << expr; }
#define CERR(expr) \
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

    int initializeLogging(int &i);

    static int initvar = initializeLogging(initvar);

}  // namespace hypro

#define TRACE(channel, expr) \
    { __CARL_LOG( carl::logging::LogLevel::LVL_TRACE, channel, expr ); }
#define DEBUG(channel, expr) \
    { __CARL_LOG( carl::logging::LogLevel::LVL_DEBUG, channel, expr ); }
#define INFO(channel, expr) \
    { __CARL_LOG( carl::logging::LogLevel::LVL_INFO, channel, expr ); }
#define WARN(channel, expr) \
    { __CARL_LOG( carl::logging::LogLevel::LVL_WARN, channel, expr ); }
#define FATAL(channel, expr) \
    { __CARL_LOG( carl::logging::LogLevel::LVL_FATAL, channel, expr ); }

#endif
