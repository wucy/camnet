#ifndef CAMNET_LOG_LOGGER_H
#define CAMNET_LOG_LOGGER_H

#include <string>
#include <cstdarg>
#include <set>

#include <pthread.h>

namespace camnet {

//a simple i/o thread-safe logger
class Logger {

public:
    //trace level from low to high
    enum TraceLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 };

    //Debug and Info are assigned to stdout, Warn and Error to stderr, thread-safe
    static void Debug(const char * format, ...);
    static void Info(const char * format, ...);
    static void Warn(const char * format, ...);
    static void Error(const char * format, ...);



    //set and get the lowest trace level, not thread-safe
    static void set_trace_level(TraceLevel level); 
    TraceLevel get_trace_level() const;

private:

    Logger();
    ~Logger();

    
    void _debug(const char * format, va_list print_args) const;
    void _info(const char * format, va_list print_args) const;
    void _warn(const char * format, va_list print_args) const;
    void _error(const char * format, va_list print_args) const;

    static Logger & _get_instance();

    //lowest trace level
    TraceLevel trace_level;

    mutable pthread_mutex_t mutex;
};


}


#endif
