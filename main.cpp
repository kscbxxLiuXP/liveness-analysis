#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Block.h"
#include "Func.h"
#include "Instruction.h"
#include <boost/algorithm/string.hpp>
#include "init.h"
#include "operand.h"
#include <regex>
#include "utils.h"
#include <cstdlib>

using namespace std;
using namespace boost::algorithm;

std::vector<std::string> control_cmds;
std::vector<std::string> keywords;
vector<Block *> blocks;
vector<Func *> funcs;

void init() {
    control_cmds = {"jmp", "je", "jne", "jg", "jge", "jl", "jle", "ret"};
    keywords = {".string", ".long", ".int", ".float", ".double"};
}


vector<operand_type> get_operand_type(const string &operator_name) {
    return inst_map[operator_name];
}

/**
 * 1.whether the operand is a register
 * 2. if it is a register, return the register name
 * @param operand
 * @return
 */
string get_operand_regs(string &operand) {
    //extract the %... from the operand
    regex reg("%([a-zA-Z]+)");
    smatch match;
    regex_search(operand, match, reg);
    if (!match.empty()) {
        return match[1];
    }
    return "";
}

void tokenizer(Instruction *inst, string &line) {
    // 1. get operator
    string s_operator;
    string s_operands;
    for (auto it = line.begin(); it != line.end(); it++) {
        if (*it == ' ') {
            s_operator = line.substr(0, it - line.begin());
            s_operands = line.substr(it - line.begin() + 1);
            break;
        }
    }
    if (s_operator.empty()) {
        s_operator = line;
    }
    inst->i_operator = s_operator;//movq


    auto operand_types = get_operand_type(s_operator); // movq -> [IN, OUT]


    //2. get operands $5 %eax
    if (!s_operands.empty()) {
        vector<string> operands; //[ $5, %eax]
        split(operands, s_operands, is_any_of(","));

        //if the operand type is not defined, set it to UNDEF
        if (operand_types.empty()) {
            cerr << "undef operator type:" << line << endl;
            for (int i = 0; i < operands.size(); ++i) {
                operand_types.push_back(UNDEF);
            }
        }

        if (operands.size() != operand_types.size()) {
            cerr << "operands size not match: " << line << endl;
            return;
        }

        int opnd_idx = 0;
        for (auto &opnd: operands) {
            trim(opnd); // opnd = $5 | %eax
            string reg_name = get_operand_regs(opnd);
            operand_type type = operand_types[opnd_idx];
            if (!reg_name.empty()) {
                switch (type) {
                    case IN:
                        inst->ins.push_back(reg_name);
                        break;
                    case OUT:
                        inst->outs.push_back(reg_name);
                        break;
                    case INOUT:
                        inst->ins.push_back(reg_name);
                        inst->outs.push_back(reg_name);
                        break;
                    case UNDEF:
                        break;
                }
            }
            L:
            inst->operands.emplace_back(opnd, type, reg_name);
            opnd_idx++;
        }
    }
}

void parseConst(vector<string>::iterator &it) {
    std::vector<std::string> tokens;
    split(tokens, *it, is_any_of(":"));
    string label = tokens[0];
    cout << "label:" << label << " code:";

    it++;
    string line = *it;
    while (contain_const_code(line)) {
        cout << line;
        it++;
        line = *it;
    }
    cout << endl;
}

/**
 * resolve each segment in a function
 * @param it
 * @param func_label
 */
void parseBlock(vector<string>::iterator &it, string &func_label) {
    //.xxxx
    string line = *it;
    string label = line.substr(0, line.size() - 1);
    int sub_block_idx = 1;

    auto *block = new Block(func_label, label);

    line = *(++it);
    while (!starts_with(line, ".L")) {
        if (line[0] == ';' || starts_with(line, ".cfi")) {
            line = *(++it);
            continue;
        }
        //add inst to block
        auto *inst = new Instruction();
        tokenizer(inst, line);
        block->code.push_back(line);
        block->instructions.push_back(inst);
        if (contain_control_code(line)) {
            if (!block->code.empty()) {
                block->toString();
                block->createBlockInOut();
                blocks.push_back(block);
            }
            block = new Block(func_label, label + "_" + to_string(sub_block_idx));

            line = *(++it);
            continue;
        }
        line = *(++it);
    }

    if (!block->code.empty()) {
        block->toString();
        blocks.push_back(block);
    }
    //.xxx
}

