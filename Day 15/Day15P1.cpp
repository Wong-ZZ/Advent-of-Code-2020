#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    vector<int> input = {9,12,1,4,17,0,18};
    unordered_map<int,int> history;
    int turn = 0, next, last;
    for (auto& in : input) {
        history[in] = ++turn;
    }

    next = 0;

    while (turn < 2020) {
        cout << next << "\n";
        ++turn;
        if (history.count(next) != 1) {
            history[next] = turn;
            next = 0;
            continue;
        }

        last = next;
        next = turn - history[last];
        history[last] = turn;
    }

    return 0;
}