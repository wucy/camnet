#include "config.h"

#include <string>
#include <fstream>
#include <cctype>

#include "../util/util.h"
#include "../log/logger.h"


#define LINE_MAXLENGTH 65535




namespace camnet {

void Config::Load(const std::string & file_name) {
    
    std::ifstream ifs(file_name.c_str());
    
    if (!ifs.good()) {
        Logger::Error("%s\n", "Cannot find the config file");
    }
    
    char line[LINE_MAXLENGTH];
    while (ifs.getline(line, LINE_MAXLENGTH + 1)) {
        std::string sline = trim(line);
        if (sline == "") continue;
        if (sline[0] == '#') continue;

        size_t split_pos = sline.find('=');
        
        if (split_pos == std::string::npos)
            Logger::Error("%s\n", "Illegal defination in the config file");
        
        std::string key = trim(sline.substr(0, split_pos));
        std::string value = trim(sline.substr(split_pos + 1));
        params[key] = value;
    }

    ifs.close();
}

std::string Config::Get(const std::string & key, const std::string def_val) {
    if (params.find(key) == params.end()) return def_val;
    return params[key];
}

void Config::Set(const std::string & key, const std::string & value) {
    params[key] = value;
}

}

