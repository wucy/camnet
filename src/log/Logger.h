#ifndef CAMNET_LOG_LOGGER_H
#define CAMNET_LOG_LOGGER_H

#include <string>
#include <set>

#include <pthread.h>

namespace camnet {
namespace log {

//a simple i/o thread-safe logger
class Logger {

public:
    //trace level from low to high
    enum TraceLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 };

    //Debug and Info are assigned to stdout, Warn and Error to stderr
    static void Debug(const char * module, const char * format, ...);
    static void Info(const char * module, const char * format, ...);
    static void Warn(const char * module, const char * format, ...);
    static void Error(const char * module, const char * format, ...);



    //set and get the lowest trace level, not thread-safe
    static void set_trace_level(TraceLevel level); 
    TraceLevel get_trace_level();
    //add and remove ignored module names, not thread-safe
    static void add_ignored_module(const std::string & module);
    static void remove_ignored_module(const std::string & module);

private:
    //lowest trace level
    TraceLevel trace_level;
    //module names in this set are ignored in tracing, invalid for the ERROR level
    std::set<std::string> ignored_modules;



    mutable pthread_mutex_t mutex;

    static Logger & get_instance();
};
}
}


#endif
