#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    string line, instruction;
    ifstream input("input.txt");
    vector<int> v;
    unordered_set<int> s;
    int current, count = 0, PREAMBLE_SIZE = 25;
    bool is_valid;

    if (input.is_open()) {
        for (int i = 0; i < PREAMBLE_SIZE; ++i) {
            getline(input, line);
            current = stoi(line);
            v.push_back(current);
            s.insert(current);
        }
        

        while (getline(input, line)) {
            is_valid = false;
            current = stoi(line);
            for (auto& i : s) {
                if (i >= current) {
                    continue;
                }

                if (s.count(current - i) == 1) {
                    is_valid = true;
                    break;
                }
            }

            s.erase(v[count]);
            s.insert(current);
            v[count] = current;
            count = (count + 1) % PREAMBLE_SIZE;

            if (!is_valid) {
                cout << current << "\n";
                return 0;
            }
        }
        input.close();
    }

    return 0;
}