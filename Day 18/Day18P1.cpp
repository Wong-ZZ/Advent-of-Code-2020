#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

long eval_expr(string line) {
    int i = 0, j;
    while (line[i] != ' ') {
        ++i;
    }
    long result = stoi(line.substr(0, i));
    int len = line.length();
    char op;
    long arg;
    ++i;
    while (i < len) {
        op = line[i];
        i += 2;
        j = i;
        while (j < len && line[j] != ' ') {
            ++j;
        }
        arg = stoi(line.substr(i, j - i));
        if (op == '+') {
            result += arg;
        } else {
            result *= arg;
        }
        i = j + 1;
    }
    return result;
}

int find_matching_bracket(string line, int idx) {
    for (int i = idx; i >= 0; --i) {
        if (line[i] == '(') {
            return i;
        }
    }
    return -1;
}

int main() {
    string line, sub_expr;
    ifstream input("input.txt");
    long sum = 0, result_sub_expr;
    int idx_close_bracket, idx_open_bracket;
    
    if (input.is_open()) {
        while (getline(input, line)) {
            while (true) {
                idx_close_bracket = line.find_first_of(')');
                if (idx_close_bracket == -1) {
                    sum += eval_expr(line);
                    break;
                }
                idx_open_bracket = find_matching_bracket(line, idx_close_bracket);
                sub_expr = line.substr(idx_open_bracket + 1, idx_close_bracket - idx_open_bracket - 1);
                result_sub_expr = eval_expr(sub_expr);
                line = line.substr(0, idx_open_bracket) + to_string(result_sub_expr) + line.substr(idx_close_bracket + 1);
            }
        }
        cout << sum << "\n";
        input.close();
    }

    return 0;
}