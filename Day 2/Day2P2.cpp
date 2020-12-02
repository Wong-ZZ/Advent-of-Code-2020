#include <iostream>
#include <set>
#include <fstream>
#include <string>

int main() {
    std::string line, pw;
    std::ifstream input("input.txt");
    std::set<int> s;
    int pos_one, pos_two, idx_dash, idx_space, idx_colon;
    char c;
    int result = 0;

    if (input.is_open()) {
        while (std::getline (input, line)) {
            idx_dash = line.find_first_of('-');
            idx_space = line.find_first_of(' ');
            idx_colon = line.find_first_of(':');
            pos_one = std::stoi(line.substr(0, idx_dash)) - 1;
            pos_two = std::stoi(line.substr(idx_dash + 1, idx_space)) - 1;
            c = line[idx_space + 1];
            pw = line.substr(idx_colon + 2);

            if (pw[pos_one] == c ^ pw[pos_two] == c) {
                ++result;
            }
        }

        input.close();
    }

    std::cout << result << "\n";
    return result;
}