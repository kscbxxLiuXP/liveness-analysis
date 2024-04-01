#ifndef LIVENESS_INIT_H
#define LIVENESS_INIT_H

#include "operand.h"
#include <vector>
#include <unordered_map>


#define DEFINE_INST(op, ...) {#op, {__VA_ARGS__}}

std::unordered_map<std::string, std::vector<operand_type>> inst_map = {
        DEFINE_INST(pushq, IN),
        DEFINE_INST(popq, OUT),
        DEFINE_INST(cmpl, IN, IN),
        DEFINE_INST(movl, IN, OUT),
        DEFINE_INST(movq, IN, OUT),
        DEFINE_INST(leavq, IN, OUT),
        DEFINE_INST(xorq, IN, INOUT),
        DEFINE_INST(addq, IN, INOUT),
        DEFINE_INST(subq, IN, INOUT),
        DEFINE_INST(xorl, IN, INOUT),
        DEFINE_INST(addl, IN, INOUT),
        DEFINE_INST(subl, IN, INOUT),
        DEFINE_INST(leal, IN, OUT),
        DEFINE_INST(leaq, IN, OUT),
};


#endif //LIVENESS_INIT_H
