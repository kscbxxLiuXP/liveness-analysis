#include "Instruction.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/range/adaptor/transformed.hpp>

std::string Instruction::toString() {
    std::stringstream ss;
    ss << i_operator << " ";
    if (!operands.empty()) {

        std::string r = boost::algorithm::join(
                operands | boost::adaptors::transformed([](const Operand &s) { return s.exp; }), ", ");

        ss << r << std::endl;
        ss << "ins:  [ " << boost::algorithm::join(ins, ", ") << " ]" << std::endl;
        ss << "outs: [ " << boost::algorithm::join(outs, ", ") << " ]" << std::endl;

    }
    return ss.str();
}