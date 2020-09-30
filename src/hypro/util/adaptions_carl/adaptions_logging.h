#pragma once
#include "../../flags.h"

// clang-format off
#ifdef CARL_LOGGING_VX
#include <carl-logging/logging.h>
#include <carl-logging/Logger.h>
#include <carl-logging/carl-logging.h>
#else
#include <carl/core/carlLogging.h>
#include <carl/core/carlLoggingHelper.h>
#endif
// clang-format on