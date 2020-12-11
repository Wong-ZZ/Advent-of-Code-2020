#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line, instruction;
    ifstream input("input.txt");
    vector<int> v;

    if (input.is_open()) {
        while (getline(input, line)) {
            v.push_back(stoi(line));
        }
        input.close();
    }

    sort(v.begin(), v.end());

    int one = 0, three = 1, counter = 0, diff;
    for (auto& i : v) {
        diff = i - counter;
        if (diff == 1) ++one;
        if (diff == 3) ++three;
        counter = i;
    }

    cout << one * three << "\n";
    return 0;
}