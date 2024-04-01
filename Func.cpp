#include "Func.h"
#include "utils.h"
#include <iostream>

using namespace std;

void Func::create_cfg() {
    for (int i = 0; i < blocks.size(); ++i) {
        auto block = blocks[i];
        if (block->instructions.empty()) {
            continue;
        }
        auto last_inst = block->instructions.back();
        string last_op = last_inst->i_operator;
        if (contain_control_code(last_op)) {
            if (last_op == "ret") {
                continue;
            }

            string target = last_inst->operands[0].exp;
            auto it = label_idx_map.find(target);
            if (it != label_idx_map.end()) {

                block->nexts.push_back(it->second);
                blocks[it->second]->prevs.push_back(i);
            }

            if (last_op == "jmp") {
                continue;
            }
        }
        if (i + 1 < blocks.size()) {
            block->nexts.push_back(i + 1);
            blocks[i + 1]->prevs.push_back(i);
        }
    }
}

void Func::print_cfg() {
    for (auto block: blocks) {
        cout << block->label << " -> ";
        for (auto next: block->nexts) {
            cout << "  " << idx_label_map[next];
        }
        cout << "\n";
    }
}

void Func::map_label_idx() {
    for (int i = 0; i < blocks.size(); ++i) {
        blocks[i]->idx = i;
        label_idx_map[blocks[i]->label] = i;
        idx_label_map[i] = blocks[i]->label;
    }
}
