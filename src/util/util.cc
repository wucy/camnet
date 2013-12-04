#include "util.h"

#include <string>
#include <cctype>

namespace camnet {

extern std::string trim(const std::string & raw_str) {
    size_t sta = 0;
    size_t end = raw_str.length() - 1;
    while (sta <= end) {
        if (isspace(raw_str[sta])) sta ++; else break;
    }
    while (sta <= end) {
        if (isspace(raw_str[end])) end --; else break;
    }
    if (sta <= end) 
        return raw_str.substr(sta, end - sta + 1); 
    else 
        return "";
}

}


