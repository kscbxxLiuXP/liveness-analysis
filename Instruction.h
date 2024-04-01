#ifndef LIVENESS_INSTRUCTION_H
#define LIVENESS_INSTRUCTION_H

#include <string>
#include <utility>
#include <vector>
#include "operand.h"


class Instruction {
public:
    std::string i_operator;
    std::vector<Operand> operands;
    std::vector<std::string> ins;
    std::vector<std::string> outs;

    std::string toString();
};


#endif //LIVENESS_INSTRUCTION_H
