#include "Logger.h"

#include <cstdio>
#include <cstdlib>
#include <string>

#include <pthread.h>


namespace camnet {
namespace log {


void Logger::Debug(const char * module, const char * format, ...) {
    static const char * debug_line = "\n####################\n";

    if (get_instance().trace_level > DEBUG) return;
    if (module != NULL && get_instance().ignored_modules.find(module) == get_instance().ignored_modules.end()) return;


    pthread_mutex_lock(&get_instance().mutex);

    std::fprintf(stdout, "%s", debug_line);
    if (module == NULL) std::fprintf(stdout, "DEBUG --\n");
    else std::fprintf(stdout, "DEBUG @ %s --\n", module);
    va_list print_args;
    std::fprintf(stdout, format, print_args);
    std::fflush(stdout);
    std::fprintf(stdout, "%s", debug_line);

    pthread_mutex_unlock(&get_instance().mutex);
}
 

}
}
