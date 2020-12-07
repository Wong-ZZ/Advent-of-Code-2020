#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::vector<char> v1, v2, temp;
    bool is_first_person = true;
    int result = 0;

    if (input.is_open()) {
        int row, col;
        while (std::getline(input, line)) {
            if (line.empty()) {
                result += v1.size();
                // std::cout << v1.size() << "\n";
                v1.clear();
                is_first_person = true;
                continue;
            }

            if (v1.empty() && is_first_person) {
                for (char c : line) {
                    v1.push_back(c);
                }
                is_first_person = false;
            } else {
                for (char c : v1) {
                    if (line.find(c) != -1) {
                        v2.push_back(c);
                    }
                }
                temp = v1;
                v1 = v2;
                v2 = v1;
                v2.clear();
            }
        }
        result += v1.size();
        input.close();
    }

    std::cout << result << "\n";
    return result;
}