#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::set<int> s;
    int max = 0;
    int min = 1 << 8;

    if (input.is_open()) {
        int row, col, id;
        while (std::getline(input, line)) {
            row = 0;
            col = 0;
            for (int i = 0; i < 7; ++i) {
                if (line[i] == 'B') {
                    row += 1 << (6 - i);
                }
            }

            for (int i = 7; i < 10; ++i) {
                if (line[i] == 'R') {
                    col += 1 << (9 - i);
                }
            }

            id = row * 8 + col;
            max = std::max(max, id);
            min = std::min(min, id);
            s.insert(id);
        }

        input.close();
    }

    for (int i = min + 1; i < max; ++i) {
        if (s.count(i) != 1) {
            std::cout << i << "\n";
            return i;
        }
    }
}