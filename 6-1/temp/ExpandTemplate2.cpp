#include "../ExpandTemplate.h"
#include "algorithm"
#include "vector"


std::string EdxpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params) {
    std::vector<std::string> keys;
    for (auto const& [key, value] : params) {
        if (!key.empty()) {
            keys.push_back(key);
        }
    }
    std::sort(keys.begin(), keys.end(), [](std::string const& a, std::string const& b) {
        return a.size() > b.size();
    });
    std::string result = tpl;
    for (auto const& key : keys) {
        std::string const& value = params.at(key);
        std::size_t pos = 0;
        while ((pos = result.find(key, pos)) != std::string::npos) {
            result.replace(pos, key.size(), value);
            pos += value.size();
        }
    }
    return result;
}
