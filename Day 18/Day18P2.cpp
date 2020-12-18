#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

long eval_expr(string line) {
    int idx_plus = line.find_first_of('+');
    int sum, idx_one, idx_two;
    int len = line.length();
    while (idx_plus != -1) {
        sum = 0;
        for (int i = idx_plus - 2; i >= -1; --i) {
            if (i == -1 || line[i] == ' ') {
                sum += stoi(line.substr(i + 1, idx_plus - i - 2));
                idx_one = i + 1;
                break;
            }
        }
        for (int i = idx_plus + 2; i <= len; ++i) {
            if (i == len || line[i] == ' ') {
                sum += stoi(line.substr(idx_plus + 2, i - idx_plus - 2));
                idx_two = i;
                break;
            }
        }
        line = line.substr(0, idx_one) + to_string(sum) + line.substr(idx_two);
        idx_plus = line.find_first_of('+');
        len = line.length();
    }

    int i = 0, j;
    while (line[i] != ' ') {
        ++i;
    }
    long result = stoi(line.substr(0, i));
    i += 3;
    long arg;
    while (i < len) {
        j = i;
        while (j < len && line[j] != ' ') {
            ++j;
        }
        arg = stoi(line.substr(i, j - i));
        result *= arg;
        i = j + 3;
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