/**
 * parse function such like main: add1:
 * @param it
 */
void parseFunc(vector<string>::iterator &it) {
    it++;
    string line = *it; //main:
    string func_label = line.substr(0, line.size() - 1);

    //eat first segment
    it++;
    line = *it; //.XXX
    //end when .LFE
    while (!starts_with(line, ".LFE")) {
        parseBlock(it, func_label);
        line = *it;
    }
    //create func object
    auto *func = new Func();
    blocks.swap(func->blocks);
    func->map_label_idx();
    func->create_cfg();
    func->print_cfg();
    funcs.push_back(func);


}

void toDot() {
    std::ofstream dotfile("../graph.dot");
    dotfile << "digraph G {" << endl;
    dotfile << "\tgraph [dpi=300]" << endl;
    dotfile << "\tnode [shape=box nojustify=false] " << endl;

    int node_idx = 0;
    //restore nodeX to which block id
    unordered_map<string, int> label_map;

    for (const auto &v: funcs) {
        for (auto b: v->blocks) {
            label_map[b->id] = node_idx;
            string label = "node" + to_string(node_idx);
            dotfile << "\t" << label << " [label=\"" << b->toLabelString() << "\"];" << endl;
            node_idx++;
        }
    }
    for (const auto &v: funcs) {
        for (auto b: v->blocks) {
            for (auto n: b->nexts) {
                //get next id
                string next_id = v->blocks[n]->id;
                string next_node_label = "node" + to_string(label_map[next_id]);
                string node_label = "node" + to_string(label_map[b->id]);

                dotfile << "\t" << node_label << " -> " << next_node_label << ";" << endl;
            }
        }
    }


    dotfile << "}" << endl;
    dotfile.close();

    string cmd = "dot -Tpng ../graph.dot -o ../graph.png";
    int r = system(cmd.c_str());
    if (r == 0) {
        cout << "export graph.png." << endl;
    } else {
        cout << "export failed" << endl;
    }
}

pair<vector<unordered_set<string>>, vector<unordered_set<string>>> liveness(vector<Block *> &blocks) {
    bool condition = true;

    auto inn = vector<unordered_set<string>>(blocks.size());
    auto out = vector<unordered_set<string>>(blocks.size());

    while (condition) {
        condition = false;
        for (int n = 0; n < blocks.size(); ++n) {
            auto use = blocks[n]->in;
            auto def = blocks[n]->out;
            auto succ = blocks[n]->nexts;

            auto innp = inn[n];
            auto outp = out[n];

            //inn[n] = out[n] -def
            set_difference(out[n].begin(), out[n].end(), def.begin(), def.end(), inserter(inn[n], inn[n].begin()));

            //inn[n].update(use)
            inn[n].insert(use.begin(), use.end());

            out[n].clear();
            for (auto s: succ) {
                out[n].insert(inn[s].begin(), inn[s].end());
            }

            if (out[n] != outp || inn[n] != innp) {
                condition = true;
            }
        }
    }
    return make_pair(inn, out);
}

int main() {

    string filename = "../example3.s";
    ifstream file(filename, ios::in);

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        trim(line);
        lines.push_back(line);
    }

    init();
    // create basic blocks
    auto it = lines.begin();
    while (it != lines.end()) {
        line = *it;
        if (line[0] == ';' || starts_with(line, ".cfi")) {
            continue;
        }
        //resolve static const data
        if (starts_with(line, ".LC")) {
            parseConst(it);
            continue;
        }
        if (ends_with(line, "@function")) {
            parseFunc(it);
            continue;
        }
        it++;
    }
    // block to dot
    toDot();
    //
    for (auto func: funcs) {
        auto r = liveness(func->blocks);
        auto inn = r.first;
        auto out = r.second;
        for (int i = 0; i < func->blocks.size(); ++i) {
            cout << "block:" << func->blocks[i]->id << endl;
            cout << "in:";
            for (auto &v: inn[i]) {
                cout << v << " ";
            }
            cout << endl;
            cout << "out:";
            for (auto &v: out[i]) {
                cout << v << " ";
            }
            cout << endl;
            cout << endl;
        }
    }
    return 0;
}
