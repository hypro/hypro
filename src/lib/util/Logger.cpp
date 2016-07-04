//
// Created by stefan on 01.07.16.
//

#include "Logger.h"

#ifdef LOGGING_HYPRO
namespace hypro{
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
		return this->logger;
	}

	LogInitializer* LogInitializer::instance = nullptr;
	::log4cplus::Initializer LogInitializer::initializer;
	::log4cplus::BasicConfigurator LogInitializer::config;

	log4cplus::Logger logger = LogInitializer::get();

} // namespace hypro
#endif
