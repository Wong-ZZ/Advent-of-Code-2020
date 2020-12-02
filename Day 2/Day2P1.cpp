#include <iostream>
#include <set>
#include <fstream>
#include <string>

int main() {
    std::string line, pw;
    std::ifstream input("input.txt");
    std::set<int> s;
    int count, min, max, idx_dash, idx_space, idx_colon;
    char c;
    int result = 0;

    if (input.is_open()) {
        while (std::getline (input, line)) {
            count = 0;
            idx_dash = line.find_first_of('-');
            idx_space = line.find_first_of(' ');
            idx_colon = line.find_first_of(':');
            min = std::stoi(line.substr(0, idx_dash));
            max = std::stoi(line.substr(idx_dash + 1, idx_space));
            c = line[idx_space + 1];
            pw = line.substr(idx_colon + 2);

            for (char i : pw) {
                if (i == c) {
                    ++count;
                }
            }

            if (count >= min && count <= max) {
                ++result;
            }
        }

        input.close();
    }

    std::cout << result << "\n";
    return result;
}