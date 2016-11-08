#pragma once

#ifdef LOGGING_HYPRO
#undef DEBUG
#undef TRACE
#undef INFO
#undef WARN
#undef FATAL
#define DEBUG(expr) LOG4CPLUS_DEBUG(hypro::logger, "[" << __func__ << " " << __FILE__ << ":" << __LINE__ << "] " << expr)
#define TRACE(expr) LOG4CPLUS_TRACE(hypro::logger, "[" << __func__ << " " << __FILE__ << ":" << __LINE__ << "] " << expr)
#define INFO(expr) LOG4CPLUS_INFO(hypro::logger, expr)
#define WARN(expr) LOG4CPLUS_DEBUG(hypro::logger, expr)
#define FATAL(expr) LOG4CPLUS_FATAL(hypro::logger, expr)
#endif
