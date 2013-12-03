#ifndef CAMNET_CONFIG_CONFIG_H
#define CAMNET_CONFIG_CONFIG_H

#include <map>
#include <string>


namespace camnet {
namespace config {

class Config {
public:
    Config() {}
    virtual ~Config() {}

    void idol(const std::string & file_name);
    void Load(const std::string & file_name);
    std::string Get(const std::string & key) const;
    void Set(const std::string & key, const std::string & value);

private:
    std::map<std::string, std::string> params;
};

}
}

#endif
