#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    vector<int> p1, p2;

    if (input.is_open()) {
        getline(input, line);
        while (getline(input, line)) {
            if (line.empty()) {
                break;
            }
            p1.push_back(stoi(line));
        }
        getline(input, line);
        while (getline(input, line)) {
            if (line.empty()) {
                break;
            }
            p2.push_back(stoi(line));
        }
        input.close();
    }

    while (!p1.empty() && !p2.empty()) {
        int next1 = p1.front();
        int next2 = p2.front();
        p1.erase(p1.begin());
        p2.erase(p2.begin());
        if (next1 > next2) {
            p1.push_back(next1);
            p1.push_back(next2);
        } else {
            p2.push_back(next2);
            p2.push_back(next1);
        }
    }

    int count = 0;
    vector<int> winner = p1.empty() ? p2 : p1;
    int len = winner.size();
    for (auto& i : winner) {
        count += i * len;
        --len;
    }

    cout << count << "\n";


    return 0;
}