#include <iostream>
#include <vector>

using namespace std;

const int NUM_TURNS = 30000000; // change to 2020 for part 1
int history[NUM_TURNS];

int main() {
    vector<int> input = {9,12,1,4,17,0,18};
    int turn = 0, next, last;
    for (auto& in : input) {
        history[in] = ++turn;
    }

    next = 0;

    while (turn < NUM_TURNS) {
        if (turn == NUM_TURNS - 1) cout << next << "\n";
        ++turn;
        if (history[next] == 0) {
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