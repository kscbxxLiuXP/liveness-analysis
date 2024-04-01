#include "utils.h"
#include <boost/algorithm/string.hpp>
bool contain_control_code(std::string line) {
    return std::any_of(control_cmds.begin(), control_cmds.end(), [&line](const std::string &keyword) {
        return boost::algorithm::contains(line, keyword);
    });
}

bool contain_const_code(std::string line) {
    return std::any_of(keywords.begin(), keywords.end(), [&line](const std::string &keyword) {
        return boost::algorithm::contains(line, keyword);
    });
}
