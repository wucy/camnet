#ifndef CAMNET_CONFIG_CONFIG_H
#define CAMNET_CONFIG_CONFIG_H

#include <map>
#include <string>

using std::map;
using std::string;

namespace camnet
{
class Config
{
public:
    Config(const int argc, const char * argv []); //just put the origin parameters of main function here
    virtual ~Config() {}

    string get(const string & key) const;
    void set(const string & key, const string & value);

private:
    Parse(const string & file_name);
    
    map<string, string> params;
};

}

#endif
