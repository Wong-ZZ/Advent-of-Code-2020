#include <iostream>
#include <set>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::set<int> s;
    int curr, remaining;
    int result = 0;

    if (input.is_open()) {
        while (std::getline (input, line)) {
            s.insert(std::stoi(line));
        }

        input.close();
    }

    for (auto i : s) {
        for (auto j : s) {
            if (j > 2020 - i) {
                continue;
            }

            remaining = 2020 - i - j;
            if (s.count(remaining) == 1) {
                result = i * j * remaining;
                break;
            }
        }

        if (result != 0) {
            break;
        }
    }

    std::cout << result;
    std::cout << "\n";
    return result;
}