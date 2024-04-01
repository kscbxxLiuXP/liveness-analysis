#ifndef LIVENESS_UTILS_H
#define LIVENESS_UTILS_H

#include "operand.h"
#include <string>

bool contain_control_code(std::string line);

bool contain_const_code(std::string line);

#endif //LIVENESS_UTILS_H
