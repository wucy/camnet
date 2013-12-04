#include "logger.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <iostream>
#include <string>

#include <pthread.h>


namespace camnet {

Logger::Logger() {
    trace_level = DEBUG;
    pthread_mutex_init(&mutex, NULL);
}

Logger::~Logger() {
    pthread_mutex_destroy(&mutex);
}


void Logger::Debug(const char * format, ...) {
    va_list print_args;
    va_start(print_args, format);
    _get_instance()._debug(format, print_args);
    va_end(print_args);
}

void Logger::Info(const char * format, ...) {
    va_list print_args;
    va_start(print_args, format);
    _get_instance()._info(format, print_args);
    va_end(print_args);
}

void Logger::Warn(const char * format, ...) {
    va_list print_args;
    va_start(print_args, format);
    _get_instance()._warn(format, print_args);
    va_end(print_args);

}

void Logger::Error(const char * format, ...) {
    va_list print_args;
    va_start(print_args, format);
    _get_instance()._error(format, print_args);
    va_end(print_args);
}

void Logger::set_trace_level(TraceLevel level) {
    _get_instance().trace_level = level;
}

Logger::TraceLevel Logger::get_trace_level() const {
    return _get_instance().trace_level;
}


void Logger::_debug(const char * format, va_list print_args) const {
    if (trace_level > DEBUG) return;

    pthread_mutex_lock(&mutex);

    std::fprintf(stdout, "<<<DEBUG>>> ");
    vfprintf(stdout, format, print_args);
    std::fflush(stdout);

    pthread_mutex_unlock(&mutex);
}

void Logger::_info(const char * format, va_list print_args) const {
    if (trace_level > INFO) return;
    
    pthread_mutex_lock(&mutex);

    vfprintf(stdout, format, print_args);
    std::fflush(stdout);
    
    pthread_mutex_unlock(&mutex);

}

void Logger::_warn(const char * format, va_list print_args) const {
    if (trace_level > WARN) return;
    
    pthread_mutex_lock(&mutex);

    std::fprintf(stderr, "<<<WARN>>> ");
    vfprintf(stderr, format, print_args);

    pthread_mutex_unlock(&mutex);


}

void Logger::_error(const char * format, va_list print_args) const {
    pthread_mutex_lock(&mutex);

    std::fprintf(stderr, "<<<ERROR>>> ");
    vfprintf(stderr, format,print_args);

    pthread_mutex_unlock(&mutex);

    exit(1);
}

Logger & Logger::_get_instance() {
    static Logger singleton;
    return singleton;
}

}
