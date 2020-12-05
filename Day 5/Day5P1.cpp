#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    int result = 0;

    if (input.is_open()) {
        int row, col;
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

            result = std::max(result, row * 8 + col);
        }

        input.close();
    }

    std::cout << result << "\n";
    return result;
}