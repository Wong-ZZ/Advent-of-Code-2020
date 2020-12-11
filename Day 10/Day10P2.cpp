#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

long calculate(int current, set<int>* s, int max, map<int, long>* m) {
    if ((*m).count(current) == 1) {
        return (*m)[current];
    }

    if (current == max) {
        return 1;
    }

    if (current > max || (*s).count(current) == 0) {
        return 0;
    }

    long result = 0;
    for (int i = 1; i < 4; ++i) {
        result += calculate(current + i, s, max, m);
    }

    (*m)[current] = result;
    return result;
}

int main() {
    string line, instruction;
    ifstream input("input.txt");
    set<int> s;
    s.insert(0);
    if (input.is_open()) {
        while (getline(input, line)) {
            s.insert(stoi(line));
        }
        input.close();
    }

    map<int, long> m;
    int max = *s.rbegin();

    cout << calculate(0, &s, max, &m) << "\n";
    return 0;
}