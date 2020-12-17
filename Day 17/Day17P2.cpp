#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int count_active_neighbors(int x, int y, int z, int w, map<int,map<int,map<int,map<int,bool>>>>* cubes) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    if (i == 0 && j == 0 && k == 0 && l == 0) {
                        continue;
                    }
                    count += (*cubes)[x + i][y + j][z + k][w + l];
                }
            }
        }
    }
    return count;
}

int main() {
    string line;
    ifstream input("input.txt");
    map<int,map<int,map<int,map<int,bool>>>> cubes, temp;

    int x_min = 0, x_max, y_min = 0, y_max, z_min = 0, z_max = 0, w_min = 0, w_max = 0;
    int x, y = 0, z = 0, w = 0;
    if (input.is_open()) {
        while (getline(input, line)) {
            x_max = line.length() - 2;
            for (x = 0; x < line.length(); ++x) {
                cubes[x][y][z][w] = line[x] == '#';
            }
            ++y;
        }
        y_max = y - 1;
        input.close();
    }

    int cycles = 0, test = 0;
    bool is_active;
    while (cycles < 6) {
        for (int i = x_min - 1; i <= x_max + 1; ++i) {
            for (int j = y_min - 1; j <= y_max + 1; ++j) {
                for (int k = z_min - 1; k <= z_max + 1; ++k) {
                    for (int l = w_min - 1; l <= w_max + 1; ++l) {
                        is_active = cubes[i][j][k][l];
                        int count = count_active_neighbors(i, j, k, l, &cubes);
                        bool is_active_next;
                        if (is_active) {
                            is_active_next = count == 2 || count == 3;
                            temp[i][j][k][l] = is_active_next;
                        } else {
                            is_active_next = count == 3;
                            temp[i][j][k][l] = is_active_next;
                        }
                        if (is_active_next) {
                            ++test;
                            x_min = min(i, x_min);
                            x_max = max(i, x_max);
                            y_min = min(j, y_min);
                            y_max = max(j, y_max);
                            z_min = min(k, z_min);
                            z_max = max(k, z_max);
                            w_min = min(l, w_min);
                            w_max = max(l, w_max);
                        }
                    }
                }
            }
        }
        cubes = temp;
        temp.clear();
        ++cycles;
    }

    int count = 0;
    for (int i = x_min; i <= x_max; ++i) {
        for (int j = y_min; j <= y_max; ++j) {
            for (int k = z_min; k <= z_max; ++k) {
                for (int l = w_min; l <= w_max; ++l) {
                    count += cubes[i][j][k][l];
                }
            }
        }
    }
    cout << count << "\n";

    return 0;
}