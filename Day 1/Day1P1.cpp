#include <iostream>
#include <set>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::set<int> s;
    int curr, remaining, result;

    if (input.is_open()) {
        while (std::getline (input, line)) {
            curr = std::stoi(line);
            remaining = 2020 - curr;
            if (s.count(remaining) == 1) {
                result = remaining * curr;
                break;
            }
            s.insert(curr);
        }
        input.close();
    }

    std::cout << result;
    std::cout << "\n";
    return result;
}