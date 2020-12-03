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

    int steps_x[] = {1, 3, 5, 7, 1};
    int steps_y[] = {1, 1, 1, 1, 2};
    int x, y, step_x, step_y;
    int rows = v.size();
    int cols = v[0].size();
    int count = 0;
    int result = 1;
    for (int i = 0; i < 5; ++i) {
        x = 0;
        y = 0;
        count = 0;
        step_x = steps_x[i];
        step_y = steps_y[i];
        while (x < cols && y < rows) {
            if (v[y][x] == '#') {
                ++count;
            }

            x = (x + step_x) % cols;
            y += step_y;
        }
        result *= count;
    }

    return result;
}