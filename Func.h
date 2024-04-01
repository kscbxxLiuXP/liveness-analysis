#ifndef LIVENESS_FUNC_H
#define LIVENESS_FUNC_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Block.h"

using namespace std;

class Func {
public:
    vector<Block *> blocks;
    string func_label;
    unordered_map<string, int> label_idx_map;
    unordered_map<int, string> idx_label_map;


    void create_cfg();

    void print_cfg();

    void map_label_idx();
};


#endif //LIVENESS_FUNC_H
