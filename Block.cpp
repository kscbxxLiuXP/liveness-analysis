#include "Block.h"

#include <sstream>
#include <iostream>

Block::Block(const std::string &function, const std::string &label) {
    this->function = function;
    this->label = label;
    this->id = function + "_" + label;
}


string Block::toString() {
    stringstream ss;
    ss << "label:" << label << " function:" << function << endl;
    for (const auto &c: code) {
        ss << "        " << c << endl;
    }
    return ss.str();
}


string Block::toLabelString() {
    stringstream ss;
    ss << "label:" << label << " function:" << function << "\\l";
    for (const auto &c: code) {
        ss << "        " << c << "\\l";
    }
    return ss.str();
}


void Block::createBlockInOut() {
    for (auto &inst: instructions) {
        in.insert(inst->ins.begin(), inst->ins.end());
        out.insert(inst->outs.begin(), inst->outs.end());
    }
}