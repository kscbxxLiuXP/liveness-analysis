#ifndef LIVENESS_OPERAND_H
#define LIVENESS_OPERAND_H

#include <string>
#include <vector>

enum operand_type {
    IN,
    OUT,
    INOUT,
    UNDEF
};

struct Operand {
    std::string exp;
    operand_type type;
    std::string register_name;

    Operand(std::string e, operand_type t, std::string r) : exp(std::move(e)), type(t), register_name(std::move(r)) {};

    Operand() {
        exp = "";
        type = IN;
        register_name = "";
    };

};

extern std::vector<std::string> control_cmds;
extern std::vector<std::string> keywords;

#endif //LIVENESS_OPERAND_H
