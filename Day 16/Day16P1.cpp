#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    unordered_map<string,vector<pair<int,int>>> constraints;

    if (input.is_open()) {
        getline(input, line);
        while (line.find("your ticket:") == -1) {
            if (line.length() <= 1) {
                getline(input, line);
                continue;
            }
            int idx_colon = line.find_first_of(':');
            string constraint = line.substr(0, idx_colon);
            line = line.substr(idx_colon + 2);
            while (!line.empty()) {
                int idx_or = line.find_first_of("or");
                int idx_dash = line.find_first_of('-');
                int lower_limit = stoi(line.substr(0, idx_dash));
                int upper_limit = idx_or == -1 ? stoi(line.substr(idx_dash + 1)) : stoi(line.substr(idx_dash + 1, idx_or - 1));
                constraints[constraint].push_back({lower_limit, upper_limit});
                line = idx_or == -1 ? "" : line.substr(idx_or + 3);
            }
            getline(input, line);
        }

        while (line.find("nearby tickets:") == -1) {
            getline(input, line);
        }

        int total = 0;
        int error_rate = 0;
        while (getline(input, line)) {
            ++total;
            while (!line.empty()) {
                int idx_comma = line.find_first_of(',');
                int current_num = stoi(line.substr(0, idx_comma == -1 ? line.length() : idx_comma));
                bool meets_any_constraint = false;
                for (auto& key_value : constraints) {
                    vector<pair<int,int>> ranges = key_value.second;
                    bool meets_constraint = false;
                    for (auto& range : ranges) {
                        int lower = range.first;
                        int upper = range.second;
                        if (current_num >= lower && current_num <= upper) {
                            meets_constraint = true;
                            break;
                        }
                    }
                    if (meets_constraint) {
                        meets_any_constraint = true;
                        break;
                    }
                }
                if (!meets_any_constraint) {
                    error_rate += current_num;
                }
                line = line.substr(idx_comma == -1 ? line.length() : idx_comma + 1);
            }
        }

        input.close();

        cout << error_rate << "\n";
    }

    return 0;
}