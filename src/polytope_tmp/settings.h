/** 
 * @file   settings.h
 * Created on Mar 23, 2011
 * Last modified May 16, 2011
 * 
 * @author Sebastian Junges
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "config.h"

// Log4cplus
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <iomanip>
#include <assert.h>

using namespace log4cplus;

namespace reachLin {
class Settings {
public:
    static bool InitializeLib(int seed = 0) {
        BasicConfigurator config;
        config.configure();
        (seed==0) ? srand(time(0)) : srand(seed);
        
        Logger log = Logger::getInstance("reachLin");
        log.setLogLevel(DEBUG_LOG_LEVEL);
        LOG4CPLUS_INFO(log, "Initialized reachLin");
        LOG4CPLUS_INFO(log, "Version: " << reachLin_VERSION_MAJOR << "." << reachLin_VERSION_MINOR);
        return true;
    }

    static std::vector<unsigned> getStaticDimensionOrder(unsigned dimension) {
            std::vector<unsigned> dimOrder;
            dimOrder.reserve(dimension);
            for (unsigned d=0; d<dimension; d++) {
                    dimOrder.push_back(d);
            }
            return dimOrder;
    }

    static void setLogLevel(int loglvl) {
        Logger log = Logger::getInstance("reachLin");
        std::string logLvl;
        
        switch (loglvl) {
            case -1:
                log.setLogLevel(WARN_LOG_LEVEL);
                logLvl = "WARN";
                break;
            case 0:
                log.setLogLevel(INFO_LOG_LEVEL);
                logLvl = "INFO";
                break;
            case 1:
                log.setLogLevel(DEBUG_LOG_LEVEL);
                logLvl = "DEBUG";
                break;
            case 2:
                log.setLogLevel(TRACE_LOG_LEVEL);
                logLvl = "TRACE";
                break;
        }
        LOG4CPLUS_WARN(log, "Changed loglevel to " + logLvl);
    }


};
}
#endif /* SETTINGS_H_ */
