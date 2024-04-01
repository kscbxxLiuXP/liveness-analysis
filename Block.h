#ifndef LIVENESS_BLOCK_H
#define LIVENESS_BLOCK_H

#include <string>
#include <vector>
#include <unordered_set>
#include "Instruction.h"

using namespace std;

class Block {
public:
    string id;
    int idx{};
    string label;
    string function;
    vector<string> code;
    vector<Instruction *> instructions;
    vector<int> nexts;
    vector<int> prevs;
    unordered_set<string> in;
    unordered_set<string> out;


    Block() = default;

    Block(const string &function, const string &label);

    void createBlockInOut();

    [[maybe_unused]] string toString();

    string toLabelString();
};


#endif //LIVENESS_BLOCK_H
