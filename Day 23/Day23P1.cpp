#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> remove_three_cups(vector<int>* cups, int idx) {
    vector<int> result;
    
    for (int i = 0; i < 3; ++i) {
        if (idx >= cups->size() - 1) {
            result.push_back(cups->front());
            cups->erase(cups->begin());
        } else {
            result.push_back((*cups)[idx + 1]);
            cups->erase(cups->begin() + idx + 1);
        }
    }
    return result;
}

int main() {
    string input = "158937462";
    vector<int> cups;

    for (char& c : input) {
        cups.push_back(c - '0');
    }

    int min = 1, max = 9;
    int count = 0;
    int idx = 0;

    while (count < 100) {
        int current = cups[idx];
        vector<int> three_cups = remove_three_cups(&cups, idx);
        int next_cup = current - 1;

        while (true) {
            bool found = false;
            for (int i = 0; i < cups.size(); ++i) {
                if (cups[i] == next_cup) {
                    found = true;
                    for (auto& j : three_cups) {
                        ++i;
                        if (i == cups.size()) {
                            cups.push_back(j);
                        } else {
                            cups.insert(cups.begin() + i, j);
                        }
                    }
                    break;
                }
            }
            if (found) {
                break;
            }
            --next_cup;
            if (next_cup < min) {
                next_cup = max;
            }
        }

        for (int i = 0; i < cups.size(); ++i) {
            if (cups[i] == current) {
                idx = (i + 1) % cups.size();
                break;
            }
        }

        ++count;
    }
    for (auto& i : cups) {
        cout << i << "\n";
    }


    return 0;
}