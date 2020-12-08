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

    unordered_set<int> s;
    int line_num, acc, current_val = 0;
    string current_instruction;
    while (true) {
        if (s.count(line_num) == 1) {
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

    cout << acc << "\n";
    return 0;
}