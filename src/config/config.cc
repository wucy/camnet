#include "config.h"

#include <string>
#include <fstream>
#include <cctype>

#include "../util/util.h"



#define LINE_MAXLENGTH 65535




namespace camnet {
namespace config {


void Config::idol(const std::string & file_name) {}

void Config::Load(const std::string & file_name) {
    
    std::ifstream ifs(file_name.c_str());
    

    if (!ifs.good()) {
        //TODO logger
        throw "Cannot find the config file: " + file_name + "\n";
    }
    
    char line[LINE_MAXLENGTH];
    while (ifs.getline(line, LINE_MAXLENGTH + 1)) {
        std::string sline = util::trim(line);
        if (sline == "") continue;
        if (sline[0] == '#') continue;

        unsigned split_pos = sline.find('=');
        
        if (split_pos == std::string::npos) {
            //TODO logger
            throw "Illegal defination in the config file: " + sline + "\n";
        }

        
        std::string key = util::trim(sline.substr(0, split_pos));
        std::string value = util::trim(sline.substr(split_pos + 1));
        params[key] = value; 
    }

    ifs.close();
}

std::string Config::Get(const std::string & key) const {
    if (params.find(key) == params.end()) {
        //TODO logger
        throw "Invalid key in the config parameters: " + key + "\n";
    }
    return "TODO";
}

void Config::Set(const std::string & key, const std::string & value) {
    params[key] = value;
}

}
}

