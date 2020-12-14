#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

int main() {
    string line, mask_string;
    ifstream input("input.txt");
    long mask1, mask2, address, idx_right_square_bracket, idx_equal;
    unordered_map<long,long> mem;

    if (input.is_open()) {
        while (getline(input, line)) {
            idx_equal = line.find_first_of('=');
            if (line.substr(0, 4) == "mask") {
                mask1 = 0;
                mask2 = 0;
                mask_string = line.substr(idx_equal + 2);
                for (int i = 0; i < 36; ++i) {
                    mask1 += mask_string[i] == '1' ? pow(2, 35 - i) : 0;
                    mask2 += mask_string[i] == 'X' ? pow(2, 35 - i) : 0;
                }
                continue;
            }

            idx_right_square_bracket = line.find_first_of(']');
            address = stoi(line.substr(4, idx_right_square_bracket - 4));
            mem[address] = mask1 + (stoi(line.substr(idx_equal + 2)) & mask2);
        }
        
        input.close();
    }

    long sum = 0;
    cout << mask1 << "," << mask2 << "\n";
    for (auto& it : mem) {
        cout << it.first << ":" << it.second << "\n";
        sum += it.second;
    }
    cout << sum << "\n";

    return 0;
}