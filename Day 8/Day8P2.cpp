#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    string line, instruction;
    ifstream input("input.txt");
    vector<pair<string, int>> v;
    int idx_space, val;

    if (input.is_open()) {
        while (getline (input, line)) {
            idx_space = line.find(" ");
            instruction = line.substr(0, idx_space);
            val = stoi(line.substr(idx_space + 1));
            v.push_back({instruction, val});
        }
        input.close();
    }

    bool is_infinite;
    unordered_set<int> s;
    int line_num, acc, current_val, len = v.size();
    string current_instruction;
    for (int i = 0; i < len; ++i) {
        s.clear();
        is_infinite = false;
        instruction = v[i].first;
        if (instruction == "jmp" || instruction == "nop") {
            v.at(i) = {instruction == "jmp" ? "nop" : "jmp", v[i].second};
        } else {
            continue;
        }

        line_num = 0;
        acc = 0;
        current_val = 0;
        while (true) {
            if (line_num == len) {
                break;
            }
            if (s.count(line_num) == 1 || line_num > len) {
                is_infinite = true;
                break;
            }
            s.insert(line_num);

            current_instruction = v[line_num].first;
            current_val = v[line_num].second;

            if (current_instruction == "jmp") {
                line_num += current_val;
                continue;
            }

            if (current_instruction == "acc") {
                acc += current_val;
            }
            ++line_num;
        }

        if (!is_infinite) {
            cout << acc << "\n";
            break;
        }

        v.at(i) = {instruction == "jmp" ? "jmp" : "nop", v[i].second};
    }

    return 0;
}