#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::string line, pw;
    std::ifstream input("input.txt");
    std::vector<std::string> v;

    if (input.is_open()) {
        while (std::getline(input, line)) {
            v.push_back(line);
        }

        input.close();
    }

    int x, y = 0;
    int rows = v.size();
    int cols = v[0].size();
    int result = 0;
    while (x < cols && y < rows) {
        if (v[y][x] == '#') {
            ++result;
        }

        x = (x + 3) % cols;
        y += 1;
    }

    return result;
}