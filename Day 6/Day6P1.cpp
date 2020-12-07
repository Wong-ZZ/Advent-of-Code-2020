#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set> 


int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::unordered_set<char> s;
    int result = 0;

    if (input.is_open()) {
        int row, col;
        while (std::getline(input, line)) {
            if (line == "") {
                s.clear();
            }

            for (char c : line) {
                if (s.count(c) != 1) {
                    ++result;
                    s.insert(c);
                }
            }
        }
        input.close();
    }

    std::cout << result << "\n";
    return result;
}