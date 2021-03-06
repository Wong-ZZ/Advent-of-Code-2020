#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

bool is_simplified(vector<string> rule) {
    regex check("[ab]+");
    for (auto& sub_rule : rule) {
        if (!regex_match(sub_rule, check)) {
            return false;
        }
    }
    return true;
}

vector<string> simplify_rule(vector<string> rule, vector<vector<string>> *rules, int n) {
    if (is_simplified(rule)) {
        return rule;
    }

    vector<string> simplified_rule, simplified_sub_rule, current = {""}, temp;
    int rule_num, idx_space;
    for (auto& sub_rule : rule) {
        idx_space = sub_rule.find_first_of(' ');
        while (idx_space != -1) {
            rule_num = stoi(sub_rule.substr(0, idx_space));
            simplified_sub_rule = simplify_rule((*rules)[rule_num], rules, rule_num);
            for (auto& i : current) {
                for (auto& j : simplified_sub_rule) {
                    temp.push_back(i + j);
                }
            }
            current = temp;
            temp.clear();
            sub_rule = sub_rule.substr(idx_space + 1);
            idx_space = sub_rule.find_first_of(' ');
        }
        rule_num = stoi(sub_rule);
        simplified_sub_rule = simplify_rule((*rules)[rule_num], rules, rule_num);
        for (auto& i : current) {
            for (auto& j : simplified_sub_rule) {
                temp.push_back(i + j);
            }
        }
        current = temp;
        temp.clear();
        simplified_rule.insert(simplified_rule.end(), current.begin(), current.end());
        current = {""};
    }
    (*rules)[n] = simplified_rule;

    return simplified_rule;
}

int main() {
    string line;
    ifstream input("input.txt");
    int idx_quote, idx_colon, index, idx_delimiter;
    vector<vector<string>> rules(1000);

    if (input.is_open()) {
        getline(input, line);
        while (line.find("\r\n") != string::npos) {
            line.erase (line.find("\r\n"), 2);
        }
        while (line.length() > 1) {
            idx_quote = line.find_first_of('"');
            idx_colon = line.find_first_of(':');
            index = stoi(line.substr(0, idx_colon));
            line = line.substr(idx_colon + 2);
            if (idx_quote != -1) {
                rules[index].push_back(line.substr(1, 1));
            } else {
                idx_delimiter = line.find_first_of('|');
                while (idx_delimiter != -1) {
                    rules[index].push_back(line.substr(0, idx_delimiter - 1));
                    line = line.substr(idx_delimiter + 2);
                    idx_delimiter = line.find_first_of('|');
                }
                rules[index].push_back(line);
            }
            getline(input, line);
            while (line.find ("\r\n") != string::npos) {
                line.erase (line.find ("\r\n"), 2);
            }
        }

        vector<string> rule_zero = simplify_rule(rules[0], &rules, 0);
        int count = 0;
        while (getline(input, line)) {
            while (line.find("\r\n") != string::npos) {
                line.erase (line.find("\r\n"), 2);
            }
            for (auto& sub_rule : rule_zero) {
                if (line == sub_rule) {
                    ++count;
                    break;
                }
            }
        }
        cout << count << "\n";
        input.close();
    }

    return 0;
}