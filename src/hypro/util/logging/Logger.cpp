//
// Created by stefan on 01.07.16.
//

#include "Logger.h"

#ifdef HYPRO_LOGGING

namespace hypro {

	LogInitializer::LogInitializer() {
		config.configure();
	}

	log4cplus::Logger& LogInitializer::get() {
		if (instance == nullptr) {
			instance = new LogInitializer();
		}
		return instance->getLogger();
	}

	log4cplus::Logger& LogInitializer::getLogger() {
		#ifdef HYPRO_LOG_TRACE
			this->logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
		#endif
		return this->logger;
	}

	LogInitializer* LogInitializer::instance = nullptr;
	::log4cplus::Initializer LogInitializer::initializer;
	::log4cplus::BasicConfigurator LogInitializer::config;

	log4cplus::Logger logger = LogInitializer::get();

} // namespace hypro
#endif
