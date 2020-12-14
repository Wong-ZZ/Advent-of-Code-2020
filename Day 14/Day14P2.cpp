#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>

using namespace std;

vector<long> get_addresses(long ini, vector<int> positions) {
    if (positions.empty()) {
        return {ini};
    }
    vector<long> result;
    int current_position = positions.back();
    positions.pop_back();
    vector<long> recurse0 = get_addresses(ini, positions);
    vector<long> recurse1 = get_addresses(ini + pow(2, current_position), positions);
    result.insert(result.end(), recurse0.begin(), recurse0.end());
    result.insert(result.end(), recurse1.begin(), recurse1.end());
    return result;
}

int main() {
    string line, mask_string;
    ifstream input("input.txt");
    long mask, idx_equal, init_value, idx_right_square_bracket, val, address, offset;
    unordered_map<long,long> mem;
    vector<int> floating_positions;

    if (input.is_open()) {
        while (getline(input, line)) {
            idx_equal = line.find_first_of('=');
            if (line.substr(0, 4) == "mask") {
                floating_positions.clear();
                mask = 0;
                offset = 0;
                mask_string = line.substr(idx_equal + 2);
                for (int i = 0; i < 36; ++i) {
                    mask += mask_string[i] == '1' ? pow(2, 35 - i) : 0;
                    offset += mask_string[i] == 'X' ? pow(2, 35 - i) : 0;
                    if (mask_string[i] == 'X') {
                        floating_positions.push_back(35 - i);
                    }
                }
                continue;
            }

            idx_right_square_bracket = line.find_first_of(']');
            address = stoi(line.substr(4, idx_right_square_bracket - 4));
            val = stoi(line.substr(idx_equal + 2));
            init_value = (address | mask) - (address & offset);
            for (auto& address : get_addresses(init_value, floating_positions)) {
                mem[address] = val;
            }
        }
        input.close();
    }

    long sum = 0;
    for (auto& it : mem) {
        sum += it.second;
    }
    cout << sum << "\n";

    return 0;
}