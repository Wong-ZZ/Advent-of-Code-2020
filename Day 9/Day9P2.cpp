#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    vector<int> v, store;
    unordered_set<int> s;
    int current, result, count = 0, PREAMBLE_SIZE = 25;
    bool is_valid;

    if (input.is_open()) {
        for (int i = 0; i < PREAMBLE_SIZE; ++i) {
            getline(input, line);
            current = stoi(line);
            v.push_back(current);
            store.push_back(current);
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
            store.push_back(current);

            if (!is_valid) {
                result = current;
                break;
            }
        }
        input.close();

        int sum = 0;
        for (int i = 0; i < store.size(); ++i) {
            for (int j = i + 1; j < store.size(); ++j) {
                sum = 0;
                for (int k = i; k <= j; ++k) {
                    sum += store[k];
                }

                if (sum == result) {
                    int minimum = 1 << 30, maximum = -1;
                    for (int k = i; k <= j; ++k) {
                        minimum = min(minimum, store[k]);
                        maximum = max(maximum, store[k]);
                    }
                    cout << minimum + maximum << "\n";
                    return 0;
                }

                if (sum > result) {
                    break;
                }
            }
        }
    }

    return 0;
}